#include "Arduino.h"
#include "Tlc5940.h"
#include "LEDColor.h"

LEDColor currentColor = white;
int intensityArray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
	19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39,
	40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 55, 56, 57, 58, 59, 61, 62,
	63, 65, 66, 68, 69, 70, 72, 74, 75, 77, 78, 80, 82, 84, 85, 87, 89, 91, 93, 95, 97, 
	99, 101, 104, 106, 108, 110, 113, 115, 118, 120, 123, 125, 128, 131, 134, 137, 140, 
	143, 146, 149, 152, 155, 159, 162, 166, 169, 173, 177, 181, 184, 188, 192, 197, 201, 
	205, 210, 214, 219, 224, 228, 233, 238, 244, 249, 254, 260, 265, 271, 277, 283, 289, 
	295, 302, 308, 315, 322, 328, 336, 343, 350, 358, 366, 373, 382, 390, 398, 407, 416, 
	425, 434, 443, 453, 462, 472, 483, 493, 504, 515, 526, 537, 549, 561, 573, 585, 598, 
	611, 624, 637, 651, 665, 680, 694, 709, 725, 740, 756, 773, 789, 806, 824, 842, 860, 
	878, 897, 917, 937, 957, 977, 999, 1020, 1042, 1065, 1088, 1111, 1135, 1160, 1185, 
	1210, 1237, 1263, 1291, 1319, 1347, 1376, 1406, 1436, 1467, 1499, 1531, 1565, 1598, 
	1633, 1668, 1704, 1741, 1779, 1817, 1856, 1897, 1937, 1979, 2022, 2066, 2110, 2156, 
	2203, 2250, 2299, 2349, 2399, 2451, 2504, 2558, 2614, 2670, 2728, 2787, 2847, 2909, 
	2971, 3036, 3101, 3168, 3237, 3307, 3378, 3451, 3526, 3602, 3680, 3759, 3841, 3924, 
	4008, 4095}
		/**
		 * Values for this array are calculated so that there are 256 individual unique
		 * valuesthat scale logarithmically from 0 to 4095. This
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