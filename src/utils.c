#include "../include/structs.h"

// grayscale function
void grayscaleImage(Image *img)
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