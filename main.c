#include <Gl/freeglut.h>
#include <stdbool.h>

#include "CircleService/CircleService.h"

/* Настройки */
Settings settings = {
        .screenResolution = {800, 600},
        .minRadius = 25, //Минимальный радиус случайного шара, px;
        .maxRadius = 50, //Максимальный радиус случайного шара, px;
        .amountSegments = 100, //Количество полигонов у шара;
        .delay = 20, //Задержка между кадрами, мс;
        .debugDelayRatio = 1.5, //Множитель замедления в режиме отладки;
        .R0 = 50, //Надбавка к радиусу шара для поля отталкивания, px;
        .R0Ratio = 50, //Во сколько раз отталкивание сильнее притяжения;
        .G = 10, //Гравитационная постоянная
        .circlesAmount = 5, // Количество шаров
        .isDebug = false //Включить режим отладки при запуске
};

void Keyboard(unsigned char key, int mouseX, int mouseY) {
    switch (key) {
        case 'a': // A = Добавить шар (Add)
            circleService_createCircle();
            break;
        case 'd': // D = удалить шар (Delete)
            circleService_delete(-1);
            break;
        case 'r': // R = Перегенерировать шары (Reset)
            circleService_reset();
            break;
        case 'v': // V = Сбросить скорость (Velocity)
            circleService_resetVelocities();
            break;
        case 's': // S = Включить отладку (Super mode)
            circleService_switchDebug();
            break;
        case '\033': // ESC = Выйти
            exit(0);
        default:
            return;
    }
}

void Mouse(int button, int state, int mouseX, int mouseY) {
    TwoDimensions mouseClickPoint = {mouseX, mouseY};
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        circleService_createCircleAtPoint(mouseClickPoint);
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        circleService_deleteAtPoint(mouseClickPoint);
}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT);

    circleService_CallDraw();

    glutSwapBuffers();
}

void Reshape(GLint w, GLint h) {
    settings.screenResolution.x = w;
    settings.screenResolution.y = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, h, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
}

void Idle() {
    glutTimerFunc(settings.delay, Idle, 0);

    circleService_CallCalculate();

    glutPostRedisplay();
}

int main(int argc, char *argv[]) {

    circleService_Initialize(&settings);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize((int)settings.screenResolution.x, (int)settings.screenResolution.y);
    glutCreateWindow("CircleService");

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    glutKeyboardFunc(Keyboard);
    glutMouseFunc(Mouse);
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutTimerFunc(settings.delay, Idle, settings.delay);

    glutMainLoop();

}