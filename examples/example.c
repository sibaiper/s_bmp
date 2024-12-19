#include "../include/structs.h"
#include "../include/bmp.h"
#include <stdio.h>


int main()
{

    Image *img = loadBMP("bird.bmp");
    if (!img)
    {
        printf("Failed to load image\n");
        return 1;
    }

    grayscaleImage(img);
    
    //flip regionally:
    regional_horizontal_flip(img, 25, 25, 200, 200);
    
    saveBMP("output.bmp", img, 24);
    freeImage(img);

    printf("Image processed successfully!\n");
    return 0;
}