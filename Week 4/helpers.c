#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;

            int gray = round((red + green + blue) / 3.0);

            image[i][j].rgbtRed = gray;
            image[i][j].rgbtGreen = gray;
            image[i][j].rgbtBlue = gray;
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
            // Swap pixels at index j and (width - j - 1)
            RGBTRIPLE temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sRed = 0, sBlue = 0, sGreen = 0;
            int count = 0;

            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int newI = i + di;
                    int newJ = j + dj;

                    // Check if neighbor is within bounds
                    if (newI >= 0 && newI < height && newJ >= 0 && newJ < width)
                    {
                        sRed += temp[newI][newJ].rgbtRed;
                        sGreen += temp[newI][newJ].rgbtGreen;
                        sBlue += temp[newI][newJ].rgbtBlue;
                        count++;
                    }
                }

                image[i][j].rgbtRed = round(sRed / (float)count);
                image[i][j].rgbtGreen = round(sGreen / (float)count);
                image[i][j].rgbtBlue = round(sBlue / (float)count);
            }
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
   // Sobel kernels
    int Gx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    RGBTRIPLE temp[height][width];

    // Copy original image to temp array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRedX = 0, sumGreenX = 0, sumBlueX = 0;
            int sumRedY = 0, sumGreenY = 0, sumBlueY = 0;

            // Loop through kernel
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int newI = i + di;
                    int newJ = j + dj;

                    if (newI >= 0 && newI < height && newJ >= 0 && newJ < width)
                    {
                        // Apply Gx and Gy kernels
                        sumRedX += temp[newI][newJ].rgbtRed * Gx[di + 1][dj + 1];
                        sumGreenX += temp[newI][newJ].rgbtGreen * Gx[di + 1][dj + 1];
                        sumBlueX += temp[newI][newJ].rgbtBlue * Gx[di + 1][dj + 1];

                        sumRedY += temp[newI][newJ].rgbtRed * Gy[di + 1][dj + 1];
                        sumGreenY += temp[newI][newJ].rgbtGreen * Gy[di + 1][dj + 1];
                        sumBlueY += temp[newI][newJ].rgbtBlue * Gy[di + 1][dj + 1];
                    }
                }
            }

            // Combine the results
            int red = round(sqrt(sumRedX * sumRedX + sumRedY * sumRedY));
            int green = round(sqrt(sumGreenX * sumGreenX + sumGreenY * sumGreenY));
            int blue = round(sqrt(sumBlueX * sumBlueX + sumBlueY * sumBlueY));

            // Cap values at 255
            image[i][j].rgbtRed = (red > 255) ? 255 : red;
            image[i][j].rgbtGreen = (green > 255) ? 255 : green;
            image[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
        }
    }
}
