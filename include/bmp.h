#ifndef BMP_H
#define BMP_H

#include "structs.h"
#include <stdint.h>

// function declarations
BMPImage *load_bmp(const char *filename);
void free_image(BMPImage *img);
void save_bmp(const char *filename, const BMPImage *img, uint16_t bitCount);
void grayscale_image(BMPImage *img);
void vertical_flip(BMPImage *img);
void horizontal_flip(BMPImage *img);
void regional_vertical_flip(BMPImage *img, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void regional_horizontal_flip(BMPImage *img, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void sepia_image(BMPImage *img);
void invert_image(BMPImage *img);
float **create_gaussian_kernel(int size, float sigma);
void gaussian_blur(BMPImage *img, int kernel_size, float sigma);
void box_blur(BMPImage *img, int pixel_size);
void int_clamp(int value, int min, int max);
void brightness(BMPImage *img, int value);
void replace_color_simple(BMPImage *img, Color oldColor, Color newColor);
int color_distance_squared(Pixel c1, Pixel c2);
void replace_similar_colors(BMPImage *img, Pixel oldColor, Pixel newColor, int threshold);
void contrast(BMPImage *img, float value);
void gamma_correction(BMPImage *img, float value);
void pixelate(BMPImage *img, int pixel_size);
void sharpen(BMPImage *image, int strength);

#endif // BMP_H
