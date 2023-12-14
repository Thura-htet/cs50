#include "helpers.h"
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float new_pix = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
            image[i][j].rgbtRed = new_pix;
            image[i][j].rgbtGreen = new_pix;
            image[i][j].rgbtBlue = new_pix;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            float sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            float sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE reflect_pix[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            reflect_pix[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = reflect_pix[i][width - (j + 1)];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_pix[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_pix[i][j] = image[i][j];
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red, blue, green;
            int count;
            red = new_pix[i][j].rgbtRed;
            green = new_pix[i][j].rgbtGreen;
            blue = new_pix[i][j].rgbtBlue;
            count = 1;
            if (j - 1 >= 0)
            {
                red += new_pix[i][j - 1].rgbtRed;
                green += new_pix[i][j - 1].rgbtGreen;
                blue += new_pix[i][j - 1].rgbtBlue;
                count++;
            }
            if (j + 1 < width)
            {
                red += new_pix[i][j + 1].rgbtRed;
                green += new_pix[i][j + 1].rgbtGreen;
                blue += new_pix[i][j + 1].rgbtBlue;
                count++;
            }
            if (i - 1 >= 0)
            {
                red += new_pix[i - 1][j].rgbtRed;
                green += new_pix[i - 1][j].rgbtGreen;
                blue += new_pix[i - 1][j].rgbtBlue;
                count++;
            }
            if (i + 1 <= height)
            {
                red += new_pix[i + 1][j].rgbtRed;
                green += new_pix[i + 1][j].rgbtGreen;
                blue += new_pix[i + 1][j].rgbtBlue;
                count++;
            }
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                red += new_pix[i - 1][j - 1].rgbtRed;
                green += new_pix[i - 1][j - 1].rgbtGreen;
                blue += new_pix[i - 1][j - 1].rgbtBlue;
                count++;
            }
            if (i - 1 >= 0 && j + 1 < width)
            {
                red += new_pix[i - 1][j + 1].rgbtRed;
                green += new_pix[i - 1][j + 1].rgbtGreen;
                blue += new_pix[i - 1][j + 1].rgbtBlue;
                count++;
            }
            if (i + 1 <= height && j - 1 >= 0)
            {
                red += new_pix[i + 1][j - 1].rgbtRed;
                green += new_pix[i + 1][j - 1].rgbtGreen;
                blue += new_pix[i + 1][j - 1].rgbtBlue;
                count++;
            }
            if (i + 1 <= height && j + 1 < width)
            {
                red += new_pix[i + 1][j + 1].rgbtRed;
                green += new_pix[i + 1][j + 1].rgbtGreen;
                blue += new_pix[i + 1][j + 1].rgbtBlue;
                count++;
            }
            image[i][j].rgbtRed = round(red / count);
            image[i][j].rgbtGreen = round(green / count);
            image[i][j].rgbtBlue = round(blue / count);
        }
    }
    return;
}


