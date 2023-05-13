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
        unsigned int h = img.info.height;
        unsigned int w = img.info.width;
        unsigned int h3 = h+h%4;
        unsigned int w3 = 3*w+w%4;
        for (int i = 0; i <h ;  i++){
            fwrite(&img.data[i], 1, w3, f);
        }

        printf("Работает!\n");


    }
    fclose(f);


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

    unsigned int h = img.info.height;
    unsigned int w = img.info.width;
    unsigned int w3 = 3*w+w%4;
    unsigned int h3 = h+h%4;
    printf("%d\n", w3);
    img.data = (RGB**)calloc(1, h* sizeof(RGB*));

    for (int i = 0; i < h  ;  i++){
        img.data[i] = (RGB*)calloc(1,w3);
        fread(&img.data[i], 1, 3*w, f);
        //unsigned char tmp ;
        //printf("%d: %d, %d, %d\n", i, img.data[i]->red, img.data[i]->green, img.data[i]->blue);
    }


    fclose(f);
    printf("*%u\n", w3*(img.info.height));
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