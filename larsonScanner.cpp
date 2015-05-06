#include "Arduino.h"
#include "larsonScanner.h"
#include "functions.h"
#include "Tlc5940.h"

/**
 * The larson scanner is an iterator which tests each LED. It iterates through each
 * layer, and on each layer, it goes through each LED, in each color, once. Useful
 * for testing hardware, and making sure LEDs are functioning properly.
 */

void larsonScanner() {
	Serial.println("Start larsonScanner()");
	Tlc.clear();
	int direction = 1;
	int dir = 1;

	for (int i = 0; i <= 3; i += dir) {

		Serial.println("iterate layer");

		if (i == 3) dir = -1;
		if (i == 0) dir = 1;

		setLevel(i);

		for (int channel = 0; channel < (3 * 16); channel += direction) {

			Tlc.clear();

			if (channel == 0) {
				direction = 1;
			} else {
				Tlc.set(channel - 1, 0);
			}

			Tlc.set(channel, getIntensity());

			if (channel != ((3 * 16) - 1)) {
				Tlc.set(channel + 1, 0);
			} else {
				//direction = -1;
			}

			Tlc.update();
			delay(10);
		}

	}
	Serial.println("End larsonScanner()");
}