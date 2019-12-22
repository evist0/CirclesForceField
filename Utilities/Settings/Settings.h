#ifndef RGR_SETTINGS_H
#define RGR_SETTINGS_H

#include <stdbool.h>
#include "../TwoDimensions/TwoDimensions.h"

/* Settings.h Описывает структуру настроек */

typedef struct {
    TwoDimensions screenResolution;

    int amountSegments;
    int minRadius, maxRadius;

    int delay;
    double debugDelayRatio;

    double R0, R0Ratio, G;

    int circlesAmount;

    bool isDebug;
} Settings;

#endif //RGR_SETTINGS_H
