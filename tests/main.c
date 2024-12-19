#include <stdio.h>
#include "../include/bmp.h"


int main() {
    Image *img = loadBMP("bird.bmp");
    if (!img) {
        printf("Failed to load image\n");
        return 1;
    }

    grayscaleImage(img);
    saveBMP("output.bmp", img, 24);
    freeImage(img);

    printf("Image processed successfully!\n");
    return 0;
}
