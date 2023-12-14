// ask the user the amount of change
// print the minimum number of coins
// last line of output must be the minimum number of coins possible: an integer followed by \n


#include <stdio.h>
#include <cs50.h>
#include <math.h>

//use '%' and '/'
float get_input(string prompt);

int main(void)
{
    float dollars = get_input("Change owed: ");
    int cents = round(dollars * 100);
    int count = 0;
    //int remain;
    while (cents >= 25)
    {
        cents = cents - 25;
        count++;
    }
    while (cents < 25 && cents >= 10)
    {
        cents = cents - 10;
        count++;
    }
    while (cents < 10 && cents >= 5)
    {
        cents = cents - 5;
        count++;
    } 
    while (cents < 5 && cents >= 1)
    {
        cents = cents - 1;
        count++;
    }
    printf("%i\n", count);
}


float get_input(string prompt)
{
    float input;
    do
    {
        input = get_float("%s", prompt);
    }
    while (input <= 0);
    return input;
}
