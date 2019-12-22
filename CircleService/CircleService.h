#ifndef RGR_CIRCLESERVICE_H
#define RGR_CIRCLESERVICE_H

#include "ServiceComponents/CircleLogic/CirclesLogic.h"
#include "ServiceComponents/CirclesDraw/CirclesDraw.h"

void circleService_delete(int deleteId);
void circleService_deleteAtPoint(TwoDimensions point);

void circleService_reset();
void circleService_resetVelocities();

void circleService_createCircle();
void circleService_createCircleAtPoint(TwoDimensions point);

void circleService_switchDebug();

void circleService_CallDraw();
void circleService_CallCalculate();
void circleService_Initialize(Settings *inputSettings);

#endif //RGR_CIRCLESERVICE_H
