//
// Created by Златослава on 02.05.2023.
//

#include "Functions.h"



void save_img (const char* path, BMP img ){
    FILE *f = fopen(path , "wb");
    if (f == NULL) {
        printf("Unable to open image\n");

    }
    fwrite(&img.file_header, 1, sizeof(img.file_header), f);
    fwrite(&img.info, 1, sizeof(img.info), f);
    for (int i = 0; i < sizeof(img.info.height);  i++){
        fwrite(&img.data[i], 1, sizeof(img.data)*((img.info.height*3-3)&(-4)), f);
    }
    fclose(f);
    printf("Работает!\n");
}

BMP open_img (const char* path){
    BMP img;
    FILE *f = fopen(path, "rb");
    if (f == NULL) {
        printf("Unable to open image\n");

    }
    else{
        printf("Image is open\n");
    }
    fread(&img.file_header, 1, sizeof(img.file_header), f);
    if (img.file_header.type[0] != 19778 && img.file_header.type[0] != 9805) {
        printf("Invalid BMP file\n");


    }
    fread(&img.info, 1, sizeof(img.info), f);

    img.data = (RGB**)malloc(sizeof(RGB*)*((img.info.height*3-3)&(-4)));
    for (int i = 0; i < sizeof(img.info.height);  i++){
        img.data[i] = (RGB*)malloc(sizeof(RGB)*(img.info.width));
        fread(&img.data[i], 1, sizeof(img.data)*img.info.width, f);
    }


    fclose(f);

    return img;
}


void color_inversion(BMP *img, int coord_x1, int coord_y1, int coord_x2, int coord_y2){
    for (int i = coord_y1; i < coord_y2; i++){
        for (int j = coord_x1; j< coord_x2; j++){
            img->data[i][j].red = 255 - img->data[i][j].red;
            img->data[i][j].green = 255 - img->data[i][j].green;
            img->data[i][j].blue = 255 - img->data[i][j].blue;
        }
    }
    //return img;
}