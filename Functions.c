//
// Created by Златослава on 02.05.2023.
//

#include "Functions.h"

void save_img (const char* path, BMP img ){
    FILE *f = fopen(path, "wb");
    if (f == NULL) {
        printf("Invalid file path\n");
    }
    else{

        fwrite(&img.file_header, 1, sizeof(img.file_header), f);
        fwrite(&img.info, 1, sizeof(img.info), f);
        //img.info.image_size = img.info.height*img.info.width*3;

        for (int i = 0; i <img.info.height ;  i++){
            fwrite(&img.data[i], 1, sizeof(RGB)*img.info.width+img.info.width%4, f);
        }

        printf("Работает!\n");


    }
    fclose(f);
    printf("%d   %d\n", img.info.width, img.info.width&(4));

}


BMP open_img(const char* path){
    BMP img;
    FILE *f = fopen(path, "rb");
    if (f == NULL) {
        printf("Unable to open image\n");

    }
    else{
        printf("Image is open\n");
    }
    fread(&img.file_header, 1, sizeof(img.file_header), f);
    if (img.file_header.type[0] != 'B' && img.file_header.type[0] != 'M'){
        printf("Invalid BMP file\n");
        return img;
    }
    fread(&img.info, 1, sizeof(img.info), f);
    printf("%u\n", img.info.image_size);


    img.data = (RGB**)malloc(img.info.height* sizeof(RGB*));

    for (int i = img.info.height-1; i >= 0 ;  i--){
        img.data[i] = (RGB*)malloc(sizeof(RGB)*img.info.width+img.info.width%4);
        fread(&img.data[i], 1, sizeof(RGB)*img.info.width, f);
    }


    fclose(f);
    printf("*%u\n", (3*img.info.width+img.info.width%4)*(img.info.height));
    return img;

    }







/*void color_inversion(BMP *img, int coord_x1, int coord_y1, int coord_x2, int coord_y2){
    for (int i = coord_y1; i < coord_y2; i++){
        for (int j = coord_x1; j< coord_x2; j++){
            img->data[i][j].red = 255 - img->data[i][j].red;
            img->data[i][j].green = 255 - img->data[i][j].green;
            img->data[i][j].blue = 255 - img->data[i][j].blue;
        }
    }
    //return img;
}

void black_white(BMP * img,int coord_x1, int coord_y1, int coord_x2, int coord_y2 ) {
    unsigned int b_w = 0;
    for (int i = coord_y1; i < coord_y2; i++) {
        for (int j = coord_x1; j < coord_x2; j++) {

            b_w = (img->data[i][j].red + img->data[i][j].green + img->data[i][j].blue) / 3;

            img->data[i][j].red = b_w;
            img->data[i][j].green = b_w;
            img->data[i][j].blue = b_w;
        }
    }
}*/