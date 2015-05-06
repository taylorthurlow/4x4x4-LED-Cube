#include "Arduino.h"
#include "Tlc5940.h"
#include "LEDColor.h"

LEDColor currentColor = white;
int intensityArray[] = {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4,
		4, 4, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9, 10,
		10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 19,
		19, 20, 21, 21, 22, 23, 23, 24, 25, 26, 27, 27, 28, 29, 30, 31, 32, 33, 35, 36,
		37, 38, 39, 41, 42, 43, 45, 46, 48, 49, 51, 53, 54, 56, 58, 60, 62, 64, 66, 68,
		71, 73, 75, 78, 80, 83, 86, 89, 91, 95, 98, 101, 104, 108, 111, 115, 119, 123,
		127, 131, 135, 140, 144, 149, 154, 159, 164, 170, 175, 181, 187, 193, 200, 206,
		213, 220, 227, 235, 243, 251, 259, 267, 276, 285, 295, 304, 314, 325, 336, 347,
		358, 370, 382, 395, 408, 421, 435, 450, 464, 480, 496, 512, 529, 546, 564, 583,
		602, 622, 643, 664, 686, 709, 732, 756, 781, 807, 834, 861, 890, 919, 949, 981,
		1013, 1046, 1081, 1117, 1154, 1192, 1231, 1272, 1314, 1357, 1402, 1448, 1496,
		1545, 1596, 1649, 1704, 1760, 1818, 1878, 1940, 2004, 2070, 2139, 2209, 2282,
		2358, 2435, 2516, 2599, 2685, 2774, 2865, 2960, 3057, 3158, 3263, 3371, 3482,
		3597, 3716, 3838, 3965, 4095};
		/**
		 * Values for this array are calculated so that there are 256 individual values
		 * (not necessarily unique values) that scale logarithmically from 0 to 4095. This
		 * accounts for the non-linearity of the provided tlc5940 scale of LED brightness,
		 * as the lower ranges from 0-2000 seemed to have a significantly larger effect
		 * on total brightness as compared to the values from 2000-4095. The logarithmic
		 * scaling should help make the brightness value have a more linear effect.
		 */
int currentIntensity = 4095;
int currentLevel = 0;

/**
 * Sets the current vertical LED plane to be manipulated. Each layer
 * consists of 16 LEDs.
 * @param level - The level to switch to - valid input [0,3].
 */
void setLevel(int level) {

	if(level >= 0 && level <= 3) {
		for (int i = 4; i <= 7; i++) {
			// Due to the use of PNP transistors in the MOSFETs, setting the pin HIGH will
			// result in the pin being turned off. LOW will enable the layer.
			digitalWrite(i, HIGH);
		}

		setLevel(level);

		switch(currentLevel) {
			case 0:
				digitalWrite(4, LOW);
				break;
			case 1:
				digitalWrite(5, LOW);
				break;
			case 2:
				digitalWrite(6, LOW);
				break;
			case 3:
				digitalWrite(7, LOW);
				break;
			default:
				break;
		}
	} else {
		setLevel(0);
	}
}

/**
 * Gets the current value of currentLevel.
 * @return currentLevel, [0,3]
 */
int getLevel() {
	return currentLevel;
}

/**
 * Sets the intensity level according to the logarithmically scaled values pre-determined
 * by intensityArray[]. Input checks for a valid range, and sets to full brightness
 * otherwise.
 * @param intensity - Value of [1,256] which corresponds (more or less) linearly to the
 * brightness of enabled LEDs.
 */
void setIntensity(int intensity) {
	if (intensity >= 1 && intensity < 256) {
		currentIntensity = intensityArray[intensity];
	} else {
		currentIntensity = intensityArray[255];
	}
}

/**
 * Gets the current value of currentIntensity.
 * @return currentIntensity, [0, 4095]
 */
int getIntensity() {
	return currentIntensity;
}

/**
 * Sets the current selected LED color to the selected color that is included in the enum
 * LEDColor. Choices are red, green, blue, cyan, magenta, yellow, and white.
 * @param color - The LEDColor enum object to set to the current color.
 */
void setColor(LEDColor color) {
	currentColor = color;
}

/**
 * Gets the current LED color setting.
 * @return currentColor, {white, cyan, magenta, yellow, red, green, blue}
 */
LEDColor getColor() {
	return currentColor;
}