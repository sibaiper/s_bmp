#include "../include/structs.h"

void replace_color_simple(BMPImage *img, Color oldColor, Color newColor)
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

            // check if pixel color matches oldColor
            if (pixel->r == oldColor.r && pixel->g == oldColor.g && pixel->b == oldColor.b)
            {
                // replace color with newColor
                pixel->r = newColor.r;
                pixel->g = newColor.g;
                pixel->b = newColor.b;
            }
        }
    }
}

// Function to calculate squared Euclidean distance between two colors
int color_distance_squared(Pixel c1, Pixel c2)
{
    int dr = c1.r - c2.r;
    int dg = c1.g - c2.g;
    int db = c1.b - c2.b;
    return dr * dr + dg * dg + db * db;
}

// Function to replace colors similar to OldColor with NewColor
void replace_similar_colors(BMPImage *img, Pixel oldColor, Pixel newColor, int threshold)
{
    int thresholdSquared = threshold * threshold; // Compare squared distance for efficiency

    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            int index = y * img->width + x;
            Pixel currentColor = img->data[index];

            // Check if the current color is similar to oldColor
            if (color_distance_squared(currentColor, oldColor) <= thresholdSquared)
            {
                // Replace the color
                img->data[index] = newColor;
            }
        }
    }
}