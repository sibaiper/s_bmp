#ifndef STRUCTS_H
#define STRUCTS_H


#include <stdint.h>


#pragma pack(push, 1) // Disable padding for the structures
struct BMPHeader
{
  uint16_t type;      // File type ("BM")
  uint32_t fileSize;  // File size in bytes
  uint16_t reserved1; // Reserved (must be 0)
  uint16_t reserved2; // Reserved (must be 0)
  uint32_t offset;    // Offset to the start of pixel data
};

struct DIBHeader
{
  uint32_t headerSize;      // Size of this header (40 bytes for BITMAPINFOHEADER)
  int32_t width;            // Width of the image in pixels
  int32_t height;           // Height of the image in pixels
  uint16_t planes;          // Number of color planes (must be 1)
  uint16_t bitCount;        // Bits per pixel (e.g., 24 for RGB)
  uint32_t compression;     // Compression type (0 = no compression)
  uint32_t imageSize;       // Image size (may be 0 for uncompressed images)
  int32_t xPixelsPerMeter;  // Horizontal resolution (pixels per meter)
  int32_t yPixelsPerMeter;  // Vertical resolution (pixels per meter)
  uint32_t colorsUsed;      // Number of colors used in the palette
  uint32_t importantColors; // Number of important colors
};
#pragma pack(pop)

typedef struct
{
  unsigned char r, g, b; // RGB components
} Pixel;

typedef struct
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
} Color;

typedef struct
{
  int width;
  int height;
  Pixel *data; // Array of pixels
} BMPImage;

struct RGBQuad
{
  uint8_t blue;     // Blue intensity
  uint8_t green;    // Green intensity
  uint8_t red;      // Red intensity
  uint8_t reserved; // Reserved (must be 0)
};


#endif // STRUCTS_H