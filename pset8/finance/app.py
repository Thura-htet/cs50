import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index(): # the things that need to be on portfolio ==> total-total, cash-left, for every company he owns the name, the symbol, shares, and price

    company_shares = db.execute("SELECT company, SUM(shares) AS shares FROM transactions WHERE user_id = :user GROUP BY company",
                            user=session["user_id"])

    all_infos = []
    for row in company_shares:
        company = row["company"]
        shares = row["shares"]
        stock_info = lookup(company.upper())
        all_info = {
            'symbol' : stock_info["symbol"],
            'name' : stock_info["name"],
            'share' : shares,
            'price' : stock_info["price"],
            'holding' : stock_info["price"] * shares
        }
        all_infos.append(all_info)

    total_holdings = 0
    for info in all_infos:
        total_holdings += info["holding"]

    cash_left = db.execute("SELECT cash FROM users WHERE id = :user",
                            user=session["user_id"])

    total_total = cash_left[0]["cash"] + total_holdings

    return render_template("index.html", portfolio=all_infos, total_holdings=total_holdings, total_total=total_total, cash=cash_left[0]["cash"])


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol", 400)

        elif not shares:
            return apology("must provide shares", 400)

        stock = lookup(symbol.upper())
        if stock == None:
            return apology("invalid symbol", 400)

        symbol = stock["symbol"].upper()
        price = stock["price"]
        user_id = session["user_id"]

        cash = db.execute("SELECT cash FROM users WHERE id=:user", user = user_id)

        if cash[0]["cash"] < (price * int(shares)):
            return apology("not enough cash", 400)

        cash = cash[0]["cash"] - (price * int(shares))

        db.execute("INSERT INTO transactions (user_id, company, shares, method, price) VALUES (:user, :name, :amount, :buy, :cost)",
                    user=user_id, name=symbol, amount=shares, buy="buy", cost=price)
        db.execute("UPDATE users SET cash = :amount WHERE id = :user",
                    user=user_id, amount = cash)

        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    log = db.execute("SELECT company, shares, price, time FROM transactions WHERE user_id = :user",
                        user=session["user_id"])
    return render_template("history.html", log=log)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":

        if not request.form.get("symbol"):
            return apology("must provide symbol", 400)

        symbol = request.form.get("symbol")
        stock = lookup(symbol.upper())
        if stock == None:
            return apology("invalid symbol", 400)

        name = stock["name"]
        symbol = stock["symbol"]
        price = usd(stock["price"])

        return render_template("quote.html", name=name, symbol=symbol, price=price)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    session.clear()

    if request.method == "POST":
        usernames = db.execute("SELECT username FROM users")
        if not request.form.get("username"):
            return apology("must provide username", 403)

        elif not request.form.get("password"):
            return apology("must provide password", 403)

        elif not request.form.get("confirm-password"):
            return apology("must confirm password", 403)

        elif request.form.get("username") in usernames:
            return apology("username is already taken", 403)

        elif request.form.get("password") != request.form.get("confirm-password"):
            return apology("passwords must be the same", 403)

        name = request.form.get("username")
        password = request.form.get("confirm-password")
        db.execute("INSERT INTO users (username, hash) VALUES (:name, :password)", name=name, password=generate_password_hash(password))

        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        session["user_id"] = rows[0]["id"]

        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    if request.method == "POST":

        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol", 400)

        elif not shares:
            return apology("must provide shares", 400)

        stock = lookup(symbol.upper())
        if stock == None:
            return apology("invalid symbol", 400)

        symbol = stock["symbol"].upper()
        price = stock["price"]
        user_id = session["user_id"]

        shares_owned = db.execute("SELECT SUM(shares) AS shares FROM transactions WHERE user_id = :user GROUP BY company HAVING company = :symbol",
                            user=session["user_id"], symbol=symbol)

        if int(shares) > shares_owned[0]["shares"]:
            return apology("not own enough shares", 400)

        cash = db.execute("SELECT cash FROM users WHERE id=:user", user = user_id)

        cash = cash[0]["cash"] + (price * int(shares))

        amount = -int(shares)

        db.execute("INSERT INTO transactions (user_id, company, shares, method, price) VALUES (:user, :name, :amount, :sell, :cost)",
            user=user_id, name=symbol, amount=amount, sell="sell", cost=price)
        db.execute("UPDATE users SET cash = :cash WHERE id = :user",
                    user=user_id, cash = cash)

        return redirect("/")

    else:
        return render_template("sell.html")


@app.route("/trend", methods=["GET", "POST"])
# @login_required
def trend():
    """
    Show the stock trend
    """
    if request.method == "POST":
        symbol = request.form.get("symbol")
        start = request.form.get("start")
        end = request.form.get("end")
        print(type(start), start)
        return render_template("trend.html")
    else:
        return render_template("trend.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
