#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //printf("%i, %i, %i. \n", image[i][j].rgbtBlue, image[i][j].rgbtGreen, image[i][j].rgbtRed);
            //printf("index: %i\n", j);
            //sum the values and calculate the average
            float total = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            float avg = total / 3;
            //assign the value to each pixel
            image[i][j].rgbtBlue = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtRed = round(avg);
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
            float sepiared = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            //check for cap
            if (sepiared > 255)
            {
                sepiared = 255;
            }
            float sepiagreen =  0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            //capcheck
            if (sepiagreen > 255)
            {
              sepiagreen = 255;
            }

            float sepiablue =  0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;
             //capcheck
             if ( sepiablue > 255)
             {
                sepiablue = 255;
             }


            //assign each value to the pixel
            image[i][j].rgbtBlue = round(sepiablue);
            image[i][j].rgbtGreen = round(sepiagreen);
            image[i][j].rgbtRed = round(sepiared);

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //divide in half the image.
    int half = round(width / 2);

    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < half; j++)
        {
            //printf("%i\n", j);
            //store the value in a temporary variable
            int tempb = image[i][j].rgbtBlue;
            int tempg = image[i][j].rgbtGreen;
            int tempr = image[i][j].rgbtRed;
            //lp stands for last pixel, and represent the last index of the array
            int lp = width - 1;

            // switch the value from left with the right one
            image[i][j].rgbtBlue = image[i][lp - j].rgbtBlue;
            image[i][j].rgbtGreen = image[i][lp - j].rgbtGreen;
            image[i][j].rgbtRed = image[i][lp - j].rgbtRed;

            // switch the value from right to the left using the temp variable
            image[i][lp - j].rgbtBlue = tempb;
            image[i][lp - j].rgbtGreen = tempg;
            image[i][lp - j].rgbtRed = tempr;

        }
    }
    return;
}

//prototype for bluring
int checkPixel(int i, int j, int height, int width);

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Create a copy of the image
    RGBTRIPLE new_image[height][width];
    
    //initial loop for pixel choice
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //storing variables
            int totalR = 0;
            int totalG = 0;
            int totalB = 0;
            int validPixels = 0;
            //inner loop, calculate the value of the selected pixel
            for (int li = i - 1; li <= i + 1; li++)
            {
                for (int lj = j - 1; lj <= j + 1; lj++)
                {
                    if (checkPixel(li, lj, height, width))
                    {
                        //check for validity
                        validPixels++;
                        //add the value to a total
                        totalR += image[li][lj].rgbtRed;
                        totalG += image[li][lj].rgbtGreen;
                        totalB += image[li][lj].rgbtBlue;
                    }
                }
            }
            
            //store the value in a new image.
            new_image[i][j].rgbtRed = round((float) totalR / validPixels);
            new_image[i][j].rgbtGreen = round((float) totalG / validPixels);
            new_image[i][j].rgbtBlue = round((float) totalB / validPixels);
             
            //end of j for loop   
        }
        //end of i for loop
    }
    
    //place every pixel in the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }
    return;
}

int checkPixel(int i, int j, int height, int width)
{
    if (i >= 0 && i < height && j >= 0 && j < width)
    {
        //return true
        return 1;
    }
    else
    {
        //return false
        return 0;
    }
}