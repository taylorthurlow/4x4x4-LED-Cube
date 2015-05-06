#include "Arduino.h"
#include "glowingPlatform.h"
#include "functions.h"
#include "Tlc5940.h"

/**
 * Generates a glowing platform of varying brightness. The lower level has
 * the highest brightness, and the 4th (uppermost) level has the lowest
 * brightness. This produces the glowing effect. The color used to generate
 * the platform is based on the value of currentColor.
 */
void glowingPlatform() {
	for (int level = 0; level < 4; level++) {
		setLevel(level);
		setIntensity(256 - (64 * level));
		if (level == 0) setIntensity(255);
		LEDColor color = getColor();
		// iterates through one layer of 16 leds (0-15)
		for (int led = 0; led < 16; led++) {
			if (color == white) {
				for (int i = 0; i < 3; i++) {
					Tlc.set((i * 16) + led, getIntensity());
					Tlc.update();
				}
			} else if (color == cyan) {
				Tlc.set(led + 16, getIntensity());
				Tlc.update();
				Tlc.set(led + 32, getIntensity());
				Tlc.update();
			} else if (color == magenta) {
				Tlc.set(led, getIntensity());
				Tlc.update();
				Tlc.set(led + 32, getIntensity());
				Tlc.update();
			} else if (color == yellow) {
				Tlc.set(led, getIntensity());
				Tlc.update();
				Tlc.set(led + 16, getIntensity());
				Tlc.update();
			} else if (color == red) {
				Tlc.set(led, getIntensity());
				Tlc.update();
			} else if (color == green) {
				Tlc.set(led + 16, getIntensity());
				Tlc.update();
			} else if (color == blue) {
				Tlc.set(led + 32, getIntensity());
				Tlc.update();
			}
		}
	}
}
