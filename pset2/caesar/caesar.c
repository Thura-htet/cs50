#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    bool digit;
    for (int i = 0; i < argc; i++)
    {
        for (int j = 0, n = strlen(argv[i]); j < n; j++)
        {
            digit = isdigit(argv[i][j]);
        }
    }
    if (argc == 2 && digit)
    {
        int key = atoi(argv[1]);
        string plain = get_string("plaintext: ");
        char cipher;
        printf("ciphertext: ");
        for (int i = 0, n = strlen(plain); i < n; i++)
        {
            if (isalpha(plain[i]))
            {
                if (isupper(plain[i]))
                {
                    int index = plain[i] - 65;
                    cipher = (index + key) % 26;
                    printf("%c", cipher + 65);
                }
                else if (islower(plain[i]))
                {
                    int index = plain[i] - 97;
                    cipher = (index + key) % 26;
                    printf("%c", cipher + 97);
                }
            }
            else
            {
                printf("%c", plain[i]);
            }
        }
        printf("\n");
        return 0;
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}
