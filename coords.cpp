/*
#include "Arduino.h"
#include "led.h"

led grid[3][3][3];

void loopGrid() {
	for (int x = 0; x <= 3; x++) {
		for (int y = 0; y <= 3; y++) {
			for (int z = 0; z <= 3; z++) {
				led newLed;
				setLedColor(newLed, white);
				setLedIntensity(newLed, 256);
				grid[x][y][z] = newLed;
			}
		}
	}
}
*/