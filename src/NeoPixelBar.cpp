#include "NeoPixelBar.h"

#include <Adafruit_NeoPixel.h>

namespace{
	Adafruit_NeoPixel strip = Adafruit_NeoPixel(15, 5, NEO_RGB + NEO_KHZ800);
	uint8_t LEDStageVal = 0;
	uint16_t SHIFTLIGHT_RPM = 5500;
	uint16_t STEPSIZE_RPM = 300;
}

void NeoPixelBar::init(uint16_t NewShiftLightRPM, uint16_t NewStepsizeRPM){
	strip.begin();
	strip.show();
	SHIFTLIGHT_RPM = NewShiftLightRPM;
	STEPSIZE_RPM = NewStepsizeRPM;
}

void NeoPixelBar::welcome(){
	for(uint8_t i = 0; i < 15; ++i){
		strip.setPixelColor(i, 50, 0, 0);
		strip.show();
		delay(20);
	}
	for(uint8_t i = 0; i < 15; ++i){
		strip.setPixelColor(i, 0, 0, 0);
		strip.show();
		delay(20);
	}
}

void NeoPixelBar::blank(){
	for(uint8_t i = 0; i < 15; ++i) strip.setPixelColor(i, 0, 0, 0);
	strip.show();
}

void NeoPixelBar::leftToRightFill(uint16_t RPM){
	if (RPM > SHIFTLIGHT_RPM - 14 * STEPSIZE_RPM ) strip.setPixelColor(0, 0, GREEN_INTENSITY, 0); else strip.setPixelColor(0, 0, 0, 0);
	if (RPM > SHIFTLIGHT_RPM - 13 * STEPSIZE_RPM ) strip.setPixelColor(1, 0, GREEN_INTENSITY, 0); else strip.setPixelColor(1, 0, 0, 0);
	if (RPM > SHIFTLIGHT_RPM - 12 * STEPSIZE_RPM ) strip.setPixelColor(2, 0, GREEN_INTENSITY, 0); else strip.setPixelColor(2, 0, 0, 0);
	if (RPM > SHIFTLIGHT_RPM - 11 * STEPSIZE_RPM ) strip.setPixelColor(3, 0, GREEN_INTENSITY, 0); else strip.setPixelColor(3, 0, 0, 0);
	if (RPM > SHIFTLIGHT_RPM - 10 * STEPSIZE_RPM ) strip.setPixelColor(4, 0, GREEN_INTENSITY, 0); else strip.setPixelColor(4, 0, 0, 0);
	if (RPM > SHIFTLIGHT_RPM - 9 * STEPSIZE_RPM ) strip.setPixelColor(5, 0, GREEN_INTENSITY, 0); else strip.setPixelColor(5, 0, 0, 0);
	if (RPM > SHIFTLIGHT_RPM - 8 * STEPSIZE_RPM ) strip.setPixelColor(6, 0, GREEN_INTENSITY, 0); else strip.setPixelColor(6, 0, 0, 0);
	if (RPM > SHIFTLIGHT_RPM - 7 * STEPSIZE_RPM ) strip.setPixelColor(7, 0, GREEN_INTENSITY, 0); else strip.setPixelColor(7, 0, 0, 0);
	if (RPM > SHIFTLIGHT_RPM - 6 * STEPSIZE_RPM ) strip.setPixelColor(8, 0, GREEN_INTENSITY, 0); else strip.setPixelColor(8, 0, 0, 0);
	if (RPM > SHIFTLIGHT_RPM - 5 * STEPSIZE_RPM ) strip.setPixelColor(9, 0, GREEN_INTENSITY, 0); else strip.setPixelColor(9, 0, 0, 0);
	if (RPM > SHIFTLIGHT_RPM - 4 * STEPSIZE_RPM ) strip.setPixelColor(10, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0); else strip.setPixelColor(10, 0, 0, 0);
	if (RPM > SHIFTLIGHT_RPM - 3 * STEPSIZE_RPM ) strip.setPixelColor(11, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0); else strip.setPixelColor(11, 0, 0, 0);
	if (RPM > SHIFTLIGHT_RPM - 2 * STEPSIZE_RPM ) strip.setPixelColor(12, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0); else strip.setPixelColor(12, 0, 0, 0);
	if (RPM > SHIFTLIGHT_RPM - STEPSIZE_RPM ) strip.setPixelColor(13, RED_INTENSITY, 0, 0); else strip.setPixelColor(13, 0, 0, 0);
	if (RPM > SHIFTLIGHT_RPM) strip.setPixelColor(14, RED_INTENSITY, 0, 0); else strip.setPixelColor(14, 0, 0, 0);

	strip.show();
}

void NeoPixelBar::sideFill(uint16_t RPM){
	if (RPM > SHIFTLIGHT_RPM - 8 * STEPSIZE_RPM){
		if (RPM < SHIFTLIGHT_RPM - 7 * STEPSIZE_RPM ){
			strip.setPixelColor(0, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(1, 0, 0, 0);
			strip.setPixelColor(2, 0, 0, 0);
			strip.setPixelColor(3, 0, 0, 0);
			strip.setPixelColor(4, 0, 0, 0);
			strip.setPixelColor(5, 0, 0, 0);
			strip.setPixelColor(6, 0, 0, 0);
			strip.setPixelColor(7, 0, 0, 0);
			strip.setPixelColor(8, 0, 0, 0);
			strip.setPixelColor(9, 0, 0, 0);
			strip.setPixelColor(10, 0, 0, 0);
			strip.setPixelColor(11, 0, 0, 0);
			strip.setPixelColor(12, 0, 0, 0);
			strip.setPixelColor(13, 0, 0, 0);
			strip.setPixelColor(14, 0, GREEN_INTENSITY, 0);
			if (LEDStageVal != 1) strip.show();
			LEDStageVal = 1;
		}
		else if (RPM < SHIFTLIGHT_RPM - 6 * STEPSIZE_RPM){
			strip.setPixelColor(0, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(1, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(2, 0, 0, 0);
			strip.setPixelColor(3, 0, 0, 0);
			strip.setPixelColor(4, 0, 0, 0);
			strip.setPixelColor(5, 0, 0, 0);
			strip.setPixelColor(6, 0, 0, 0);
			strip.setPixelColor(7, 0, 0, 0);
			strip.setPixelColor(8, 0, 0, 0);
			strip.setPixelColor(9, 0, 0, 0);
			strip.setPixelColor(10, 0, 0, 0);
			strip.setPixelColor(11, 0, 0, 0);
			strip.setPixelColor(12, 0, 0, 0);
			strip.setPixelColor(13, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(14, 0, GREEN_INTENSITY, 0);
			if (LEDStageVal != 2) strip.show();
			LEDStageVal = 2;
		}
		else if (RPM < SHIFTLIGHT_RPM - 5 * STEPSIZE_RPM){
			strip.setPixelColor(0, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(1, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(2, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(3, 0, 0, 0);
			strip.setPixelColor(4, 0, 0, 0);
			strip.setPixelColor(5, 0, 0, 0);
			strip.setPixelColor(6, 0, 0, 0);
			strip.setPixelColor(7, 0, 0, 0);
			strip.setPixelColor(8, 0, 0, 0);
			strip.setPixelColor(9, 0, 0, 0);
			strip.setPixelColor(10, 0, 0, 0);
			strip.setPixelColor(11, 0, 0, 0);
			strip.setPixelColor(12, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(13, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(14, 0, GREEN_INTENSITY, 0);
			if (LEDStageVal != 3) strip.show();
			LEDStageVal = 3;
		}
		else if (RPM < SHIFTLIGHT_RPM - 4 * STEPSIZE_RPM){
			strip.setPixelColor(0, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(1, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(2, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(3, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(4, 0, 0, 0);
			strip.setPixelColor(5, 0, 0, 0);
			strip.setPixelColor(6, 0, 0, 0);
			strip.setPixelColor(7, 0, 0, 0);
			strip.setPixelColor(8, 0, 0, 0);
			strip.setPixelColor(9, 0, 0, 0);
			strip.setPixelColor(10, 0, 0, 0);
			strip.setPixelColor(11, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(12, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(13, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(14, 0, GREEN_INTENSITY, 0);
			if (LEDStageVal != 4) strip.show();
			LEDStageVal = 4;
		}
		else if (RPM < SHIFTLIGHT_RPM - 3 * STEPSIZE_RPM){
			strip.setPixelColor(0, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(1, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(2, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(3, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(4, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(5, 0, 0, 0);
			strip.setPixelColor(6, 0, 0, 0);
			strip.setPixelColor(7, 0, 0, 0);
			strip.setPixelColor(8, 0, 0, 0);
			strip.setPixelColor(9, 0, 0, 0);
			strip.setPixelColor(10, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(11, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(12, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(13, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(14, 0, GREEN_INTENSITY, 0);
			if (LEDStageVal != 5) strip.show();
			LEDStageVal = 5;
		}
		else if (RPM < SHIFTLIGHT_RPM - 2 * STEPSIZE_RPM){
			strip.setPixelColor(0, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(1, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(2, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(3, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(4, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(5, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(6, 0, 0, 0);
			strip.setPixelColor(7, 0, 0, 0);
			strip.setPixelColor(8, 0, 0, 0);
			strip.setPixelColor(9, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(10, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(11, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(12, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(13, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(14, 0, GREEN_INTENSITY, 0);
			if (LEDStageVal != 6) strip.show();
			LEDStageVal = 6;
		}
		else if (RPM < SHIFTLIGHT_RPM - 1 * STEPSIZE_RPM){
			strip.setPixelColor(0, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(1, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(2, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(3, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(4, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(5, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(6, RED_INTENSITY, 0, 0);
			strip.setPixelColor(7, 0, 0, 0);
			strip.setPixelColor(8, RED_INTENSITY, 0, 0);
			strip.setPixelColor(9, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(10, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(11, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(12, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(13, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(14, 0, GREEN_INTENSITY, 0);
			if (LEDStageVal != 7) strip.show();
			LEDStageVal = 7;
		}
		else if (RPM < SHIFTLIGHT_RPM){
			strip.setPixelColor(0, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(1, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(2, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(3, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(4, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(5, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(6, RED_INTENSITY, 0, 0);
			strip.setPixelColor(7, RED_INTENSITY, 0, 0);
			strip.setPixelColor(8, RED_INTENSITY, 0, 0);
			strip.setPixelColor(9, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(10, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(11, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(12, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(13, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(14, 0, GREEN_INTENSITY, 0);
			if (LEDStageVal != 8) strip.show();
			LEDStageVal = 8;
		}
		else{
			for(int i = 0; i < 15; ++i) strip.setPixelColor(i, 0, 0, BLUE_INTENSITY);
			if (LEDStageVal != 9) strip.show();
			LEDStageVal = 9;
		}
	}
	else{
		if (LEDStageVal != 0) NeoPixelBar::blank();
		LEDStageVal = 0;
	}
}

void NeoPixelBar::sideFillShortStep(uint16_t RPM){
	if (RPM > SHIFTLIGHT_RPM - 3 * STEPSIZE_RPM){
		if (RPM < SHIFTLIGHT_RPM - 2 * STEPSIZE_RPM){
			strip.setPixelColor(0, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(1, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(2, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(3, 0, 0, 0);
			strip.setPixelColor(4, 0, 0, 0);
			strip.setPixelColor(5, 0, 0, 0);
			strip.setPixelColor(6, 0, 0, 0);
			strip.setPixelColor(7, 0, 0, 0);
			strip.setPixelColor(8, 0, 0, 0);
			strip.setPixelColor(9, 0, 0, 0);
			strip.setPixelColor(10, 0, 0, 0);
			strip.setPixelColor(11, 0, 0, 0);
			strip.setPixelColor(12, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(13, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(14, 0, GREEN_INTENSITY, 0);
			if (LEDStageVal != 1) strip.show();
			LEDStageVal = 1;
		}
		else if (RPM < SHIFTLIGHT_RPM - 1 * STEPSIZE_RPM){
			strip.setPixelColor(0, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(1, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(2, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(3, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(4, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(5, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(6, 0, 0, 0);
			strip.setPixelColor(7, 0, 0, 0);
			strip.setPixelColor(8, 0, 0, 0);
			strip.setPixelColor(9, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(10, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(11, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(12, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(13, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(14, 0, GREEN_INTENSITY, 0);
			if (LEDStageVal != 2) strip.show();
			LEDStageVal = 2;
		}
		else if (RPM < SHIFTLIGHT_RPM){
			strip.setPixelColor(0, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(1, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(2, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(3, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(4, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(5, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(6, RED_INTENSITY, 0, 0);
			strip.setPixelColor(7, RED_INTENSITY, 0, 0);
			strip.setPixelColor(8, RED_INTENSITY, 0, 0);
			strip.setPixelColor(9, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(10, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(11, YELLOW_RED_INTENSITY, GREEN_INTENSITY, 0);
			strip.setPixelColor(12, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(13, 0, GREEN_INTENSITY, 0);
			strip.setPixelColor(14, 0, GREEN_INTENSITY, 0);
			if (LEDStageVal != 3) strip.show();
			LEDStageVal = 3;
		}
		else{
			for(uint8_t i = 0; i < 15; ++i) strip.setPixelColor(i, 0, 0, BLUE_INTENSITY);
			if (LEDStageVal != 4) strip.show();
			LEDStageVal = 4;
		}
	}
	else{
		if (LEDStageVal != 0) NeoPixelBar::blank();
		LEDStageVal = 0;
	}
}

void NeoPixelBar::shiftLight(uint16_t RPM){
	if(RPM > SHIFTLIGHT_RPM){
		for(uint8_t i = 0; i < 15; ++i) strip.setPixelColor(i, 0, 0, BLUE_INTENSITY);
		if (LEDStageVal != 1) strip.show();
		LEDStageVal = 1;
	}
	else{
		if (LEDStageVal != 0) NeoPixelBar::blank();
		LEDStageVal = 0;
	}    
}

