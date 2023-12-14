#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s. \n", argv[1]);
        return  2;
    }
    FILE *img = NULL;

    unsigned char buffer[512];
    char filename[8];
    int i = 0;
    while (fread(buffer, 512, 1, inptr) == 1)
    {

        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (img == NULL)
            {
                sprintf(filename, "%03i.jpg", i);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
                i++;
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", i);
                img = fopen(filename, "w");
                fwrite(buffer, 1, 512, img);
                i++;
            }
        }
        else
        {
            if (img != NULL)
            {
                fopen(filename, "a");
                fwrite(buffer, 1, 512, img);
            }
        }
    }
    fclose(inptr);
    fclose(img);
    return 0;
}