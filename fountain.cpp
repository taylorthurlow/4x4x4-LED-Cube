#include "Arduino.h"
#include "glowingPlatform.h"
#include "functions.h"
#include "Tlc5940.h"
#include "fountain.h"

int levels[] = {1, 1, 2, 3, 4, 4, 3, 2};
int frames[][12] = {{1, 2, 3, 4, 5, 8, 9, 12, 13, 14, 15, 16},
				  {6, 7, 10, 11},
				  {6, 7, 10, 11},
				  {6, 7, 10, 11},
				  {6, 7, 10, 11},
				  {1, 2, 3, 4, 5, 8, 9, 12, 13, 14, 15, 16},
				  {1, 2, 3, 4, 5, 8, 9, 12, 13, 14, 15, 16},
				  {1, 2, 3, 4, 5, 8, 9, 12, 13, 14, 15, 16}};

void fountain() {
	// Frame iterator (8 total)
	for (int frame = 0; frame < 8; frame++) {
		setLevel(levels[frame]);
		for (int channel = 0; channel < 16; channel++) {
			int size = sizeof(frames[frame])/sizeof(frames[frame][0]);
			if (isValueInArray(channel, frames[frame], size)) {
				Tlc.set(channel, getIntensity());
				Tlc.update();
				Tlc.set(channel + 16, getIntensity());
				Tlc.update();
				Tlc.set(channel + 32, getIntensity());
				Tlc.update();
			}
		}
		delay(100);
	}
}

// from http://stackoverflow.com/questions/15094834/check-if-a-value-exist-in-a-array
bool isValueInArray(int val, int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == val) return true;
    }
    return false;
}