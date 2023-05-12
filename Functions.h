//
// Created by Златослава on 02.05.2023.
//

#ifndef CW_2_FUNCTIONS_H
#define CW_2_FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include "Structures.h"
#include <stdint.h>
#include <math.h>


void save_img (const char* path, BMP img );
BMP open_img (const char* path);
/*void color_inversion(BMP *img, int coord_x1, int coord_y1, int coord_x2, int coord_y2);
void black_white(BMP * img,int coord_x1, int coord_y1, int coord_x2, int coord_y2 );*/

#endif //CW_2_FUNCTIONS_H
