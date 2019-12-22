/* TwoDimensions.h описывает кортеж длиной 2 */
/* TwoDimensions - это всё, что можно разложить на 2 составляющие */
/* Точка, вектор */

#include <math.h>

typedef struct {
    double x;
    double y;
} TwoDimensions;

TwoDimensions createEmpty(){
    TwoDimensions result = {0, 0};
    return result;
}

/* Возвращает дистанцию между двумя точками */
double calculateDistance(TwoDimensions from, TwoDimensions to) {
    double distance = sqrt(pow(from.x - to.x, 2) + pow(from.y - to.y, 2));
    return distance;
}

/* Приравнивает все элементы кортежа к "value */
TwoDimensions equate(TwoDimensions term, double value){
    TwoDimensions result;

    result.x = value;
    result.y = value;

    return result;
}

/* Складывает между собой два кортежа */
TwoDimensions sumValues(TwoDimensions term1, TwoDimensions term2) {
    TwoDimensions result;

    result.x = term1.x + term2.x;
    result.y = term1.y + term2.y;

    return result;
}