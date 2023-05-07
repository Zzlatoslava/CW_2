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
    for (int i = 0; i < sizeof(img.data); i++){
        fwrite(&img.data[i], 1, sizeof(img.data)*img.info.width, f);
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
    fread(&img.info, 1, sizeof(img.info), f);
    img.data = (RGB**)malloc(sizeof(RGB**)*img.info.height);
    for (int i = 0; i < img.info.height; i++ ){
        img.data[i] = (RGB*)malloc(sizeof(RGB*)*img.info.width);
    }
    fclose(f);
    if (img.file_header.type[0] != 'B' || img.file_header.type[1] != 'M') {
        printf("Invalid BMP file\n");

    }
    return img;
}
