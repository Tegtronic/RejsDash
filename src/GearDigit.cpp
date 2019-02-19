#include "GearDigit.h"

void GearDigit::init(){
	pinMode(BCD_LE, OUTPUT);
	pinMode(BCD_A, OUTPUT);
	pinMode(BCD_B, OUTPUT);
	pinMode(BCD_C, OUTPUT);
	pinMode(BCD_D, OUTPUT);
}

void GearDigit::setOutput(uint8_t Digit){
	digitalWrite(BCD_LE, HIGH);
	switch(Digit)	{
	case 0:
		digitalWrite(BCD_A, LOW);
		digitalWrite(BCD_B, LOW);
		digitalWrite(BCD_C, LOW);
		digitalWrite(BCD_D, LOW);
		break;		
	case 1:
		digitalWrite(BCD_A, HIGH);
		digitalWrite(BCD_B, LOW);
		digitalWrite(BCD_C, LOW);
		digitalWrite(BCD_D, LOW);
		break;
	case 2:
		digitalWrite(BCD_A, LOW);
		digitalWrite(BCD_B, HIGH);
		digitalWrite(BCD_C, LOW);
		digitalWrite(BCD_D, LOW);
		break;
	case 3:
		digitalWrite(BCD_A, HIGH);
		digitalWrite(BCD_B, HIGH);
		digitalWrite(BCD_C, LOW);
		digitalWrite(BCD_D, LOW);
		break;
	case 4:
		digitalWrite(BCD_A, LOW);
		digitalWrite(BCD_B, LOW);
		digitalWrite(BCD_C, HIGH);
		digitalWrite(BCD_D, LOW);
		break;
	case 5:
		digitalWrite(BCD_A, HIGH);
		digitalWrite(BCD_B, LOW);
		digitalWrite(BCD_C, HIGH);
		digitalWrite(BCD_D, LOW);
		break;
	case 6:
		digitalWrite(BCD_A, LOW);
		digitalWrite(BCD_B, HIGH);
		digitalWrite(BCD_C, HIGH);
		digitalWrite(BCD_D, LOW);
		break;
	case 7:
		digitalWrite(BCD_A, HIGH);
		digitalWrite(BCD_B, HIGH);
		digitalWrite(BCD_C, HIGH);
		digitalWrite(BCD_D, LOW);
		break;
	case 8:
		digitalWrite(BCD_A, LOW);
		digitalWrite(BCD_B, LOW);
		digitalWrite(BCD_C, LOW);
		digitalWrite(BCD_D, HIGH);
		break;
	case 9:
		digitalWrite(BCD_A, HIGH);
		digitalWrite(BCD_B, LOW);
		digitalWrite(BCD_C, LOW);
		digitalWrite(BCD_D, HIGH);
		break;
	default:
		blank();
		break;
	}
	digitalWrite(BCD_LE, LOW);
}

void GearDigit::blank(){
	digitalWrite(BCD_LE, HIGH);
	digitalWrite(BCD_A, LOW);
	digitalWrite(BCD_B, HIGH);
	digitalWrite(BCD_C, LOW);
	digitalWrite(BCD_D, HIGH);
	digitalWrite(BCD_LE, LOW);
}

