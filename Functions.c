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







void color_inversion(Image *img, int coord_x1, int coord_y1, int coord_x2, int coord_y2){
    for (int y = coord_y1; y < coord_y2; y++){
        for (int x = coord_x1; x< coord_x2; x++){
            img->pixels[h*w*3].red = 255 - img->pixels[h*w*3].red;
            img->pixels[h*w*3].green = 255 - img->pixels[h*w*3].green;
            img->pixels[h*w*3].blue = 255 - img->pixels[h*w*3].blue;

        }
    }


}

/*void black_white(BMP * img,int coord_x1, int coord_y1, int coord_x2, int coord_y2 ) {
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