#include "Functions.h"

RGB choice_color(int choice){


    if (choice == 1) {
        RGB color = {50, 68, 247};//red
        return color;
    }
    else if(choice == 2) {
        RGB color = {182, 95, 255};//pink
        return color;
    }
    else if (choice == 3){
        RGB color = {184, 48, 132};//purple
        return color;}
    else {
        RGB color = {0,0,0};
        return color;
    }



}


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
    if (file == NULL ){
        printf("Ошибка в названии файла для записи. Повторите попытку\n");
        exit(1);
    }
    fwrite(buffer, allsize, 1, file);
    fclose(file);
    free(buffer);

}




Image* open_img(const char* path){
    size_t size;
    uint8_t *buffer;

    FILE * file = fopen(path, "rb");
    if (file == NULL ){
        printf("Ошибка в названии файла для считывания. Повторите попытку\n");
        exit(1);
    }
    fseek(file, 0, SEEK_END);
    size = ftell(file);
    rewind(file);

    buffer = (uint8_t*) malloc(size * sizeof(uint8_t));

    fread(buffer, size, 1, file);
    fclose(file);


    BMPFHeader* header = malloc(sizeof(BMPFHeader));
    memcpy(header, buffer, sizeof(BMPFHeader));
    if(header->type[0] != 'B' && header->type[0] != 'M'){
        printf("Вы используете не bmp-файл.\n");
        exit(1);
    }


    BMPInfo* info = malloc(sizeof (BMPInfo));
    memcpy(info, buffer + sizeof(BMPFHeader), sizeof(BMPInfo));
    if (info->header_size != 40){
        printf("Неподдерживаемая версия bmp-файла. Используйте только 3 версию.\n");
        exit(1);
    }

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
    return picture;

}



void color_inversion(Image *img, int x1, int y1, int x2, int y2){
    if (img->info->width < x1 || img->info->width < x2 || img->info->height < y1 || img->info->height < y2){
        printf ("Координаты больше размера изображения, попробуйте изменить параметры\n");
        free(img);
        exit(1);
    }
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
    if (img->info->width < x1 || img->info->width < x2 || img->info->height < y1 || img->info->height < y2){
        printf ("Координаты больше размера изображения, попробуйте изменить параметры\n");
        free(img);
        exit(1);
    }
    unsigned int b_w;
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



void resize_image(Image *image, int new_width, int new_height, int anchor_point, RGB color) {

    RGB *new_image = (RGB*)malloc(3*(new_width+new_width%4)* new_height);
    RGB* old_image = image->pixels;
    unsigned int old_width = image->w;
    unsigned int old_height = image->h;
    for( int y = 0 ; y < new_height; y++){
        for (int x = 0; x < new_width; x++){
            new_image[new_width*y+x] = color;
        }
    }
    int offsetX = 0;
    int offsetY = 0;
    if (anchor_point == 3) {
        offsetX = 0;
        offsetY = 0;
    } else if (anchor_point == 4) {
        offsetX = new_width - old_width;
        offsetY = 0;
    } else if (anchor_point == 1) {
        offsetX = 0;
        offsetY = new_height - old_height;
    } else if (anchor_point == 2) {
        offsetX = new_width - old_width;
        offsetY = new_height - old_height;
    } else if (anchor_point == 0 ){
        offsetX = abs(new_width - old_width)/2;
        offsetY = abs(new_height - old_height)/2;
    }
    else{
        printf("Неверно выбрана точка, воспользуйтесь справкой(-h /--help)\n");
        free(image);
        exit(1);
    }

    for (int y = 0; y < old_height; y++) {
        for (int x = 0; x < old_width; x++) {
            int newX = x + offsetX;
            int newY = y + offsetY;
            if (newX >= 0 && newX < new_width && newY >= 0 && newY < new_height) {
                new_image[newY * new_width + newX] = old_image[y * old_width + x];
            }
        }
    }



    image->pixels = new_image;
    image->w = new_width;
    image->h = new_height;
    image->info->image_size = 3*(new_width+new_width%4)* new_height;
    image->info->width = new_width;
    image->info->height = new_height;
}


void draw_line(Image * img, int x1, int y1, int x2, int y2, RGB color, int thickness ){
    if (img->info->width < x1 || img->info->width < x2 || img->info->height < y1 || img->info->height < y2){
        printf ("Координаты больше размера изображения, попробуйте изменить параметры\n");
        free(img);
        exit(1);
    }
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
