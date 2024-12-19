#include "../include/structs.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

Image *loadBMP(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (!file)
    {
        perror("Failed to open file");
        return NULL;
    }

    // read BMP header
    struct BMPHeader bmpHeader;
    fread(&bmpHeader, sizeof(struct BMPHeader), 1, file);

    // read DIB header
    struct DIBHeader dibHeader;
    fread(&dibHeader, sizeof(struct DIBHeader), 1, file);

    // validate the BMP signature ("BM")
    if (bmpHeader.type != 0x4D42)
    {
        fprintf(stderr, "Not a valid BMP file.\n");
        fclose(file);
        return NULL;
    }

    // only support uncompressed BMPs
    if (dibHeader.compression != 0)
    {
        fprintf(stderr, "Only uncompressed BMP files are supported.\n");
        fclose(file);
        return NULL;
    }

    // extract width and height (little-endian)
    int width = *(int *)&dibHeader.width;
    int height = *(int *)&dibHeader.height;

    // allocate memory for the image
    Image *img = (Image *)malloc(sizeof(Image));
    img->width = dibHeader.width;
    img->height = dibHeader.height;
    img->data = (Pixel *)malloc(width * height * sizeof(Pixel));

    if (dibHeader.bitCount == 24)
    {
        // seek to the pixel data (offset from fileHeader)
        int pixelDataOffset = *(int *)&bmpHeader.offset;
        fseek(file, pixelDataOffset, SEEK_SET);

        // read pixel data (BMP stores rows bottom-to-top)
        int rowSize = (3 * width + 3) & ~3; // each row is padded to 4-byte boundary
        unsigned char *row = (unsigned char *)malloc(rowSize);

        for (int y = 0; y < height; y++)
        {
            fread(row, sizeof(unsigned char), rowSize, file);
            for (int x = 0; x < width; x++)
            {
                int i = (height - 1 - y) * width + x; // bottom-to-top ordering
                img->data[i].b = row[x * 3 + 0];
                img->data[i].g = row[x * 3 + 1];
                img->data[i].r = row[x * 3 + 2];
            }
        }

        free(row);
    }
    else if (dibHeader.bitCount == 8)
    {
        // handle 8-bit BMPs
        int paletteSize = 1 << dibHeader.bitCount; // 2^bitCount entries in the palette
        struct RGBQuad *palette = (struct RGBQuad *)malloc(paletteSize * sizeof(struct RGBQuad));
        fread(palette, sizeof(struct RGBQuad), paletteSize, file);

        // allocate memory for grayscale image data
        img->data = (Pixel *)malloc(img->width * img->height * sizeof(Pixel));

        int rowSize = (dibHeader.width + 3) & ~3; // row size is padded to 4-byte boundary
        unsigned char *row = (unsigned char *)malloc(rowSize);

        fseek(file, bmpHeader.offset, SEEK_SET);
        for (int y = 0; y < img->height; y++)
        {
            fread(row, sizeof(unsigned char), rowSize, file);
            for (int x = 0; x < img->width; x++)
            {
                int i = (img->height - 1 - y) * img->width + x; // BMP rows are stored bottom-to-top
                unsigned char paletteIndex = row[x];
                img->data[i].r = palette[paletteIndex].red;
                img->data[i].g = palette[paletteIndex].green;
                img->data[i].b = palette[paletteIndex].blue;
            }
        }
        free(row);
        free(palette);
    }

    fclose(file);
    return img;
}

void saveBMP(const char *filename, const Image *img, uint16_t bitCount)
{
    FILE *file = fopen(filename, "wb");
    if (!file)
    {
        perror("Failed to open file for writing");
        return;
    }

    // prepare BMP Header
    struct BMPHeader bmpHeader = {0};
    bmpHeader.type = 0x4D42; // 'BM'
    bmpHeader.offset = sizeof(struct BMPHeader) + sizeof(struct DIBHeader);

    // add the palette size to the offset IF the image is being saved to 8 bit
    if (bitCount == 8)
    {
        bmpHeader.offset += 256 * sizeof(struct RGBQuad); // Include palette size for 8-bit BMP
    }

    // if its 24 bits, means every pixel is 3 bytes: so u do 3 * width. else the color is 1 byte so its directly just width. and then the + 3 & ~3 to ensure its multiples of 4 (for padding)
    int rowSize = (bitCount == 24) ? (3 * img->width + 3) & ~3 : (img->width + 3) & ~3;
    bmpHeader.fileSize = bmpHeader.offset + rowSize * img->height;

    fwrite(&bmpHeader, sizeof(struct BMPHeader), 1, file);

    // prepare DIB Header
    struct DIBHeader dibHeader = {0};
    dibHeader.headerSize = sizeof(struct DIBHeader);
    dibHeader.width = img->width;
    dibHeader.height = img->height;
    dibHeader.planes = 1;
    dibHeader.bitCount = bitCount;
    dibHeader.compression = 0;
    dibHeader.imageSize = rowSize * img->height;

    fwrite(&dibHeader, sizeof(struct DIBHeader), 1, file);

    if (bitCount == 8)
    {
        // write grayscale palette
        for (int i = 0; i < 256; i++)
        {
            struct RGBQuad color = {i, i, i, 0};
            fwrite(&color, sizeof(struct RGBQuad), 1, file);
        }
    }

    // write pixel data
    unsigned char *row = (unsigned char *)malloc(rowSize);
    for (int y = 0; y < img->height; y++)
    {
        for (int x = 0; x < img->width; x++)
        {
            int i = (img->height - 1 - y) * img->width + x; // bottom-to-top ordering
            if (bitCount == 24)
            {
                row[x * 3 + 0] = img->data[i].b;
                row[x * 3 + 1] = img->data[i].g;
                row[x * 3 + 2] = img->data[i].r;
            }
            else if (bitCount == 8)
            {
                row[x] = img->data[i].r; // use red as grayscale intensity
            }
        }
        fwrite(row, sizeof(unsigned char), rowSize, file);
    }

    free(row);
    fclose(file);
}

void freeImage(Image *img)
{
    if (img)
    {
        free(img->data);
        free(img);
    }
}