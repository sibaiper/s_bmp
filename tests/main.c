#include <stdio.h>
#include "../include/bmp.h"


int main() {
    BMPImage *img = load_bmp("bird.bmp");
    if (!img) {
        printf("Failed to load image\n");
        return 1;
    }

    grayscale_image(img);
    save_bmp("output.bmp", img, 24);
    free_image(img);

    printf("Image processed successfully!\n");
    return 0;
}
