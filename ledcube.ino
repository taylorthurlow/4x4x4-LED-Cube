#include "Tlc5940.h"
#include "larsonScanner.h"
#include "glowingPlatform.h"
#include "functions.h"
#include "LEDColor.h"
#include "fountain.h"

/**
 * 48 channels total (0-47)
 * 		0-15 red
 * 		16-31 green
 * 		32-47 blue
 *
 * Because each color channel is separate, one layer can be used to
 * describe the channel arrangement on any given layer. For the
 * following diagram, add 16 to the value to get green, and 32 to
 * get blue.
 *
 * 		01  02  03  04
 *
 * 		05  06  07  08			  N
 * 								W-+-E
 * 		09  10  11  12			  S
 *
 * 		13  14  15  16
 */

void setup()
{
	// TLC5940 init, clear all LEDs
	Tlc.init();
	Tlc.clear();
	Serial.begin(9600);

	// Set arduino digital pins [4,7] for output
	for (int i = 4; i <= 7; i++) {
		pinMode(i, OUTPUT);
	}

	// Default to full brightness LED display
	setIntensity(255);

	setColor(red);
}

void loop() {
	//Serial.print("start loop");
	larsonScanner();
	//Serial.print("end loop");
}