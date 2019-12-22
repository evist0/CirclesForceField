#ifndef RGR_COLOR_H
#define RGR_COLOR_H

/* Color.h Описывает модель и инициализацию цвета */

typedef struct {
    double red;
    double green;
    double blue;
} Color;

/* Создаёт новый цвет RGB, принимает на вход значения [0, 255] */
Color newColor(double red, double green, double blue);

/* Создаёт новый случайный цвет */
Color newRandomColor();

#endif //RGR_COLOR_H
