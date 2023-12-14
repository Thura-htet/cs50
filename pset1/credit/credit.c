#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    //getting user input
    long long cc;
    do
    {
        cc = get_long_long("Number: ");
    }
    while (cc < 0);
    // j is the sum of the second to last digit and every other digits which are multiplied by two
    // k is the sum of the last digit and every other digit
    int j = 0;
    int k = 0;
    for (long long digit1 = 100; digit1 <= 10000000000000000; digit1 *= 100)
    {
        int i = ((cc % digit1) / (digit1 / 10)) * 2;
        // to split the numbers greater than nine to separate digits
        int n = i % 10;
        int l = ((i % 100)) / 10;
        int m = n + l;
        j += m;
    }
    for (long long digit2 = 10; digit2 <= 10000000000000000; digit2 *= 100)
    {
        int i = (cc % digit2) / (digit2 / 10);
        k += i;
    }
    // check sum
    int sum = j + k;
    if (sum % 10 == 0)
    {
        // checking credit card
        if ((cc >= 340000000000000 && cc < 350000000000000) || (cc >= 370000000000000 && cc < 380000000000000))
        {
            printf("AMEX\n");
        }
        else if (cc >= 5100000000000000 && cc < 5600000000000000)
        {
            printf("MASTERCARD\n");
        }
        else if ((cc >= 4000000000000 && cc < 5000000000000) || (cc >= 4000000000000000 && cc < 5000000000000000))
        {
            printf("VISA\n");
        }
        // invalid value for the cards that have the check sum ending with zero but not belonging to any of the above companies
        else
        {
            printf("INVALID\n");
        }
    }
    // invalid value for cards whose check sum does not end with zero
    else
    {
        printf("INVALID\n");
    }
}
