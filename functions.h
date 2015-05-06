#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "LEDColor.h"

void setLevel(int);
int getLevel();
void setIntensity(int);
int getIntensity();
void setColor(LEDColor);
LEDColor getColor();

#endif