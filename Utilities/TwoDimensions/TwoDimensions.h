#ifndef RGR_TWODIMENSIONS_H
#define RGR_TWODIMENSIONS_H

/* TwoDimensions.h описывает кортеж длиной 2 */
/* TwoDimensions - это всё, что можно разложить на 2 составляющие */
/* Точка, вектор */

typedef struct {
    double x;
    double y;
} TwoDimensions;

TwoDimensions createEmpty();

/* Возвращает дистанцию между двумя точками */
double calculateDistance(TwoDimensions from, TwoDimensions to);

/* Приравнивает все элементы кортежа к "value */
TwoDimensions equate(TwoDimensions term, double value);

/* Складывает между собой два кортежа */
TwoDimensions sumValues(TwoDimensions term1, TwoDimensions term2);

#endif //RGR_TWODIMENSIONS_H
