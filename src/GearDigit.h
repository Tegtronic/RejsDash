#pragma once

#include <arduino.h>

/*
* BCD Driver IC: CD4511B
* http://www.ti.com/lit/ds/symlink/cd4511b.pdf
*/

#define BCD_LE A1	// Latch enable
#define BCD_A A2
#define BCD_B A3
#define BCD_C A4
#define BCD_D A5

namespace GearDigit{
	void init();
	void setOutput(uint8_t Digit); 
	void blank();                                      
};
