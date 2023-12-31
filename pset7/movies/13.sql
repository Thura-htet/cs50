SELECT DISTINCT name FROM people JOIN stars ON people.id = stars.person_id WHERE movie_id IN
(SELECT movies.id FROM movies JOIN 
(stars JOIN  people ON  stars.person_id = people.id)
ON movies.id = stars.movie_id WHERE name = "Kevin Bacon" AND birth = 1958)
AND name != "Kevin Bacon";