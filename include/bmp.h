#ifndef BMP_H
#define BMP_H

#include "structs.h"
#include <stdint.h>

//function declarations
Image *loadBMP(const char *filename);
void freeImage(Image *img);
void saveBMP(const char *filename, const Image *img, uint16_t bitCount);
void grayscaleImage(Image *img);
void vertical_flip(Image *img);
void horizontal_flip(Image *img);
void regional_vertical_flip(Image *img, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void regional_horizontal_flip(Image *img, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

#endif // BMP_H
