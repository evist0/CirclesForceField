#ifndef RGR_CIRCLESDRAW_H
#define RGR_CIRCLESDRAW_H

/* CirclesDraw.h отвечает за отрисовку шаров и отладочной информации */

#include "../CircleLogic/CirclesLogic.h"

Settings *drawSettings;

void drawText(char *text);

/* Выводит ID шара, если включена отладка */
void printCircleId(Circle *circle);
/* Рисует вектор скорости, если включена отладка */
void drawVelocityVector(Circle *circle);
/* Рисует вектор ускорения */
void drawAccelerationVector(Circle *circle);
/* Рисует поле отталкивания, если включена отладка */
void drawR0Circle(Circle *circle);

/* Рисует шар */
void drawCircle(Circle *circle);

void circlesDraw_initialize(Settings *inputSettings);

#endif //RGR_CIRCLESDRAW_H
