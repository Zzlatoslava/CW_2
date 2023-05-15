
#include "Functions.h"
#include <unistd.h>
#include <getopt.h>



int main(int argc, char *argv[]){
    int num_func;
    char* file_name;
    char * str;
    char* str_end;
    int x1, x2, y1, y2;
    RGB color = choice_color(3);
    int thick;
    int point;
    char* write;
    int width;
    int height;

    Image* img = open_img("1.bmp");
    resize_image(img, 600,900, color, 1);
    save_img("new.bmp", img);


    int c ;

    while (1){
        static struct option long_opt[] = {
                {"help",   1, 0, 'h'},
                {"invert", 0, 0, 'i'},
                {"black",  0, 0, 'b'},
                {"resize", 0, 0, 'r'},
                {"line",   0, 0, 'l'},
                {"start",  1, 0, 's'},
                {"end",    1, 0, 'e'},
                {"color",  1, 0, 'c'},
                {"file",   1, 0, 'f'},
                {"thick",  1, 0, 't'},
                {"point",  1, 0, 'p'},
                {"write",  1, 0, 'w'},
                {"value",  1, 0, 'v'},

                {0,        0, 0, 0}
        };
        int optIdx;

        if((c = getopt_long(argc, argv, "ibrl hsecftpevw:", long_opt, &optIdx)) == -1)
            break;
        switch (c) {
            case 'h': {
                printf("-----------------------------------------------------------\n");
                if (strcmp(optarg, "i") == 0 || strcmp(optarg, "invert") == 0) {
                    printf("Инверсия цвета области задается:\n"
                           "Путь к изображению(img)\n"
                           "Координатами левого верхнего и правого нижнего углов( (x1, y1), (x2, y2) )\n"
                           "-i/--invert img x1 y1 x2 y2\n"
                    );
                } else if (strcmp(optarg, "b") == 0 || strcmp(optarg, "black") == 0) {
                    printf("Преобразование области в Ч/Б задается:\n"
                           "Путь к изображению(img)\n"
                           "Координатами левого верхнего и правого нижнего углов( (x1, y1), (x2, y2) )\n"
                           "-b/--black img x1 y1 x2 y2\n"
                    );

                } else if (strcmp(optarg, "l") == 0 || strcmp(optarg, "line") == 0) {
                    printf("Рисование отрезка задается:\n"
                           "Путь к изображению(img)\n"
                           "Координатами начала (x1, y1)\n"
                           "Координатами конца (x2, y2)\n"
                           "Цветом отрезка (color):\n"
                           "                Возможные цвета: red, pink, purple\n"
                           "Толщиной (thick)"
                           "-l/--line img x1 y1 x2 y2 color thick\n"
                    );

                } else if (strcmp(optarg, "r") == 0 || strcmp(optarg, "resize") == 0) {
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
                           "-r/--resize img width height color point\n"
                    );

                } else {
                    printf("Unknown function\n");
                }
                printf("-----------------------------------------------------------\n");
                return (-1);
            };
            case 'i':
                printf("Инверсия цвета в заданной области\n");
                num_func = 1;
                break;
            case 'b':
                printf("Преобразование в Ч/Б заданной области\n");
                num_func = 2;
                break;
            case 'r':
                printf("Изменение размера изображения\n");
                num_func = 3;
                break;
            case 'l':
                printf("Рисование отрезка\n");
                num_func = 4;
                break;
            case 's':

                x1 =  atoi(optarg[optIdx]);
                y1 =  atoi(optarg[optIdx+1]);
                printf("%d %d\n", x1,y1);
                break;
            case 'e':
                str = optarg;
                x2 = (int) strtol(str, &str_end, 10);
                y2 = (int) strtol(str_end, NULL, 10);

                break;
            case 'c':
                if (strcmp(optarg, "red") == 0)
                    color = choice_color(1);
                else if (strcmp(optarg, "pink") == 0)
                    color = choice_color(2);
                else if (strcmp(optarg, "purple") == 0)
                    color = choice_color(3);
                else {
                    printf("Неверный цвет\n");
                    return (-1);
                }
                break;
            case 'f':
                if (optarg != NULL) {
                    file_name = optarg;
                } else {
                    printf("Неверное название файла 1\n");
                    //printf("%d\n", optarg);
                    return (-1);
                }
            case 't':
                str = optarg;
                thick = (int) strtol(str, NULL, 10);
                if (thick <= 0) {
                    printf("Толщина должна быть больше 0.\n");
                    return (-1);
                }
            case 'p':
                str = optarg;
                point = (int) strtol(str, NULL, 10);
                if (point < 0 || point > 5) {
                    printf("Неверное значение для точки.\n");
                    return (-1);
                }

            case 'w':
                write = optarg;
                if (write == NULL) {
                    printf("Неверное название файла 2\n");
                    return (-1);
                }

                break;
            case 'v':
                str = optarg;
                width = (int) strtol(str, &str_end, 10);
                height = (int) strtol(str_end, NULL, 10);

            default:
                printf("Неверный параметр, воспользуйтесь справкой(-h /--help)\n");
                return (-1);
        }
    }
   //Image* img = open_img(file_name);
    switch(num_func){
        case 1:
            color_inversion(img, x1, y1, x2, y2);
            break;
        case 2:
            black_white(img, x1, y1, x2, y2);
            break;
        case 3:
            resize_image(img, width,height,color, point );
            break;
        case 4:
            draw_line(img, x1,y1,x2,y2, color , thick);
            break;
        default:
            printf("Error!\n");
    }

    //save_img(write, img);
    return 0;



}





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


        }
    }
     }





    Image* img = open_img("1.bmp");
    RGB color=  {17, 36, 128};
    resize_image(img, 800,900, color, 1);
    save_img("new.bmp", img);
    }*/




    /*static struct option long_opt[] = {
                {"help",   1, 0, 'h'},
                {"invert", 0, 0, 'i'},
                {"black",  0, 0, 'b'},
                {"resize", 0, 0, 'r'},
                {"line",   0, 0, 'l'},
                {"start",  1, 0, 's'},
                {"end",    1, 0, 'e'},
                {"color",  1, 0, 'c'},
                {"file",   1, 0, 'f'},
                {"thick",  1, 0, 't'},
                {"point",  1, 0, 'p'},
                {"write",  1, 0, 'w'},
                {"value",  1, 0, 'v'},

                {0,        0, 0, 0}
        };
     *
     *
     *
     *
     *
     * switch (c) {
                case 'h': {
                    printf("-----------------------------------------------------------\n");
                    if (strcmp(optarg, "i") == 0 || strcmp(optarg, "invert") == 0) {
                        printf("Инверсия цвета области задается:\n"
                               "Путь к изображению(img)\n"
                               "Координатами левого верхнего и правого нижнего углов( (x1, y1), (x2, y2) )\n"
                               "-i/--invert img x1 y1 x2 y2\n"
                        );
                    } else if (strcmp(optarg, "b") == 0 || strcmp(optarg, "black") == 0) {
                        printf("Преобразование области в Ч/Б задается:\n"
                               "Путь к изображению(img)\n"
                               "Координатами левого верхнего и правого нижнего углов( (x1, y1), (x2, y2) )\n"
                               "-b/--black img x1 y1 x2 y2\n"
                        );

                    } else if (strcmp(optarg, "l") == 0 || strcmp(optarg, "line") == 0) {
                        printf("Рисование отрезка задается:\n"
                               "Путь к изображению(img)\n"
                               "Координатами начала (x1, y1)\n"
                               "Координатами конца (x2, y2)\n"
                               "Цветом отрезка (color):\n"
                               "                Возможные цвета: red, pink, purple\n"
                               "Толщиной (thick)"
                               "-l/--line img x1 y1 x2 y2 color thick\n"
                        );

                    } else if (strcmp(optarg, "r") == 0 || strcmp(optarg, "resize") == 0) {
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
                               "-r/--resize img width height color point\n"
                        );

                    } else {
                        printf("Unknown function\n");
                    }
                    printf("-----------------------------------------------------------\n");
                    return (-1);
                };
                case 'i':
                    printf("Инверсия цвета в заданной области\n");
                    num_func = 1;
                    break;
                case 'b':
                    printf("Преобразование в Ч/Б заданной области\n");
                    num_func = 2;
                    break;
                case 'r':
                    printf("Изменение размера изображения\n");
                    num_func = 3;
                    break;
                case 'l':
                    printf("Рисование отрезка\n");
                    num_func = 4;
                    break;
                case 's':
                    str = optarg;
                    x1 = (int) strtol(str, &str_end, 10);
                    y1 = (int) strtol(str_end, NULL, 10);
                    break;
                case 'e':
                    str = optarg;
                    x2 = (int) strtol(str, &str_end, 10);
                    y2 = (int) strtol(str_end, NULL, 10);

                    break;
                case 'c':
                    if (strcmp(optarg, "red") == 0)
                        color = choice_color(1);
                    else if (strcmp(optarg, "pink") == 0)
                        color = choice_color(2);
                    else if (strcmp(optarg, "purple") == 0)
                        color = choice_color(3);
                    else {
                        printf("Неверный цвет\n");
                        return (-1);
                    }
                    break;
                case 'f':
                    if (optarg != NULL) {
                        file_name = optarg;
                    } else {
                        printf("Неверное название файла 1\n");
                        //printf("%d\n", optarg);
                        return (-1);
                    }
                case 't':
                    str = optarg;
                    thick = (int) strtol(str, NULL, 10);
                    if (thick <= 0) {
                        printf("Толщина должна быть больше 0.\n");
                        return (-1);
                    }
                case 'p':
                    str = optarg;
                    point = (int) strtol(str, NULL, 10);
                    if (point < 0 || point > 5) {
                        printf("Неверное значение для точки.\n");
                        return (-1);
                    }

                case 'w':
                    write = optarg;
                    if (write == NULL) {
                        printf("Неверное название файла 2\n");
                        return (-1);
                    }

                    break;
                case 'v':
                    str = optarg;
                    width = (int) strtol(str, &str_end, 10);
                    height = (int) strtol(str_end, NULL, 10);

                default:
                    printf("Неверный параметр, воспользуйтесь справкой(-h /--help)\n");
                    return (-1);
            };*/