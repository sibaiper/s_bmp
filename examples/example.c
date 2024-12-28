#include "../include/structs.h"
#include "../include/bmp.h"
#include <stdio.h>


int main()
{

    BMPImage *img = load_bmp("bird.bmp");
    if (!img)
    {
        printf("Failed to load image\n");
        return 1;
    }

    
    //flip regionally:
    regional_horizontal_flip(img, 25, 25, 200, 200);
    
    //invert the image colors:
    //invert_image(img);

    //sepia the image:
    // sepia_image(img);

    
    //blur the image (gaussian blur): kernel_size between 3 and 15? 
    // gaussian_blur(img, 3, 1.5);
    // gaussian_blur(img, 7, 10.5);


    //brightness the image:
    // brightness(img, -10);


    //simple 1 specific color replacement (oldColor, newColor):
    // replace_color_simple(img, (Color){255, 255, 255}, (Color){0, 0, 0});


    //complex replace color with threshold:
    //replace_similar_colors(img, (Pixel){35,66,17}, (Pixel){0, 0, 0}, 50);

    
    //contrast
    // contrast(img, 1.1f);

    //gamma correctio
    // gamma_correction(img, 1.1f);

    //pixelate the image:
    // pixelate(img, 20);

    //box blur
    // box_blur(img, 20);

    //sharpen the image:
    // sharpen(img, 1);

    //save the image:
    save_bmp("output.bmp", img, 24);
    
    //cleanup:
    free_image(img);

    printf("Image processed successfully!\n");
    return 0;
}