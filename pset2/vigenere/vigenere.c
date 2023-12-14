#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int shift(char c);

int main(int argc, string argv[])
{
    bool check;
    for (int i = 0; i < argc; i++)
    {
        for (int j = 0, n = strlen(argv[i]); j < n; j++)
        {
            check = isalpha(argv[i][j]);
        }
    }
    
    if (check == true && argc == 2)
    {        
        string p_txt = get_string("plaintext: ");        
        printf("ciphertext: ");
        string k = argv[1];
        int k_len = strlen(k);
        for (int i = 0, j = 0, n = strlen(p_txt); i < n; i++)
        {                
            int key = shift(argv[1][j % k_len]);
            if islower(p_txt[i])
            {
                printf("%c", (((p_txt[i] - 97) + key) % 26) + 97);
                j++;
            }
            else if isupper(p_txt[i])
            {
                printf("%c", (((p_txt[i] - 65) + key) % 26) + 65);
                j++;
            }
            else 
            {
                printf("%c", p_txt[i]);
            }                               
        }
        printf("\n");
        return 0;
    }
    else 
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
}

int shift(char c)
{
    if (isalpha(c))
    {
        c = tolower(c) - 'a';
    }
    return c;
}
