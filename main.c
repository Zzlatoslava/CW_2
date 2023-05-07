
#include "Structures.h"
#include "Functions.h"



int main(){

    BMP img = open_img("./Cw_2.bmp");
    save_img("./nem_img.bmp", img);
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