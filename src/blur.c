#include "../include/structs.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>


#define M_PI 3.14159265358979323846

// function to create a guassian kernel
float **create_gaussian_kernel(int size, float sigma)
{
    float **kernel = (float **)malloc(size * sizeof(float *));
    for (int i = 0; i < size; i++)
    {
        kernel[i] = (float *)malloc(size * sizeof(float));
    }

    float sum = 0.0f;
    for (int x = -size / 2; x <= size / 2; x++)
    {
        for (int y = -size / 2; y <= size / 2; y++)
        {
            kernel[x + size / 2][y + size / 2] = exp(-(x * x + y * y) / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
            sum += kernel[x + size / 2][y + size / 2];
        }
    }

    // normalize the kernel
    for (int x = 0; x < size; x++)
    {
        for (int y = 0; y < size; y++)
        {
            kernel[x][y] /= sum;
        }
    }

    return kernel;
}

void gaussian_blur(BMPImage *img, int kernel_size, float sigma)
{
    if (!img || !img->data)
    {
        return; // handle null pointer
    }

    // create the gaussian kernel
    float **kernel = create_gaussian_kernel(kernel_size, sigma);

    // create a temporary buffer/image to store the blurred image
    BMPImage *tmp = (BMPImage *)malloc(sizeof(BMPImage));
    tmp->width = img->width;
    tmp->height = img->height;
    tmp->data = (Pixel *)malloc(tmp->width * tmp->height * sizeof(Pixel));

    // loop through all pixels in the image
    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            float r = 0.0f, g = 0.0f, b = 0.0f;
            for (int i = -kernel_size / 2; i <= kernel_size / 2; i++)
            {
                for (int j = -kernel_size / 2; j <= kernel_size / 2; j++)
                {
                    int xk = x + j;
                    int yk = y + i;
                    if (xk >= 0 && xk < img->width && yk >= 0 && yk < img->height)
                    {
                        Pixel *pixel = &img->data[yk * img->width + xk];
                        float weight = kernel[i + kernel_size / 2][j + kernel_size / 2];
                        r += pixel->r * weight;
                        g += pixel->g * weight;
                        b += pixel->b * weight;
                    }
                }
            }

            Pixel *pixel = &tmp->data[y * tmp->width + x];
            pixel->r = (uint8_t)r;
            pixel->g = (uint8_t)g;
            pixel->b = (uint8_t)b;
        }
    }

    // copy the blurred image back to the original image
    memcpy(img->data, tmp->data, img->width * img->height * sizeof(Pixel));

    // free the temporary image
    free(tmp->data);
    free(tmp);

    // free the gaussian kernel
    for (int i = 0; i < kernel_size; i++)
    {
        free(kernel[i]);
    }
    free(kernel);
}
