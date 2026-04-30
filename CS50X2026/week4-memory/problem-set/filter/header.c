#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j -1] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int counter = 0;
    float red = 0.0;
    float green = 0.0;
    float blue = 0.0;
    RGBTRIPLE new_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            counter = 0;
            red = green = blue = 0.0;

            for (int r = i - 1; r <= i + 1; r++)
            {
                if (r < 0 || r >= height)
                {
                    continue;
                }
                for (int c = j - 1; c <= j + 1; c++)
                {
                    if (c < 0 || c >= width)
                    {
                        continue;
                    }
                    red += image[r][c].rgbtRed;
                    green += image[r][c].rgbtGreen;
                    blue += image[r][c].rgbtBlue;
                    counter++;
                }
            }
            new_image[i][j].rgbtRed = (int) round(red / counter);
            new_image[i][j].rgbtGreen = (int) round(green / counter);
            new_image[i][j].rgbtBlue = (int) round(blue / counter);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE buffer[height][width];
    int gx[3][3] =
    {
        { -1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int gy[3][3] = 
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    float redx = 0, redy = 0;
    float bluex = 0, bluey = 0;
    float greenx = 0, greeny = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
           redx = redy = 0;
           greenx = greeny = 0;
           bluex = bluey = 0;

            for (int r = i - 1; r <= i + 1; r++)
            {
                if (r < 0 || r >= height)
                {
                    continue;
                }
                for (int c = j - 1; c <= j + 1; c++)
                {
                    if (c < 0 || c >= width)
                    {
                        continue;
                    }

                    redx += image[r][c].rgbtRed * gx[r - i + 1][c - j + 1];
                    redy += image[r][c].rgbtRed * gy[r - i + 1][c - j + 1];

                    greenx += image[r][c].rgbtGreen * gx[r -i + 1][c - j + 1];
                    greeny += image[r][c].rgbtGreen * gy[r -i + 1][c - j + 1];

                    bluex += image[r][c].rgbtBlue * gx[r -i + 1][c - j + 1];
                    bluey += image[r][c].rgbtBlue * gy[r -i + 1][c - j + 1];
                }
            }

            int red = (int) round(sqrt(redx * redx + redy * redy));
            int green = (int) round(sqrt(greenx * greenx + greeny * greeny));
            int blue = (int) round(sqrt(bluex * bluex + bluey * bluey));

            if (red > 255)
            {
                red = 255;
            }

            if (green > 255) 
            {
                green = 255;
            }

            if (blue > 255) 
            {
                blue = 255;
            }

            buffer[i][j].rgbtRed = red;
            buffer[i][j].rgbtGreen = green;
            buffer[i][j].rgbtBlue = blue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = buffer[i][j];
        }
    }
    return;
}

