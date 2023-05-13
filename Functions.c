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
            img->pixels[w*(y-1)+x-1].red = 255 - img->pixels[w*(y-1)+x-1].red;
            img->pixels[w*(y-1)+x-1].green = 255 - img->pixels[w*(y-1)+x-1].green;
            img->pixels[w*(y-1)+x-1].blue = 255 - img->pixels[w*(y-1)+x-1].blue;

        }
    }


}

void black_white(Image * img,int x1, int y1, int x2, int y2 ) {
    unsigned int b_w = 0;
    unsigned int w = img->w;
    for (int y = y2; y < y1; y++) {
        for (int x = x1; x < x2; x++) {

            b_w = (img->pixels[w*(y-1)+x-1].red + img->pixels[w*(y-1)+x-1].green + img->pixels[w*(y-1)+x-1].blue) / 3;

            img->pixels[w*(y-1)+x-1].red = b_w;
            img->pixels[w*(y-1)+x-1].green = b_w;
            img->pixels[w*(y-1)+x-1].blue = b_w;
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

void resize_image(Image *image, int new_width, int new_height, RGB background, int pos_x, int pos_y) {
    unsigned int width = image->w;
    unsigned int height = image->h;
    RGB *new_image = (RGB*)malloc(sizeof(RGB)*new_width*new_height);
    for (int y = 0; y < new_height; y++) {
        for (int x = 0; x < new_width; x++) {
            int old_x = (int)((x - pos_x) * width/ new_width + pos_x);
            int old_y = (int)((y - pos_y) * height / new_height + pos_y);
            if ( old_x > width  || old_y > height) {
                new_image[y * new_width + x] = background;
            } else {
                new_image[y * new_width + x] = image->pixels[old_y * (width) + old_x];
            }
        }
    }

    image->pixels = new_image;
    image->w = new_width;
    image->h = new_height;
    image->info->image_size = (3*new_width+new_width%4)* new_height;
    image->info->width = new_width;
    image->info->height = new_height;
}