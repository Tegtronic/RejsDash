#include <arduino.h>

#define RED_INTENSITY 32
#define YELLOW_RED_INTENSITY 16
#define GREEN_INTENSITY 16
#define BLUE_INTENSITY 16

namespace NeoPixelBar{
	void init(uint16_t NewShiftLightRPM, uint16_t NewStepsizeRPM);
	void welcome();
	void blank();
	void leftToRightFill(uint16_t RPM);
	void sideFill(uint16_t RPM);
	void sideFillShortStep(uint16_t RPM);
	void shiftLight(uint16_t RPM);
}

