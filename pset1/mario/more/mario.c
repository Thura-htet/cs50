#include <cs50.h>
#include <stdio.h>

int get_h(string prompt);

// print out the blocks
int main(void)
{
    int h = get_h("Height: ");
    for (int i = 1; i <= h; i++)
    {
        for (int k = i; k < h; k++)
        {
            printf(" ");
        }
        for (int j = (h-i); j < h; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int l = (h-i); l < h; l++)
        {
            printf("#");
        }
        printf("\n");
    }
}
// gettig user input
int get_h(string prompt)
{
    int height;
    do
    {
        height = get_int("%s", prompt);
    }
    while (height < 1 || height > 8);
    return height;
}
