#ifndef RGR_CIRCLESLOGIC_H
#define RGR_CIRCLESLOGIC_H


#include "../../../Utilities/Settings/Settings.c"
#include "../../../Utilities/TwoDimensions/TwoDimensions.h"
#include "../../../Utilities/Color/Color.h"

/* CircleLogic.h описывает модель шара, его инициализацию и действия над ним */

typedef struct {
    int _id;
    TwoDimensions centerCoordinates, velocity, acceleration;
    Color color;
    double radius;
} Circle;

Settings *logicSettings;


/* Блок Движений: */
/* Увеличивает координаты в зависимости от проекций скорости */
void integrateCoordinates(Circle *circle);
/* Увеличивает проекции скорости в зависимости от проекций ускорения */
void integrateVelocity(Circle *circle);


/* Блок Столкновений: */
/* Отрабатывает соприкосновение шарика с границами окна */
void bordersCollision(Circle *circle);

/* Отрабатывает соприкосновение шариков друг с другом */
void circlesCollision(Circle *circle1, Circle *circle2);


/* Блок Притяжения: */
/* Возвращает проекции вектора силы притяжения между fromCircle и toCircle */
TwoDimensions getGravityForce(Circle *fromCircle, Circle *toCircle);

/* Инициализирует логической части */
void circleLogic_Initialize(Settings *inputSettings);

#endif //RGR_CIRCLESLOGIC_H
