
#include "Structures.h"
#include "Functions.h"
#include <unistd.h>
#include <getopt.h>



int main(int argc, char *argv[]){
    Image* img = open_img("1.bmp");
    RGB color=  {17, 36, 128};
    resize_image(img, 700,900, color, 1);
    save_img("./new_img.bmp", img);
    printf("\n-------------------------------------------------------\n"
             "------Обработка bmp-файла------\n\n"
             "1.Инверсия цвета в заданной области  -i -invert\n"
             "2.Преобразование в Ч/Б заданной области  -b  -black\n"
             "3.Изменение размера изображения   -r  -resize\n"
             "4.Рисование отрезка  -l  -line\n"
             "-------------------------------------------------------\n\n");

    const char* short_options = "hs::f:";

    const struct option long_options[] = {
            { "help", no_argument, NULL, 'h' },
            { "size", optional_argument, NULL, 's' },
            { "file", required_argument, NULL, 'f' },
            { NULL, 0, NULL, 0 }
    };

    int rez;
    int option_index;

    while ((rez=getopt_long(argc,argv,short_options,
                            long_options,&option_index))!=-1){

        switch(rez){
            case 'h': {
                printf("This is demo help. Try -h or --help.\n");
                printf("option_index = %d (\"%s\",%d,%c)\n",
                       option_index,
                       long_options[option_index].name,
                       long_options[option_index].has_arg,
                       long_options[option_index].val
                );
                break;
            };
            case 's': {
                if (optarg!=NULL)
                    printf("found size with value %s\n",optarg);
                else
                    printf("found size without value\n");
                break;
            };

            case 'f': {
                printf("file = %s\n",optarg);
                break;
            };
            case '?': default: {
                printf("found unknown option\n");
                break;
            };
        };
    };
    return 0;
};





    /*
        Image* img = open_img("1.bmp");
    color_inversion(img, 10, 50, 50, 10);
    //black_white(img, 50, 700, 400,50);
   // color_inversion(img, 200, 700, 550,50);
    RGB color = {99, 155, 133};

    //draw_line(img, 10, 50, 50, 10, color, 2 );
    draw_line(img,200, 700, 550,50, color, 10 );
    //resize_image(img, 300,400, color, 2);
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
    }*/




    /*case 'h': {
                printf("-----------------------------------------------------------\n");
                printf("%s\n", optarg);
                if(strcmp (optarg, " i")==0 || strcmp (optarg, " invert")==0 ) {
                    printf("Инверсия цвета области задается:\n"
                           "Путь к изображению(img)\n"
                           "Координатами левого верхнего и правого нижнего углов( (x1, y1), (x2, y2) )\n"
                           "-i img x1 y1 x2 y2\n"
                    );
                }
                else if (strcmp (optarg, " b")==0 || strcmp (optarg, " black") == 0){
                    printf("Преобразование области в Ч/Б задается:\n"
                           "Путь к изображению(img)\n"
                           "Координатами левого верхнего и правого нижнего углов( (x1, y1), (x2, y2) )\n"
                           "-b/-black img x1 y1 x2 y2\n"
                    );

                }
                else if (strcmp (optarg, "l")==0 || strcmp (optarg, "line") == 0){
                    printf("Рисование отрезка задается:\n"
                           "Путь к изображению(img)\n"
                           "Координатами начала (x1, y1)\n"
                           "Координатами конца (x2, y2)\n"
                           "Цветом отрезка (color):\n"
                           "                Возможные цвета: red, pink, purple\n"
                           "Толщиной (thickness)"
                           "-l/-line img x1 y1 x2 y2 color thickness\n"
                    );

                }
                else if (strcmp (optarg, "r")==0 || strcmp (optarg, "resize") == 0){
                    printf("Изменение размера изображения задается:\n"
                           "Путь к изображению(img)\n"
                           "Новой шириной изображения(width)\n"
                           "Новой высотой изображения(height)\n"
                           "Цветом при расширении (color):\n"
                           "                Возможные цвета: red, pink, purple\n"
                           "Точкой относительно которой производится действие(point):\n"
                           "                Центр - 0\n"
                           "                Левый верхний угол - 1\n"
                           "                Правый верхний угол - 2\n"
                           "                Левый нижний угол - 3\n"
                           "                Правый нижний угол - 4\n"
                           "-r/-resize img width height color point\n"
                    );

                }
                else {
                    printf("Unknown function\n");
                }
                printf("-----------------------------------------------------------\n");
                break;
            };
            case 's': {
                if (optarg!=NULL)
                    printf("found size with value %s\n",optarg);
                else
                    printf("found size without value\n");
                break;
            };

            case 'f': {
                printf("file = %s\n",optarg);
                break;
            };
            case '?': default: {
                printf("found unknown option\n");
                break;
            };
        };*/