# CW_2


Программа должна иметь CLI или GUI. Более подробно тут: http://se.moevm.info/doku.php/courses:programming:rules_extra_kurs


Общие сведения
24 бита на цвет
без сжатия
файл всегда соответствует формату BMP (но стоит помнить, что версий у формата несколько)
обратите внимание на выравнивание; мусорные данные, если их необходимо дописать в файл для выравнивания, должны быть нулями.
обратите внимание на порядок записи пикселей
все поля стандартных BMP заголовков в выходном файле должны иметь те же значения что и во входном (разумеется кроме тех, которые должны быть изменены).
Программа должна реализовывать весь следующий функционал по обработке bmp-файла

Инверсия цвета в заданной области. Функционал определяется
Координатами левого верхнего угла области
Координатами правого нижнего угла области


Преобразовать в Ч/Б изображение (любым простым способом). Функционал определяется
Координатами левого верхнего угла области
Координатами правого нижнего угла области
Алгоритмом, если реализовано несколько алгоритмов преобразования изображения (по желанию студента)


Изменение размера изображения с его обрезкой или расширением фона.
Функционал определяется:
Действием: увеличение или уменьшение изображения
Цветом фона при увеличении изображения
Точкой относительно которой производится действие: центр, левый верхний, правый верхний, левый нижний, правый нижний угол


Рисование отрезка. 
Отрезок определяется:
координатами начала
координатами конца
цветом
толщиной
