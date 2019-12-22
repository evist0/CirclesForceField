/* CircleService.h отвечает за добавление/удаление шариков */
/* За вызов функции отрисовки и просчёта шариков */

#include "stdlib.h"
#include "stdio.h"

#include "ServiceComponents/CircleLogic/CirclesLogic.h"
#include "ServiceComponents/CirclesDraw/CirclesDraw.h"

Circle *circles;
Settings *serviceSettings;

int idCounter = 0;

double getRandomRadius() {
    return logicSettings->minRadius + rand() % (logicSettings->maxRadius - logicSettings->minRadius + 1);
}

/* Конструкторы структур */
Circle newCircle(TwoDimensions coordinates, double radius) {
    Circle circle;

    circle._id = idCounter++;

    circle.centerCoordinates = coordinates;

    circle.velocity = createEmpty();
    circle.acceleration = createEmpty();

    circle.color = newRandomColor();

    circle.radius = radius;

    return circle;
}

Circle newRandomCircle() {
    Circle result;

    double radius = serviceSettings->minRadius + rand() % (serviceSettings->maxRadius - serviceSettings->minRadius + 1);

    TwoDimensions minCoordinate = {radius, radius};
    TwoDimensions maxCoordinate = sumValues(minCoordinate, serviceSettings->screenResolution);

    TwoDimensions centerCoordinate = {minCoordinate.x + rand() % (int) (maxCoordinate.x - minCoordinate.x + 1),
                                      minCoordinate.y + rand() % (int) (maxCoordinate.y - minCoordinate.y + 1)};

    return newCircle(centerCoordinate, radius);
}

Circle newRandomCircleAtPoint(TwoDimensions point) {
    return newCircle(point, getRandomRadius());
}

/* Работа с памятью */
void addMemoryForCircle() {
    if (serviceSettings->circlesAmount == 0)
        circles = malloc(sizeof(Circle) * ++serviceSettings->circlesAmount);
    else
        circles = realloc(circles, sizeof(Circle) * ++serviceSettings->circlesAmount);
}

/* Удаление шара с deleteID */
void circleService_delete(int deleteId) {
    /* Если нечего удалять */
    if (serviceSettings->circlesAmount == 0) return;

    switch (deleteId) {
        case -1: //Если вызов без ID - удаляется последний
            realloc(circles, sizeof(Circle) * --serviceSettings->circlesAmount);
            break;
        default:
            if (deleteId != circles[serviceSettings->circlesAmount - 1]._id) {
                int i = 0;

                while (circles[i]._id != deleteId)
                    i++;

                for (; i < serviceSettings->circlesAmount - 1; i++) //Удаляем сдвигом
                    circles[i] = circles[i + 1];
            }
            realloc(circles, sizeof(Circle) * --serviceSettings->circlesAmount);
            break;
    }
}

/* Удаление шара в данной точке */
void circleService_deleteAtPoint(TwoDimensions point) {
    int circleId = -1;

    for (int i = 0; i < serviceSettings->circlesAmount; i++) {
        if (calculateDistance(point, circles[i].centerCoordinates) < circles[i].radius) {
            circleId = circles[i]._id;
            break;
        }
    }

    if (circleId != -1)
        circleService_delete(circleId);
}

/* Создание случайного шара */
void circleService_createCircle() {
    addMemoryForCircle();
    circles[serviceSettings->circlesAmount - 1] = newRandomCircle();
}

/* Создаёт случаний шар в точке */
void circleService_createCircleAtPoint(TwoDimensions point) {
    addMemoryForCircle();
    circles[serviceSettings->circlesAmount - 1] = newRandomCircleAtPoint(point);
}

/* Выделяет память и заполняет её шарами */
void fillCircles() {
    circles = malloc(sizeof(Circle) * serviceSettings->circlesAmount);
    for (int i = 0; i < serviceSettings->circlesAmount; i++)
        circles[i] = newRandomCircle();
}

/* Перегенерирует шары */
void circleService_reset() {
    free(circles);
    fillCircles();
}

/* Сбрасывает скорости */
void circleService_resetVelocities() {
    for (int id = 0; id < serviceSettings->circlesAmount; id++)
        circles[id].velocity = equate(circles[id].velocity, 0);
}

void circleService_switchDebug() {
    serviceSettings->isDebug = !serviceSettings->isDebug;
}

/* Вызывает отрисовку шаров */
void circleService_CallDraw() {
    for (int id = 0; id < serviceSettings->circlesAmount; id++)
        drawCircle(&circles[id]);
}

/* Обрабатывает логику шаров */
void circleService_CallCalculate() {
    /* Пробегаем каждый шар */
    for (int currentCircleId = 0; currentCircleId < serviceSettings->circlesAmount; currentCircleId++) {
        /* Запоминаем текущий шар и начинаем вычислять итоговое ускорение (принцип супер позиций) */
        Circle *currentCircle = &circles[currentCircleId];
        TwoDimensions superForce = {0, 0};

        /* Пробегаем каждый шар, кроме текущего и считаем силу взаимодействия с ним */
        for (int id = 0; id < serviceSettings->circlesAmount; id++) {
            if (currentCircleId == id) continue; //Пропуск самого себя

            Circle *iteratingCircle = &circles[id]; //Запоминаем итерируемый шар

            /* Прибавляем силу между шарами к итоговой силе */
            superForce = sumValues(superForce, getGravityForce(currentCircle, iteratingCircle));

            /* Проверка столкновения шариков */
            circlesCollision(currentCircle, iteratingCircle);
        }

        /* Записываем полученную силу в ускорение */
        currentCircle->acceleration = superForce;

        /* Описывает поведение при столкновении с границами окна */
        bordersCollision(currentCircle);

        /* Описывает перемещение шара */
        integrateCoordinates(currentCircle); //Приращение координат
        integrateVelocity(currentCircle); //Приращение скорости
    }
}

/* Начальная инициализация всех составляющих */
void circleService_Initialize(Settings *inputSettings) {
    serviceSettings = inputSettings;
    circleLogic_Initialize(inputSettings);
    circlesDraw_initialize(inputSettings);

    fillCircles();
}