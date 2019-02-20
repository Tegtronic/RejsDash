#include <arduino.h>

#define MAX6954_CS 10     // Chip Select pin for SPI

#define CMD_NoOp 0x00
#define CMD_DecodeMode 0x01
#define CMD_GlobalIntensity 0x02
#define CMD_ScanLimit 0x03
#define CMD_Configuration 0x04
#define CMD_GPIOData 0x05
#define CMD_PortConfiguration 0x06
#define CMD_DisplayTest 0x07
#define CMD_WriteDigitType 0x0C
#define CMD_Intensity10 0x10
#define CMD_Intensity32 0x11
#define CMD_Intensity54 0x12
#define CMD_Intensity76 0x13
#define CMD_Digit0PlaneP0 0x20
#define CMD_Digit1PlaneP0 0x21
#define CMD_Digit2PlaneP0 0x22
#define CMD_Digit3PlaneP0 0x23
#define CMD_Digit4PlaneP0 0x24
#define CMD_Digit5PlaneP0 0x25
#define CMD_Digit6PlaneP0 0x26
#define CMD_Digit7PlaneP0 0x27
#define CMD_Digit0PlaneP1 0x40
#define CMD_Digit1PlaneP1 0x41
#define CMD_Digit2PlaneP1 0x42
#define CMD_Digit3PlaneP1 0x43
#define CMD_Digit4PlaneP1 0x44
#define CMD_Digit5PlaneP1 0x45
#define CMD_Digit6PlaneP1 0x46
#define CMD_Digit7PlaneP1 0x47
#define CMD_Digit0DualP 0x60
#define CMD_Digit1DualP 0x61
#define CMD_Digit2DualP 0x62
#define CMD_Digit3DualP 0x63
#define CMD_Digit4DualP 0x64
#define CMD_Digit5DualP 0x65
#define CMD_Digit6DualP 0x66
#define CMD_Digit7DualP 0x67

#define BLANK 0x10

#define NUM_0 0x00
#define NUM_1 0x01
#define NUM_2 0x02
#define NUM_3 0x03
#define NUM_4 0x04
#define NUM_5 0x05
#define NUM_6 0x06
#define NUM_7 0x07
#define NUM_8 0x08
#define NUM_9 0x09
#define NUM_0_W_DOT 0x80
#define NUM_1_W_DOT 0x81
#define NUM_2_W_DOT 0x82
#define NUM_3_W_DOT 0x83
#define NUM_4_W_DOT 0x84
#define NUM_5_W_DOT 0x85
#define NUM_6_W_DOT 0x86
#define NUM_7_W_DOT 0x87
#define NUM_8_W_DOT 0x88
#define NUM_9_W_DOT 0x89

enum SegmentChunk{
	LEFT, RIGHT               // Selects which side of the gear digit to show a value
};


namespace MAX6954{
	void init();
	void welcome();
	void outputNumericalDualP(SegmentChunk SegChunk, float Val, uint8_t NoOfDecimals);
	void outputNumericalPlaneP0(SegmentChunk SegChunk, float Val, uint8_t NoOfDecimals);
	void outputNumericalPlaneP1(SegmentChunk SegChunk, float Val, uint8_t NoOfDecimals);
	void clear();
	void WriteRegister(uint8_t RegAdr, uint8_t Payload);
	void Display(uint8_t FontAddress[]);
}
