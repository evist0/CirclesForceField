/* CirclesDraw.h отвечает за отрисовку шаров и отладочной информации */

#include "GL/freeglut.h"
#include "math.h"
#include "../CircleLogic/CirclesLogic.h"

Settings *drawSettings;

void drawText(char *text){
    for(int i = 0; i < strlen(text); i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
    }
}

/* Выводит ID шара, если включена отладка */
void printCircleId(Circle *circle) {
    /* Координаты надписи */
    double xTextCoordinate = circle->centerCoordinates.x + circle->radius;
    double yTextCoordinate = circle->centerCoordinates.y - circle->radius;
    int circleIdValue = circle->_id; //Создаём новую переменную, чтобы не менять ссылку.

    /* Считаем количество цифр у ID */
    int circleDigitsAmount = 0;
    while (circleIdValue % 10 != 0) {
        circleDigitsAmount++;
        circleIdValue /= 10;
    }

    glRasterPos2d(xTextCoordinate, yTextCoordinate);

    //Отрисовка постоянной надписи
    //const char *label = "ID: ";
    drawText("ID: ");

    //Динамическая надпись
    char *tmp = malloc(sizeof(char) * circleDigitsAmount);
    tmp = itoa(circle->_id, tmp, 10);

    drawText(tmp);
    free(tmp);
}
/* Рисует вектор скорости, если включена отладка */
void drawVelocityVector(Circle *circle) {
    /* delay указывается в мс., поэтому вычисляем домножение, чтобы рисовать вектор за 1 секунду */
    double pxPerSec = (double) 1000 / drawSettings->delay;
    double dx = circle->centerCoordinates.x + (circle->velocity.x * pxPerSec);
    double dy = circle->centerCoordinates.y + (circle->velocity.y * pxPerSec);

    glColor3f(0.0f, 0.0f, 1.0f);
    glLineWidth(3);

    glBegin(GL_LINES);
    glVertex2d(circle->centerCoordinates.x, circle->centerCoordinates.y);
    glVertex2d(dx, dy);
    glEnd();
}
/* Рисует вектор ускорения */
void drawAccelerationVector(Circle *circle) {
    /* delay указывается в мс., поэтому вычисляем домножение, чтобы рисовать вектор за 1 секунду */
    double pxPerSec = pow((double) 1000 / drawSettings->delay, 2);
    double dx = circle->centerCoordinates.x + (circle->acceleration.x * pxPerSec);
    double dy = circle->centerCoordinates.y + (circle->acceleration.y * pxPerSec);


    glColor3f(0.0f, 1.0f, 0.0f);
    glLineWidth(3);

    glBegin(GL_LINES);
    glVertex2d(circle->centerCoordinates.x, circle->centerCoordinates.y);
    glVertex2d(dx, dy);
    glEnd();
}
/* Рисует поле отталкивания, если включена отладка */
void drawR0Circle(Circle *circle) {
    int amountSegments = drawSettings->amountSegments;
    double x = circle->centerCoordinates.x;
    double y = circle->centerCoordinates.y;
    double radius = circle->radius + drawSettings->R0;

    glColor4f(1, 1, 1, 0.1);
    glBegin(GL_POLYGON);
    for (int i = 0; i < amountSegments; i++) {
        double angle = 3.1415926 * 2 * (float) i / (float) amountSegments;
        double dx = (float) radius * cosf((float) angle);
        double dy = (float) radius * sinf((float) angle);
        glVertex2f((float) x + dx, (float) y + dy);
    }
    glEnd();
}

/* Рисует шар */
void drawCircle(Circle *circle) {

    if (drawSettings->isDebug)
        drawR0Circle(circle);

    int amountSegments = drawSettings->amountSegments;
    double x = circle->centerCoordinates.x;
    double y = circle->centerCoordinates.y;
    double radius = circle->radius;
    Color color = circle->color;

    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_POLYGON);
    for (int i = 0; i < amountSegments; i++) {
        double angle = 3.1415926 * 2 * (float) i / (float) amountSegments;
        double dx = (float) radius * cosf((float) angle);
        double dy = (float) radius * sinf((float) angle);
        glVertex2f((float) x + dx, (float) y + dy);
    }
    glEnd();

    if (drawSettings->isDebug) {
        printCircleId(circle);
        drawVelocityVector(circle);
        drawAccelerationVector(circle);
    }
}

void circlesDraw_initialize(Settings *inputSettings){
    drawSettings = inputSettings;
}