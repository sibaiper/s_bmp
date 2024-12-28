#include "../include/structs.h"
#include <math.h>

void pixelate(BMPImage *img, int pixel_size)
{
    if (!img || !img->data || pixel_size <= 0)
    {
        return; // handle null pointers or invalid pixel_size
    }

    // loop through the image in blocks of size `pixel_size x pixel_size`
    for (int y = 0; y < img->height; y += pixel_size)
    {
        for (int x = 0; x < img->width; x += pixel_size)
        {
            // average color for the current block
            int block_r = 0, block_g = 0, block_b = 0;
            int pixel_count = 0;

            for (int block_y = 0; block_y < pixel_size && (y + block_y) < img->height; block_y++)
            {
                for (int block_x = 0; block_x < pixel_size && (x + block_x) < img->width; block_x++)
                {
                    Pixel *pixel = &img->data[(y + block_y) * img->width + (x + block_x)];
                    block_r += pixel->r;
                    block_g += pixel->g;
                    block_b += pixel->b;
                    pixel_count++;
                }
            }

            // compute the average color
            uint8_t avg_r = block_r / pixel_count;
            uint8_t avg_g = block_g / pixel_count;
            uint8_t avg_b = block_b / pixel_count;

            // set all pixels in the block to the average color
            for (int block_y = 0; block_y < pixel_size && (y + block_y) < img->height; block_y++)
            {
                for (int block_x = 0; block_x < pixel_size && (x + block_x) < img->width; block_x++)
                {
                    Pixel *pixel = &img->data[(y + block_y) * img->width + (x + block_x)];
                    pixel->r = avg_r;
                    pixel->g = avg_g;
                    pixel->b = avg_b;
                }
            }
        }
    }
}
