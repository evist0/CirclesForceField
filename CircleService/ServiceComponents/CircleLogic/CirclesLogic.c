/* Circle.h описывает модель шара, его инициализацию и действия над ним */

#include <math.h>
#include <stdio.h>

#include "../../../Utilities/Settings/Settings.c"
#include "../../../Utilities/TwoDimensions/TwoDimensions.h"
#include "../../../Utilities/Color/Color.h"


typedef struct {
    int _id;
    TwoDimensions centerCoordinates, velocity, acceleration;
    Color color;
    double radius;
} Circle;
Settings *logicSettings;


/* Блок Движений: */
/* Увеличивает координаты в зависимости от проекций скорости */
void integrateCoordinates(Circle *circle) {
    circle->centerCoordinates = sumValues(circle->centerCoordinates, circle->velocity);
}
/* Увеличивает проекции скорости в зависимости от проекций ускорения */
void integrateVelocity(Circle *circle) {
    circle->velocity = sumValues(circle->velocity, circle->acceleration);
}


/* Блок Столкновений: */
/* Отрабатывает соприкосновение шарика с границами окна */
void bordersCollision(Circle *circle) {
    /* Левая граница */
    if (circle->centerCoordinates.x - circle->radius < 0) {
        if (logicSettings->isDebug)
            printf("Circe_%d hit left border \n", circle->_id);
        circle->velocity.x /= -2;
        circle->centerCoordinates.x = 0 + circle->radius;
    }

    /* Правая граница */
    if (circle->centerCoordinates.x + circle->radius > logicSettings->screenResolution.x) {
        if (logicSettings->isDebug)
            printf("Circe_%d hit right border \n", circle->_id);
        circle->velocity.x /= -2;
        circle->centerCoordinates.x = logicSettings->screenResolution.x - circle->radius;
    }

    /* Верхняя граница */
    if (circle->centerCoordinates.y - circle->radius < 0) {
        if (logicSettings->isDebug)
            printf("Circe_%d hit top border \n", circle->_id);
        circle->velocity.y /= -2;
        circle->centerCoordinates.y = 0 + circle->radius;
    }

    /* Нижняя граница */
    if (circle->centerCoordinates.y + circle->radius > logicSettings->screenResolution.y) {
        if (logicSettings->isDebug)
            printf("Circe_%d hit down border \n", circle->_id);
        circle->velocity.y /= -2;
        circle->centerCoordinates.y = logicSettings->screenResolution.y - circle->radius;
    }
}

/* Отрабатывает соприкосновение шариков друг с другом */
/* Не используется */
void circlesCollision(Circle *circle1, Circle *circle2) {
    double minDistance = circle1->radius + circle2->radius;
    double curDistance = calculateDistance(circle1->centerCoordinates, circle2->centerCoordinates);

    if (curDistance < minDistance)
        if (logicSettings->isDebug)
            printf("Collision between Circle_%d and Circle_%d \n", circle1->_id, circle2->_id);
}


/* Блок Притяжения: */
/* Возвращает проекции вектора силы притяжения между fromCircle и toCircle */
TwoDimensions getGravityForce(Circle *fromCircle, Circle *toCircle) {
    /* Расстояние между шарами */
    double distance = calculateDistance(fromCircle->centerCoordinates, toCircle->centerCoordinates);

    /* Расстояние, с которого начнётся отталкивание */
    double R0distance = 2 * logicSettings->R0 + fromCircle->radius + toCircle->radius;

    /* Если расстояние между шарами меньше, чем расстояние отталкивания, то инвертируем силу */
    double inverseMultiplier = distance < R0distance ? -(logicSettings->R0Ratio) : 1;
    //double powMultiplier = distance < R0distance ?  logicSettings.R0Ratio : 2;

    /* Вычисляем модуль угла между шарами */
    double dX = toCircle->centerCoordinates.x - fromCircle->centerCoordinates.x;
    double dY = toCircle->centerCoordinates.y - fromCircle->centerCoordinates.y;
    double angle = fabs(atan(dY / dX));

    /* Вычисляем направление силы */
    int xDirection = dX < 0 ? -1 : 1;
    int yDirection = dY < 0 ? -1 : 1;

    /* Вычисляем модуль силы */
    double absForce = (inverseMultiplier * logicSettings->G * toCircle->radius) / (pow(distance, 2));

    /* Вычисляем проекции силы притяжения на оси координат */
    TwoDimensions gravityForce = {absForce * cos(angle) * xDirection, absForce * sin(angle) * yDirection};

    return gravityForce;
}


/* Инициализирует логической части */
void circleLogic_Initialize(Settings *inputSettings){
    logicSettings = inputSettings;
}