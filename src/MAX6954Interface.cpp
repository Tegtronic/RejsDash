#include "MAX6954Interface.h"

#include <Math.h>
#include <SPI.h>

namespace{
	SPISettings settings(16000000, MSBFIRST, SPI_MODE0);
}

void MAX6954::init(){
	MAX6954::WriteRegister(CMD_DisplayTest, 0x00);  
	MAX6954::WriteRegister(CMD_WriteDigitType, 0xFF);           // Digit 0-7 is 14-segment  
	MAX6954::WriteRegister(CMD_DecodeMode, 0xFF);               // Font map enable
	MAX6954::WriteRegister(CMD_GlobalIntensity, 0x0F);          // Max intensity
	MAX6954::WriteRegister(CMD_ScanLimit, 0x07);                // Display digit 0-7
	MAX6954::WriteRegister(CMD_Configuration, 0x0D);            // Exit shutdown mode  
}

void MAX6954::welcome(){
	MAX6954::WriteRegister(CMD_Digit0DualP, 'R');
	MAX6954::WriteRegister(CMD_Digit1DualP, 'E');
	MAX6954::WriteRegister(CMD_Digit2DualP, 'J');
	MAX6954::WriteRegister(CMD_Digit3DualP, 'S');
	MAX6954::WriteRegister(CMD_Digit4DualP, 'D');
	MAX6954::WriteRegister(CMD_Digit5DualP, 'A');
	MAX6954::WriteRegister(CMD_Digit6DualP, 'S');
	MAX6954::WriteRegister(CMD_Digit7DualP, 'H');
}

void MAX6954::outputNumericalDualP(SegmentChunk SegChunk, float Val, uint8_t NoOfDecimals){
	uint16_t IntVal = 0;
	
	if (SegChunk == LEFT){
		switch (NoOfDecimals){
		case 1: IntVal = (uint16_t)round(Val * 10); break;
		case 2: IntVal = (uint16_t)round(Val * 100); break;
		case 3: IntVal = (uint16_t)round(Val * 1000); break;
		default: IntVal = (uint16_t)Val; break;
		}
		
		uint16_t Seg0 = (uint16_t)(IntVal / 1000);
		uint16_t Seg1 = (uint16_t)(IntVal % 1000 / 100);
		uint8_t Seg2 = (uint8_t)((IntVal % 100) / 10);
		uint8_t Seg3 = (uint8_t)(IntVal % 10);
		
		if (NoOfDecimals == 3){
			switch (Seg0){
			case 0: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg0){
			case 0: MAX6954::WriteRegister(CMD_Digit0DualP, BLANK); break;
			case 1: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit0DualP, NUM_9); break;
			}
		}	
		
		if (NoOfDecimals == 2){
			switch (Seg1){
			case 0: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg1){
			case 0: Seg0 == 0 ? MAX6954::WriteRegister(CMD_Digit1DualP, BLANK) : MAX6954::WriteRegister(CMD_Digit1DualP, NUM_0); break;
			case 1: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit1DualP, NUM_9); break;
			}
		}
		
		if (NoOfDecimals == 1){
			switch (Seg2){
			case 0: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg2){
			case 0: (Seg0 == 0 && Seg1 == 0)? MAX6954::WriteRegister(CMD_Digit2DualP, BLANK) : MAX6954::WriteRegister(CMD_Digit2DualP, NUM_0); break;
			case 1: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit2DualP, NUM_9); break;
			}
		}
		switch (Seg3){
		case 0: MAX6954::WriteRegister(CMD_Digit3DualP, NUM_0); break;
		case 1: MAX6954::WriteRegister(CMD_Digit3DualP, NUM_1); break;
		case 2: MAX6954::WriteRegister(CMD_Digit3DualP, NUM_2); break;
		case 3: MAX6954::WriteRegister(CMD_Digit3DualP, NUM_3); break;
		case 4: MAX6954::WriteRegister(CMD_Digit3DualP, NUM_4); break;
		case 5: MAX6954::WriteRegister(CMD_Digit3DualP, NUM_5); break;
		case 6: MAX6954::WriteRegister(CMD_Digit3DualP, NUM_6); break;
		case 7: MAX6954::WriteRegister(CMD_Digit3DualP, NUM_7); break;
		case 8: MAX6954::WriteRegister(CMD_Digit3DualP, NUM_8); break;
		case 9: MAX6954::WriteRegister(CMD_Digit3DualP, NUM_9); break;
		}		
	}
	else{
		switch (NoOfDecimals){
		case 1: IntVal = (uint16_t)round(Val * 10); break;
		case 2: IntVal = (uint16_t)round(Val * 100); break;
		case 3: IntVal = (uint16_t)round(Val * 1000); break;
		default: IntVal = (uint16_t)Val; break;
		}
		
		uint16_t Seg0 = (uint16_t)(IntVal / 1000);
		uint16_t Seg1 = (uint16_t)(IntVal % 1000 / 100);
		uint8_t Seg2 = (uint8_t)((IntVal % 100) / 10);
		uint8_t Seg3 = (uint8_t)(IntVal % 10);
		
		if (NoOfDecimals == 3){
			switch (Seg0){
			case 0: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg0){
			case 0: MAX6954::WriteRegister(CMD_Digit4DualP, BLANK); break;
			case 1: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit4DualP, NUM_9); break;
			}
		}
		
		if (NoOfDecimals == 2){
			switch (Seg1){
			case 0: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg1){
			case 0: Seg0 == 0 ? MAX6954::WriteRegister(CMD_Digit5DualP, BLANK) : MAX6954::WriteRegister(CMD_Digit5DualP, NUM_0); break;
			case 1: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit5DualP, NUM_9); break;
			}
		}
		
		if (NoOfDecimals == 1){
			switch (Seg2){
			case 0: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg2){
			case 0: (Seg0 == 0 && Seg1 == 0)? MAX6954::WriteRegister(CMD_Digit6DualP, BLANK) : MAX6954::WriteRegister(CMD_Digit6DualP, NUM_0); break;
			case 1: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit6DualP, NUM_9); break;
			}
		}
		switch (Seg3){
		case 0: MAX6954::WriteRegister(CMD_Digit7DualP, NUM_0); break;
		case 1: MAX6954::WriteRegister(CMD_Digit7DualP, NUM_1); break;
		case 2: MAX6954::WriteRegister(CMD_Digit7DualP, NUM_2); break;
		case 3: MAX6954::WriteRegister(CMD_Digit7DualP, NUM_3); break;
		case 4: MAX6954::WriteRegister(CMD_Digit7DualP, NUM_4); break;
		case 5: MAX6954::WriteRegister(CMD_Digit7DualP, NUM_5); break;
		case 6: MAX6954::WriteRegister(CMD_Digit7DualP, NUM_6); break;
		case 7: MAX6954::WriteRegister(CMD_Digit7DualP, NUM_7); break;
		case 8: MAX6954::WriteRegister(CMD_Digit7DualP, NUM_8); break;
		case 9: MAX6954::WriteRegister(CMD_Digit7DualP, NUM_9); break;
		}		
	}	
}

void MAX6954::outputNumericalPlaneP0(SegmentChunk SegChunk, float Val, uint8_t NoOfDecimals){
	uint16_t IntVal = 0;
	
	if (SegChunk == LEFT){
		switch (NoOfDecimals){
		case 1: IntVal = (uint16_t)round(Val * 10); break;
		case 2: IntVal = (uint16_t)round(Val * 100); break;
		case 3: IntVal = (uint16_t)round(Val * 1000); break;
		default: IntVal = (uint16_t)round(Val); break;
		}
		
		uint16_t Seg0 = (uint16_t)(IntVal / 1000);
		uint16_t Seg1 = (uint16_t)(IntVal % 1000 / 100);
		uint8_t Seg2 = (uint8_t)((IntVal % 100) / 10);
		uint8_t Seg3 = (uint8_t)(IntVal % 10);
		
		if (NoOfDecimals == 3){
			switch (Seg0){
			case 0: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg0){
			case 0: MAX6954::WriteRegister(CMD_Digit0PlaneP0, BLANK); break;
			case 1: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit0PlaneP0, NUM_9); break;
			}
		}
		
		if (NoOfDecimals == 2){
			switch (Seg1)	{
			case 0: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg1){
			case 0: Seg0 == 0 ? MAX6954::WriteRegister(CMD_Digit1PlaneP0, BLANK) : MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_0); break;
			case 1: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit1PlaneP0, NUM_9); break;
			}
		}
		
		if (NoOfDecimals == 1){
			switch (Seg2){
			case 0: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg2){
			case 0: (Seg0 == 0 && Seg1 == 0)? MAX6954::WriteRegister(CMD_Digit2PlaneP0, BLANK) : MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_0); break;
			case 1: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit2PlaneP0, NUM_9); break;
			}
		}
		switch (Seg3){
		case 0: MAX6954::WriteRegister(CMD_Digit3PlaneP0, NUM_0); break;
		case 1: MAX6954::WriteRegister(CMD_Digit3PlaneP0, NUM_1); break;
		case 2: MAX6954::WriteRegister(CMD_Digit3PlaneP0, NUM_2); break;
		case 3: MAX6954::WriteRegister(CMD_Digit3PlaneP0, NUM_3); break;
		case 4: MAX6954::WriteRegister(CMD_Digit3PlaneP0, NUM_4); break;
		case 5: MAX6954::WriteRegister(CMD_Digit3PlaneP0, NUM_5); break;
		case 6: MAX6954::WriteRegister(CMD_Digit3PlaneP0, NUM_6); break;
		case 7: MAX6954::WriteRegister(CMD_Digit3PlaneP0, NUM_7); break;
		case 8: MAX6954::WriteRegister(CMD_Digit3PlaneP0, NUM_8); break;
		case 9: MAX6954::WriteRegister(CMD_Digit3PlaneP0, NUM_9); break;
		}
	}
	else{
		switch (NoOfDecimals){
		case 1: IntVal = (uint16_t)round(Val * 10); break;
		case 2: IntVal = (uint16_t)round(Val * 100); break;
		case 3: IntVal = (uint16_t)round(Val * 1000); break;
		default: IntVal = (uint16_t)Val; break;
		}
		
		uint16_t Seg0 = (uint16_t)(IntVal / 1000);
		uint16_t Seg1 = (uint16_t)(IntVal % 1000 / 100);
		uint8_t Seg2 = (uint8_t)((IntVal % 100) / 10);
		uint8_t Seg3 = (uint8_t)(IntVal % 10);
		
		if (NoOfDecimals == 3){
			switch (Seg0){
			case 0: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg0){
			case 0: MAX6954::WriteRegister(CMD_Digit4PlaneP0, BLANK); break;
			case 1: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit4PlaneP0, NUM_9); break;
			}
		}
		
		if (NoOfDecimals == 2){
			switch (Seg1){
			case 0: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg1){
			case 0: Seg0 == 0 ? MAX6954::WriteRegister(CMD_Digit5PlaneP0, BLANK) : MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_0); break;
			case 1: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit5PlaneP0, NUM_9); break;
			}
		}
		
		if (NoOfDecimals == 1){
			switch (Seg2){
			case 0: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg2){
			case 0: (Seg0 == 0 && Seg1 == 0)? MAX6954::WriteRegister(CMD_Digit6PlaneP0, BLANK) : MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_0); break;
			case 1: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit6PlaneP0, NUM_9); break;
			}
		}
		switch (Seg3){
		case 0: MAX6954::WriteRegister(CMD_Digit7PlaneP0, NUM_0); break;
		case 1: MAX6954::WriteRegister(CMD_Digit7PlaneP0, NUM_1); break;
		case 2: MAX6954::WriteRegister(CMD_Digit7PlaneP0, NUM_2); break;
		case 3: MAX6954::WriteRegister(CMD_Digit7PlaneP0, NUM_3); break;
		case 4: MAX6954::WriteRegister(CMD_Digit7PlaneP0, NUM_4); break;
		case 5: MAX6954::WriteRegister(CMD_Digit7PlaneP0, NUM_5); break;
		case 6: MAX6954::WriteRegister(CMD_Digit7PlaneP0, NUM_6); break;
		case 7: MAX6954::WriteRegister(CMD_Digit7PlaneP0, NUM_7); break;
		case 8: MAX6954::WriteRegister(CMD_Digit7PlaneP0, NUM_8); break;
		case 9: MAX6954::WriteRegister(CMD_Digit7PlaneP0, NUM_9); break;
		}
	}
}

void MAX6954::outputNumericalPlaneP1(SegmentChunk SegChunk, float Val, uint8_t NoOfDecimals){
	uint16_t IntVal = 0;
	
	if (SegChunk == LEFT){
		switch (NoOfDecimals){
		case 1: IntVal = (uint16_t)round(Val * 10); break;
		case 2: IntVal = (uint16_t)round(Val * 100); break;
		case 3: IntVal = (uint16_t)round(Val * 1000); break;
		default: IntVal = (uint16_t)Val; break;
		}
		
		uint16_t Seg0 = (uint16_t)(IntVal / 1000);
		uint16_t Seg1 = (uint16_t)(IntVal % 1000 / 100);
		uint8_t Seg2 = (uint8_t)((IntVal % 100) / 10);
		uint8_t Seg3 = (uint8_t)(IntVal % 10);
		
		if (NoOfDecimals == 3){
			switch (Seg0){
			case 0: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg0){
			case 0: MAX6954::WriteRegister(CMD_Digit0PlaneP1, BLANK); break;
			case 1: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit0PlaneP1, NUM_9); break;
			}
		}
		
		if (NoOfDecimals == 2){
			switch (Seg1){
			case 0: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg1){
			case 0: Seg0 == 0 ? MAX6954::WriteRegister(CMD_Digit1PlaneP1, BLANK) : MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_0); break;
			case 1: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit1PlaneP1, NUM_9); break;
			}
		}
		
		if (NoOfDecimals == 1){
			switch (Seg2){
			case 0: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg2){
			case 0: (Seg0 == 0 && Seg1 == 0)? MAX6954::WriteRegister(CMD_Digit2PlaneP1, BLANK) : MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_0); break;
			case 1: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit2PlaneP1, NUM_9); break;
			}
		}
		switch (Seg3){
		case 0: MAX6954::WriteRegister(CMD_Digit3PlaneP1, NUM_0); break;
		case 1: MAX6954::WriteRegister(CMD_Digit3PlaneP1, NUM_1); break;
		case 2: MAX6954::WriteRegister(CMD_Digit3PlaneP1, NUM_2); break;
		case 3: MAX6954::WriteRegister(CMD_Digit3PlaneP1, NUM_3); break;
		case 4: MAX6954::WriteRegister(CMD_Digit3PlaneP1, NUM_4); break;
		case 5: MAX6954::WriteRegister(CMD_Digit3PlaneP1, NUM_5); break;
		case 6: MAX6954::WriteRegister(CMD_Digit3PlaneP1, NUM_6); break;
		case 7: MAX6954::WriteRegister(CMD_Digit3PlaneP1, NUM_7); break;
		case 8: MAX6954::WriteRegister(CMD_Digit3PlaneP1, NUM_8); break;
		case 9: MAX6954::WriteRegister(CMD_Digit3PlaneP1, NUM_9); break;
		}
	}
	else{
		switch (NoOfDecimals){
		case 1: IntVal = (uint16_t)round(Val * 10); break;
		case 2: IntVal = (uint16_t)round(Val * 100); break;
		case 3: IntVal = (uint16_t)round(Val * 1000); break;
		default: IntVal = (uint16_t)Val; break;
		}
		
		uint16_t Seg0 = (uint16_t)(IntVal / 1000);
		uint16_t Seg1 = (uint16_t)(IntVal % 1000 / 100);
		uint8_t Seg2 = (uint8_t)((IntVal % 100) / 10);
		uint8_t Seg3 = (uint8_t)(IntVal % 10);
		
		if (NoOfDecimals == 3){
			switch (Seg0){
			case 0: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg0){
			case 0: MAX6954::WriteRegister(CMD_Digit4PlaneP1, BLANK); break;
			case 1: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit4PlaneP1, NUM_9); break;
			}
		}
		
		if (NoOfDecimals == 2){
			switch (Seg1){
			case 0: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg1){
			case 0: Seg0 == 0 ? MAX6954::WriteRegister(CMD_Digit5PlaneP1, BLANK) : MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_0); break;
			case 1: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit5PlaneP1, NUM_9); break;
			}
		}
		
		if (NoOfDecimals == 1){
			switch (Seg2){
			case 0: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_0_W_DOT); break;
			case 1: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_1_W_DOT); break;
			case 2: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_2_W_DOT); break;
			case 3: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_3_W_DOT); break;
			case 4: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_4_W_DOT); break;
			case 5: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_5_W_DOT); break;
			case 6: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_6_W_DOT); break;
			case 7: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_7_W_DOT); break;
			case 8: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_8_W_DOT); break;
			case 9: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_9_W_DOT); break;
			}
		}
		else{
			switch (Seg2){
			case 0: (Seg0 == 0 && Seg1 == 0)? MAX6954::WriteRegister(CMD_Digit6PlaneP1, BLANK) : MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_0); break;
			case 1: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_1); break;
			case 2: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_2); break;
			case 3: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_3); break;
			case 4: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_4); break;
			case 5: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_5); break;
			case 6: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_6); break;
			case 7: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_7); break;
			case 8: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_8); break;
			case 9: MAX6954::WriteRegister(CMD_Digit6PlaneP1, NUM_9); break;
			}
		}
		switch (Seg3){
		case 0: MAX6954::WriteRegister(CMD_Digit7PlaneP1, NUM_0); break;
		case 1: MAX6954::WriteRegister(CMD_Digit7PlaneP1, NUM_1); break;
		case 2: MAX6954::WriteRegister(CMD_Digit7PlaneP1, NUM_2); break;
		case 3: MAX6954::WriteRegister(CMD_Digit7PlaneP1, NUM_3); break;
		case 4: MAX6954::WriteRegister(CMD_Digit7PlaneP1, NUM_4); break;
		case 5: MAX6954::WriteRegister(CMD_Digit7PlaneP1, NUM_5); break;
		case 6: MAX6954::WriteRegister(CMD_Digit7PlaneP1, NUM_6); break;
		case 7: MAX6954::WriteRegister(CMD_Digit7PlaneP1, NUM_7); break;
		case 8: MAX6954::WriteRegister(CMD_Digit7PlaneP1, NUM_8); break;
		case 9: MAX6954::WriteRegister(CMD_Digit7PlaneP1, NUM_9); break;
		}
	}
}

void MAX6954::clear(){
	MAX6954::WriteRegister(CMD_Digit0DualP, BLANK);
	MAX6954::WriteRegister(CMD_Digit1DualP, BLANK);
	MAX6954::WriteRegister(CMD_Digit2DualP, BLANK);
	MAX6954::WriteRegister(CMD_Digit3DualP, BLANK);
	MAX6954::WriteRegister(CMD_Digit4DualP, BLANK);
	MAX6954::WriteRegister(CMD_Digit5DualP, BLANK);
	MAX6954::WriteRegister(CMD_Digit6DualP, BLANK);
	MAX6954::WriteRegister(CMD_Digit7DualP, BLANK);
}

void MAX6954::WriteRegister(uint8_t RegAdr, uint8_t Payload){
	SPI.beginTransaction(settings);
	digitalWrite(MAX6954_CS, LOW);
	SPI.transfer(RegAdr);
	SPI.transfer(Payload);
	digitalWrite(MAX6954_CS, HIGH);
	SPI.endTransaction();
}

void MAX6954::Display(uint8_t FontAddress[]){
	WriteRegister(CMD_Digit0DualP, FontAddress[0]);
	WriteRegister(CMD_Digit1DualP, FontAddress[1]);
	WriteRegister(CMD_Digit2DualP, FontAddress[2]);
	WriteRegister(CMD_Digit3DualP, FontAddress[3]);
	WriteRegister(CMD_Digit4DualP, FontAddress[4]);
	WriteRegister(CMD_Digit5DualP, FontAddress[5]);
	WriteRegister(CMD_Digit6DualP, FontAddress[6]);
	WriteRegister(CMD_Digit7DualP, FontAddress[7]);
}
