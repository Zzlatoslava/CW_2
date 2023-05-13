
#include "Structures.h"
#include "Functions.h"



int main(){

    Image* img = open_img("./1.bmp");
    color_inversion(img, 10, 50, 50, 10);
    //black_white(img, 50, 700, 400,50);
   // color_inversion(img, 200, 700, 550,50);
    RGB color = {39, 201, 99};

    //draw_line(img, 10, 50, 50, 10, color, 2 );
    draw_line(img,200, 700, 550,50, color, 2 );
    resize_image(img, 100,100, color, 150, 150);
    save_img("./new_img.bmp", img);
    int choice = 0;
    while (choice != 0) {
        switch (choice) {
            case 1:
                //first_func();
                break;
            case 2:
                //second_func();
                break;
            case 3:
                //third_func();
                break;
            case 4:
                //fourth_func();
                break;
            default:
                printf("Wrong choice, enter a different value\n");

        }
    }
    return 0;
}