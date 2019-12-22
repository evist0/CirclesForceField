/* Color.h Описывает модель и инициализацию цвета */

#include "stdlib.h"

typedef struct {
    double red;
    double green;
    double blue;
} Color;

/* Создаёт новый цвет RGB, принимает на вход значения [0, 255] */
Color newColor(double red, double green, double blue) {
    Color result;

    /* Конвертирует значения в диапазон [0, 1] для работы в OpenGL */
    result.red = red / 255;
    result.green = green / 255;
    result.blue = blue / 255;

    return result;
}

/* Создаёт новый случайный цвет */
Color newRandomColor() {
    double red = rand() % (int) (256);
    double green = rand() % (int) (256);
    double blue = rand() % (int) (256);

    return newColor(red, green, blue);
}