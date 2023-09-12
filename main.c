
#include "Functions.h"
#include <getopt.h>



int main(int argc, char *argv[]) {
    int num_func;
    char *file_name = NULL;
    char *write = NULL;
    int x1 = -1, x2 = -1, y1 = -1, y2 = -1;
    RGB color = choice_color(4);
    int thick = -1;
    int point = -1;
    int width = -1;
    int height = -1;

    int c;

    while (1) {
        static struct option long_opt[] = { //указатель массив длинных опций
                {"help",   0, 0, 'h'},
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

        if ((c = getopt_long(argc, argv, "ibrlh s:e:c:f:t:p:v:w:", long_opt, &optIdx)) == -1)
            break;
        switch (c) {
            case 'h': {
                printf("-----------------------------------------------------------\n");
                printf("\nИнверсия цвета области задается:\n"
                       "Путь к изображению(img)\n"
                       "Координатами левого верхнего и правого нижнего углов( (x1, y1), (x2, y2) )\n"
                       "Примечание: Координаты по умолчанию равны 0\n"
                       "-i/--invert -f img -s x1 y1 -e x2 y2\n");

                printf("\nПреобразование области в Ч/Б задается:\n"
                       "Путь к изображению(img)\n"
                       "Координатами левого верхнего и правого нижнего углов( (x1, y1), (x2, y2) )\n"
                       "Примечание: Координаты по умолчанию равны 0\n"
                       "-b/--black -f img -s x1 y1 -e x2 y2\n");

                printf("\nРисование отрезка задается:\n"
                       "Путь к изображению(img)\n"
                       "Координатами начала (x1, y1)\n"
                       "Координатами конца (x2, y2)\n"
                       "Примечание: Координаты по умолчанию равны 0\n"
                       "Цветом отрезка (color):\n"
                       "                Возможные цвета: red, pink, purple(по умолчанию - черный)\n"
                       "Толщиной (thick)"
                       "-l/--line -f img -s x1 y1 -e x2 y2 -c color -t thick\n"
                );


                printf("\nОбрезка изображения задается:\n"
                       "Путь к изображению(img)\n"
                       "Новой шириной изображения(width)\n"
                       "Новой высотой изображения(height)\n"
                       "Точкой относительно которой производится действие(point):\n"
                       "                Центр - 0\n"
                       "                Левый верхний угол - 1\n"
                       "                Правый верхний угол - 2\n"
                       "                Левый нижний угол - 3\n"
                       "                Правый нижний угол - 4\n"
                       "Цветом в случае увеличения (color):\n"
                       "                Возможные цвета: red, pink, purple(по умолчанию - черный)\n"
                       "-r/--resize -f img -v width height  -p point -c color \n"

                );
                printf("Обязательно указывается файл для записи результата в формате bmp\n"
                       "-w/--write\n");
                printf("-----------------------------------------------------------\n");
                exit(1);
            }
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
                x1 = atoi(argv[optind - 1]);
                y1 = atoi(argv[optind]);

                if (x1 < 0 || y1 < 0) {
                    printf("Координаты должны быть неотрицательными.\n");
                    exit(1);
                }
                break;
            case 'e':
                x2 = atoi(argv[optind - 1]);
                y2 = atoi(argv[optind]);
                printf("x2:%d\ny2:%d\n", x2, y2);
                if (x2 < 0 || y2 < 0) {
                    printf("Координаты должны быть неотрицательными.\n");
                    exit(1);
                }
                break;
            case 'c':
                if (strcmp(optarg, "red") == 0)
                    color = choice_color(1);
                else if (strcmp(optarg, "pink") == 0)
                    color = choice_color(2);
                else if (strcmp(optarg, "purple") == 0)
                    color = choice_color(3);
                else {
                    printf("Неверный цвет, воспользуйтесь справкой(-h /--help)\n");
                    exit(1);
                }
                break;
            case 'f':
                if (optarg != NULL) {
                    file_name = optarg;

                } else {
                    printf("Неверное название файла.\n");

                    exit(1);
                }
                break;
            case 't':
                thick = atoi(argv[optind - 1]);

                if (thick <= 0) {
                    printf("Толщина должна быть больше 0.\n");
                    exit(1);
                }
                break;
            case 'p':
                point = atoi(argv[optind - 1]);

                if (point < 0 || point > 5) {
                    printf("Неверное значение для точки, воспользуйтесь справкой(-h /--help)\n");
                    exit(1);
                }
                break;

            case 'w':
                if (optarg != NULL) {
                    write = optarg;

                } else {
                    printf("Неверное название файла.\n");

                    exit(1);
                }

                break;
            case 'v':
                width = atoi(argv[optind - 1]);
                height = atoi(argv[optind]);

                if (width == -1 || height == -1){
                    printf("Не хватает аргументов для выполнения функции. Воспользуйтесь справкой(-h /--help)\n");
                    exit(1);
                }

                if (width <= 0 || height <= 0) {
                    printf("Неверное значение для ширины или длины.\n");
                    exit(1);
                }
                break;

            default:
                printf("Неверный параметр, воспользуйтесь справкой(-h /--help)\n");
                exit(1);
        }

    }

    if (file_name == NULL) {
        printf("Отсутствует название файла для считывания. Воспользуйтесь справкой(-h /--help)\n");
        exit(1);
    }

    if (write == NULL) {
        printf("Отсутствует название файла для записи. Воспользуйтесь справкой(-h /--help)\n");
        exit(1);
    }
    Image *img = open_img(file_name);

    switch (num_func) {
        case 1:
            if (x1 >= x2 || y1 <= y2   ) {
                printf("Выбран не левый верхний или правый нижний угол. Воспользуйтесь справкой(-h /--help)\n");
                free(img);
                exit(1);
            }
            color_inversion(img, x1, y1, x2, y2);
            break;
        case 2:
            if (x1 >= x2 || y1 <= y2   ) {
                printf("Выбран не левый верхний или правый нижний угол. Воспользуйтесь справкой(-h /--help)\n");
                free(img);
                exit(1);
            }
            black_white(img, x1, y1, x2, y2);
            break;
        case 3:
            if (width == -1 || height == -1 || point == -1) {
                printf("Не хватает аргументов для выполнения функции. Воспользуйтесь справкой(-h /--help)\n");
                free(img);
                exit(1);
            }
            resize_image(img, width, height, point, color);
            break;
        case 4:
            if (x1 >= x2 || y1 <= y2   ) {
                printf("Выбран не левый верхний или правый нижний угол. Воспользуйтесь справкой(-h /--help)\n");
                free(img);
                exit(1);
            }
            draw_line(img, x1, y1, x2, y2, color, thick);
            break;
        default:
            printf("Не выбрана функция обработки, воспользуйтесь справкой(-h /--help)!\n");
            free(img);
            exit(1);

    }

    save_img(write, img);
    free(img);
    return 0;
}