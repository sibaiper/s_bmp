#include "../include/structs.h"
#include <math.h>

int int_clamp(int value, int min, int max)
{
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }
    else
    {
        return value;
    }
}

// grayscale function
void grayscale_image(BMPImage *img)
{
    if (!img || !img->data)
    {
        return; // handle null pointer
    }

    // loop through all pixels in the image
    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            Pixel *pixel = &img->data[y * img->width + x];       // access pixel
            uint8_t gray = (pixel->r + pixel->g + pixel->b) / 3; // average the RGB values
            pixel->r = pixel->g = pixel->b = gray;               // set to grayscale
        }
    }
}

// sepia function
void sepia_image(BMPImage *img)
{
    if (!img || !img->data)
    {
        return; // handle null pointer
    }

    // loop through all pixels in the image
    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            Pixel *pixel = &img->data[y * img->width + x]; // access pixel

            // calculate new RGB values using int for intermediate results
            int newRed = (int)((pixel->r * .393) + (pixel->g * .769) + (pixel->b * .189));
            int newGreen = (int)((pixel->r * .349) + (pixel->g * .686) + (pixel->b * .168));
            int newBlue = (int)((pixel->r * .272) + (pixel->g * .534) + (pixel->b * .131));

            // clamp values to the range 0–255
            pixel->r = newRed > 255 ? 255 : (newRed < 0 ? 0 : newRed);
            pixel->g = newGreen > 255 ? 255 : (newGreen < 0 ? 0 : newGreen);
            pixel->b = newBlue > 255 ? 255 : (newBlue < 0 ? 0 : newBlue);
        }
    }
}

// invert function
void invert_image(BMPImage *img)
{
    if (!img || !img->data)
    {
        return; // handle null pointer
    }

    // loop through all pixels in the image
    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            Pixel *pixel = &img->data[y * img->width + x]; // access pixel

            // invert RGB values
            pixel->r = 255 - pixel->r;
            pixel->g = 255 - pixel->g;
            pixel->b = 255 - pixel->b;
        }
    }
}

void brightness(BMPImage *img, int value)
{
    if (!img || !img->data)
    {
        return; // handle null pointer
    }

    // loop through all pixels in the image
    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            Pixel *pixel = &img->data[y * img->width + x]; // access pixel

            // add value to RGB values and clamp to the range 0-255
            pixel->r = int_clamp(pixel->r + value, 0, 255);
            pixel->g = int_clamp(pixel->g + value, 0, 255);
            pixel->b = int_clamp(pixel->b + value, 0, 255);
        }
    }
}

void contrast(BMPImage *img, float value)
{
    if (!img || !img->data)
    {
        return; // handle null pointer
    }

    // loop through all pixels in the image
    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            Pixel *pixel = &img->data[y * img->width + x]; // access pixel


            //calculate the new RGB values using the formula:
            //new_value = (value * (old_value - 128)) + 128
            pixel->r = int_clamp((value * (pixel->r - 128 )) + 128, 0, 255);
            pixel->g = int_clamp((value * (pixel->g - 128 )) + 128, 0, 255);
            pixel->b = int_clamp((value * (pixel->b - 128 )) + 128, 0, 255);
        }
    }
}

void gamma_correction(BMPImage *img, float value)
{
    if (!img || !img->data)
    {
        return; // handle null pointer
    }

    // loop through all pixels in the image
    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            Pixel *pixel = &img->data[y * img->width + x]; // access pixel

            // calculate the new RGB values using the formula:
            // new_value = 255 * pow(old_value / 255, 1 / value)
            pixel->r = int_clamp(255 * pow(pixel->r / 255.0, 1 / value), 0, 255);
            pixel->g = int_clamp(255 * pow(pixel->g / 255.0, 1 / value), 0, 255);
            pixel->b = int_clamp(255 * pow(pixel->b / 255.0, 1 / value), 0, 255);
        }
    }
}