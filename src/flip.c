#include "../include/structs.h"

// flip vertical function:
void vertical_flip(BMPImage *img)
{
    if (!img || !img->data)
    {
        return; //handle null pointer
    }

    int width = img->width;
    int height = img->height;

    // Iterate over each row
    for (int y = 0; y < height; y++)
    {
        //pointers to the start and end of the current row
        Pixel *row_start = &img->data[y * width];
        Pixel *row_end = &img->data[y * width + width - 1];

        //swap pixels in the row symmetrically
        while (row_start < row_end)
        {
            Pixel temp = *row_start;
            *row_start = *row_end;
            *row_end = temp;

            row_start++;
            row_end--;
        }
    }
}

// flip horizontal function:
void horizontal_flip(BMPImage *img)
{
    if (!img || !img->data)
    {
        return; //handle null pointer
    }

    int width = img->width;
    int height = img->height;

    //loop over each row
    for (int y = 0; y < height / 2; y++)
    {

        //pointers to the top row and bottom row
        Pixel *top_row = &img->data[y * width];
        Pixel *bottom_row = &img->data[(height - y - 1) * width];

        // swap pixels between the top and bottom rows
        int x = 0; //column index
        while (x < width)
        {
            Pixel temp = top_row[x];
            top_row[x] = bottom_row[x];
            bottom_row[x] = temp;

            x++;
        }
    }
}

// flip a region vertically
void regional_vertical_flip(BMPImage *img, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    if (!img || !img->data || x1 >= x2 || y1 >= y2 || x2 > img->width || y2 > img->height)
    {
        return; // invalid input / null pointer
    }

    int width = img->width;

    //loop over half the rows in the region
    for (int top = y1, bottom = y2 - 1; top < bottom; top++, bottom--)
    {
        //swap rows top and bottom
        for (int x = x1; x < x2; x++)
        {
            Pixel temp = img->data[top * width + x];
            img->data[top * width + x] = img->data[bottom * width + x];
            img->data[bottom * width + x] = temp;
        }
    }
}

// flip a region horizontally
void regional_horizontal_flip(BMPImage *img, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    if (!img || !img->data || x1 >= x2 || y1 >= y2 || x2 > img->width || y2 > img->height)
    {
        return; // invalid input / null pointer
    }

    int width = img->width;

    //loop over rows in the specified region
    for (int y = y1; y < y2; y++)
    {
        //get a pointer to the current row
        Pixel *row = &img->data[y * width];

        //flip pixels inside the region (horizontally)
        for (int left = x1, right = x2 - 1; left < right; left++, right--)
        {
            Pixel temp = row[left];
            row[left] = row[right];
            row[right] = temp;
        }
    }
}
