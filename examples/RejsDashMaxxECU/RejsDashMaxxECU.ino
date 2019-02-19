#include <ACAN2515.h>
#include <ACAN2515Settings.h>
#include <ACANBuffer.h>
#include <ACANBuffer16.h>
#include <CANMessage.h>
#include <MCP2515ReceiveFilters.h>

#include "GearDigit.h"
#include "MAX6954Interface.h"
#include "MaxxECU.h"
#include "NeoPixelBar.h"

static const byte MCP2515_CS  = 11 ; // CS input of MCP2515, adapt to your design
static const byte MCP2515_INT = 7 ; // INT output of MCP2515, adapt to your design
static const uint32_t QUARTZ_FREQUENCY = 16000000 ; // 16 MHz
static const uint32_t CAN_BAUDRATE = 500000;

ACAN2515 can (MCP2515_CS, SPI, MCP2515_INT);

static void receive0 (const CANMessage & inMessage) {
	//Serial.println ("Receive 0") ;
}

void setup() {
	Serial.begin(115200);
	GearDigit::init();
	pinMode(5, OUTPUT);               // NeoPixel Serial Data
	pinMode(MCP2515_INT, INPUT);    
	pinMode(10, OUTPUT);              // MAX6954 Chip Select
	pinMode(11, OUTPUT);              // MCP Chip Select
	pinMode(12, OUTPUT);              // MCP Reset
	pinMode(13, OUTPUT);              // ItsyBitsy LED
	GearDigit::setOutput(8);
	digitalWrite(13, LOW);
	digitalWrite(11, HIGH);
	digitalWrite(12, HIGH);
	digitalWrite(10, LOW);            // Reset MCP2515
	delay(1);                         // MCP2515 reset delay    
	digitalWrite(10, HIGH);           // MCP2515 Reset OFF
	digitalWrite(5, LOW);             // Init low value of NeoPixel Data

	SPI.begin();

	MAX6954::init();
	MAX6954::welcome();

	NeoPixelBar::init();
	NeoPixelBar::welcome();

	delay(100);
	GearDigit::blank();
	/////////////////////////////////////////// MCP2515 Init /////////////////////////////////////////// 
	ACAN2515Settings settings(QUARTZ_FREQUENCY , CAN_BAUDRATE);
	settings.mRequestedMode = ACAN2515Settings :: NormalMode;
	const ACAN2515Mask rxm0 = standard2515Mask (0x7E0 , 0, 0) ;
	const ACAN2515AcceptanceFilter filter [] = 
	{standard2515Filter (0x520 , 0, 0), receive0};
	const uint16_t errorCode = can.begin (settings ,
	[] { can.isr () ; },
	rxm0 , // Value set to RXM0 register
	filter , // The filter array
	1) ; // Filter array size
}

void loop() {
	Maxx::Signals myMaxx;             // Struct containing values from MaxxECU
	Maxx::initStruct(myMaxx);         // Set all initial values to 0

	// Only update display when value has changed so store which value is currently showing here
	byte gearShown = 0;
	int coolantTempShown = 0;
	int oilPressureShown = 0;
	int RPMShown = 0;

	CANMessage frame;

	while(1){
		if (can.available ()) {
			can.receive (frame);
			Maxx::processFrame(frame, myMaxx);
			
			if(myMaxx.Gear != gearShown){
				GearDigit::setOutput(myMaxx.Gear);
				gearShown = myMaxx.Gear;
			}
			
			/*
		* Example use of warning system. If Coolant level exceeds warning limit (in this case 105 degrees) then the value will be written to plane 0 and plane 1 will be cleared except identifier
		* letter which causes a blinking effect on the value in the dash to attract attention from the driver
		*/
			if(myMaxx.CoolantTemp != coolantTempShown){
				if(myMaxx.CoolantTemp * 0.1 > 90){
					MAX6954::outputNumericalPlaneP0(RIGHT, myMaxx.CoolantTemp*0.1, 0);
					MAX6954::WriteRegister(CMD_Digit4PlaneP0, 'W');                             // Set ID Letter on Plane 0
					MAX6954::WriteRegister(CMD_Digit4PlaneP1, 'W');                             // Set ID Letter on Plane 1
					MAX6954::WriteRegister(CMD_Digit5PlaneP1, 0x10);                            // Clear segment 6 on Plane 1
					MAX6954::WriteRegister(CMD_Digit6PlaneP1, 0x10);                            // Clear segment 7 on Plane 1
					MAX6954::WriteRegister(CMD_Digit7PlaneP1, 0x10);                            // Clear segment 8 on Plane 1
				}
				else{
					MAX6954::outputNumericalDualP(RIGHT, myMaxx.CoolantTemp*0.1, 0);          // Write coolant value to right side of the dash. Make sure to apply the appropriate factor for the value. 
					MAX6954::WriteRegister(CMD_Digit4DualP, 'W');                             // Set letter on empty segment after writing value to provide identifier (W=Water)
				}
				coolantTempShown = myMaxx.CoolantTemp;                                      // Save which value is showing so the display only needs to be updated on changes
			}
			
			if(myMaxx.UserAnalogInput1 != oilPressureShown){
				MAX6954::outputNumericalDualP(LEFT, myMaxx.UserAnalogInput1*0.001, 1);
				oilPressureShown = myMaxx.UserAnalogInput1;
				MAX6954::WriteRegister(CMD_Digit0DualP, 'O');                           // Set letter on empty segment after writing value to provide identifier (OP=OilPressure)
				MAX6954::WriteRegister(CMD_Digit1DualP, 'P');         
			}

			if(myMaxx.RPM != RPMShown){
				//NeoPixelBar::leftToRightFill(myMaxx.RPM);
				NeoPixelBar::sideFill(myMaxx.RPM);
				//NeoPixelBar::sideFillShortStep(myMaxx.RPM);
				//NeoPixelBar::shiftLight(myMaxx.RPM);
			}
		}    
	}
}
