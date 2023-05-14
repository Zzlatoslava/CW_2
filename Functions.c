//
// Created by Златослава on 02.05.2023.
//

#include "Functions.h"


void save_img (const char* filename, Image* image){

    uint8_t *buffer;

    uint32_t row_size = image->w * sizeof (RGB);
    uint32_t row_size_raw = row_size;

    if (row_size%4 != 0){
        row_size = row_size + 4-(row_size%4);
    }
    uint32_t size = row_size * image->h;

    uint32_t padding_bytes = row_size - row_size_raw;
    size_t allsize = sizeof(BMPFHeader)+sizeof(BMPInfo)+ size;
    buffer = (uint8_t*) malloc(allsize);
    memcpy(buffer, image->header, sizeof(BMPFHeader));
    memcpy(buffer + sizeof(BMPFHeader), image->info, sizeof(BMPInfo));
    uint8_t* buf = buffer + sizeof(BMPFHeader) + sizeof(BMPInfo);

    for (int y = 0; y < image->h; ++y) {
        memcpy(buf + y*row_size, ((uint8_t*)image->pixels) + y*row_size_raw, row_size_raw);
        if (padding_bytes != 0) {
            memset(buf+ y*row_size +row_size_raw, 0, padding_bytes);
        }
    }

    FILE * file = fopen(filename, "wb");
    fwrite(buffer, allsize, 1, file);
    fclose(file);

}




Image* open_img(const char* path){
    size_t size;
    uint8_t *buffer;

    FILE * file = fopen(path, "rb");
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);

    buffer = (uint8_t*) malloc(size * sizeof(uint8_t));

    fread(buffer, size, 1, file);
    fclose(file);


    BMPFHeader* header = malloc(sizeof(BMPFHeader));
    memcpy(header, buffer, sizeof(BMPFHeader));

    BMPInfo* info = malloc(sizeof (BMPInfo));
    memcpy(info, buffer + sizeof(BMPFHeader), sizeof(BMPInfo));

    uint8_t * image = malloc(sizeof(RGB) * info->width * info->height);

    uint8_t* pixel_buffer = buffer + header->bits;
    uint32_t row_size = info->width * sizeof(RGB);
    uint32_t row_size_row = row_size + info->width%4;

    for (int y = 0; y < info->height; ++y) {
        memcpy(image + y*row_size, pixel_buffer+ y*row_size_row, row_size);
    }


    Image* picture = malloc(sizeof(Image));
    picture->header = header;
    picture->info = info;
    picture->pixels = (RGB*) image;
    picture->w = info->width;
    picture->h = info->height;
    //printf("!!!!!!!!!!!\n");
    return picture;

}







void color_inversion(Image *img, int x1, int y1, int x2, int y2){
    unsigned int w = img->w;
    for (int y = y2; y <y1; y++){
        for (int x = x1; x<x2; x++){
            img->pixels[w*y+x].red = 255 - img->pixels[w*y+x].red;
            img->pixels[w*y+x].green = 255 - img->pixels[w*y+x].green;
            img->pixels[w*y+x].blue = 255 - img->pixels[w*y+x].blue;

        }
    }


}

void black_white(Image * img,int x1, int y1, int x2, int y2 ) {
    unsigned int b_w = 0;
    unsigned int w = img->w;
    for (int y = y2; y < y1; y++) {
        for (int x = x1; x < x2; x++) {

            b_w = (img->pixels[w*y+x].red + img->pixels[w*y+x].green + img->pixels[w*y+x].blue) / 3;

            img->pixels[w*y+x].red = b_w;
            img->pixels[w*y+x].green = b_w;
            img->pixels[w*y+x].blue = b_w;
        }
    }
}


void draw_line(Image * img, int x1, int y1, int x2, int y2, RGB color, int thickness ){
    unsigned int width = img->w;
    unsigned int height = img->h;
    float  dx =(float)(x2 - x1);
    float dy = (float)(y2 - y1);
    float norm = sqrt(dx*dx + dy*dy);
    dx /= norm;
    dy /= norm;

    float d = 0;
    int x = x1, y = y1;
    while ((x2 - x)*(x2 - x) + (y2 - y)*(y2 - y) > 1) {
        for (int oy = -thickness/2; oy <= thickness/2; oy++) {
            for (int ox = -thickness/2; ox <= thickness/2; ox++) {
                if (x+ox >= 0 && x+ox < width && y+oy >= 0 && y+oy < height) {
                    img->pixels[(y+oy)*width + (x+ox)] = color;
                }
            }
        }
        d += 1;
        if (d >= norm) break;
        x = x1 + (int)(dx*d);
        y = y1 + (int)(dy*d);
    }

}

void resize_image(Image *image, int new_width, int new_height, RGB background, int anchor_point) {

    RGB *new_image = (RGB*)malloc(sizeof(RGB)*new_width*new_height);
    RGB* old_image = image->pixels;
    unsigned int old_width = image->w;
    unsigned int old_height = image->h;


    int x1, x2, y1, y2;
// определить точку относительно которой производится масштабирование
    switch(anchor_point) {
        case 1:
             x1 = 0;
             x2 = new_width - 1;
             y1 = old_height -1;
             y2 = old_height - new_height;
            break;
        case 2:
            x1 = old_width-new_width;
            x2 = old_width-1;
            y1 = old_height -1;
            y2 = old_height - new_height;
            break;
        case 3:
            x1 = 0;
            x2 = new_width - 1;
            y1 = new_height -1;
            y2 = 0;
            break;
        case 4:
            x1 = old_width- new_width;
            x2 = old_width - 1;
            y1 = new_height -1;
            y2 = 0;
            break;
        case 0:
// по умолчанию центр
            x1 = 0;
            x2 = new_width - 1;
            y1 = old_height - (int)((old_height - new_height)/2)-1;
            y2 = (int)((old_height - new_height)/2);
            break;
        default:
            printf("Error!");
    }

    for( int y = 0, i = y2 ; y < y1, i< y1; y++, i++) {
        for (int x = 0, j = x1; x < x2, j < x2; x++, j++) {
                if(x1!=x2 && y1!= y2) {
                    new_image[new_width * y + x] = old_image[old_width * i + j];

                }
                   /*else{
                       new_image[new_width * y + x] = background;
                    }*/

                  }

        }
    for (int y = y1; y < new_width; y++){
        for (int x = x2; x< new_height; x++){
            new_image[new_width * y + x] = background;
        }
    }







// нарисовать старое изображение на новом с учетом масштабирования


    image->pixels = new_image;
    image->w = new_width;
    image->h = new_height;
    image->info->image_size = (3*new_width+new_width%4)* new_height;
    image->info->width = new_width;
    image->info->height = new_height;
}