
#ifndef CW_2_FUNCTIONS_H
#define CW_2_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"
#include <stdint.h>
#include <math.h>
#include <string.h>


RGB choice_color(int choice);
void save_img (const char* filename, Image* image);
Image* open_img (const char* path);
void color_inversion(Image *img, int x1, int y1, int x2, int y2);
void black_white(Image * img,int x1, int y1, int x2, int y2 );
void draw_line(Image * img, int x1, int y1, int x2, int y2, RGB color, int thickness );
void resize_image(Image *image, int new_width, int new_height, int anchor_point, RGB color);

#endif //CW_2_FUNCTIONS_H
