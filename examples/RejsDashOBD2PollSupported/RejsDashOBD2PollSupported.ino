/*
	This example program is used to check which OBD2 PID's can be polled from a car.
	Upload this sketch to RejsDash and open serial port in Arduino IDE when connected
	to a car with OBD2 over CAN. Save the reported list of supported PID's and choose
	which values to poll in your regular OBD2 sketch for display in RejsDash.
*/

#include <ACAN2515.h>
#include <ACAN2515Settings.h>
#include <ACANBuffer.h>
#include <ACANBuffer16.h>
#include <CANMessage.h>
#include <MCP2515ReceiveFilters.h>

#include "GearDigit.h"
#include "MAX6954Interface.h"
#include "NeoPixelBar.h"
#include "OBD2.h"

#define SHIFTLIGHT_THRESHOLD 4000
#define SHIFTLIGHT_STEP_PER_LED 300

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

	NeoPixelBar::init(SHIFTLIGHT_THRESHOLD, SHIFTLIGHT_STEP_PER_LED);
	NeoPixelBar::welcome();

	delay(100);
	GearDigit::blank();
	/////////////////////////////////////////// MCP2515 Init /////////////////////////////////////////// 
	ACAN2515Settings settings(QUARTZ_FREQUENCY , CAN_BAUDRATE);
	settings.mRequestedMode = ACAN2515Settings :: NormalMode;
	const ACAN2515Mask rxm0 = standard2515Mask (0x7FF , 0, 0) ;
	const ACAN2515AcceptanceFilter filter [] = 
	{standard2515Filter (0x7E8 , 0, 0), receive0};
	const uint16_t errorCode = can.begin (settings ,
		[] { can.isr () ; },
		rxm0 , // Value set to RXM0 register
		filter , // The filter array
		1) ; // Filter array size
}

void loop() {
	CANMessage MyCANFrame;

	byte PIDArray[6];
	PIDArray[0] = PID_PIDsSupported0to20;
	PIDArray[1] = PID_PIDsSupported21to40;
	PIDArray[2] = PID_PIDsSupported41to60;
	PIDArray[3] = PID_PIDsSupported61to80;
	PIDArray[4] = PID_PIDsSupported81toA0;
	PIDArray[5] = PID_PIDsSupportedA1toC0;
	
	byte PIDArrayPtr = 0;
	
	while(1){
		delay(500);
		if(!OBD2::requestIsPending())OBD2::requestPID(can, PIDArray[PIDArrayPtr]);

		if (can.available ()) {
			can.receive (MyCANFrame);
			if(MyCANFrame.data[1] == 0x41){
				byte PID_ID = MyCANFrame.data[2];
				
				if(PID_ID == PID_PIDsSupported0to20){
					if(bitRead(MyCANFrame.data[3], 7)) Serial.println(F("0x01 Monitor status DTC/MIL"));
					if(bitRead(MyCANFrame.data[3], 6)) Serial.println(F("0x02 Freeze DTC"));
					if(bitRead(MyCANFrame.data[3], 5)) Serial.println(F("0x03 Fuel system status"));
					if(bitRead(MyCANFrame.data[3], 4)) Serial.println(F("0x04 Calc Engine Load"));
					if(bitRead(MyCANFrame.data[3], 3)) Serial.println(F("0x05 Engine Coolant Temp"));
					if(bitRead(MyCANFrame.data[3], 2)) Serial.println(F("0x06 Short Term Fuel Trim B1"));
					if(bitRead(MyCANFrame.data[3], 1)) Serial.println(F("0x07 Long Term Fuel Trim B1"));
					if(bitRead(MyCANFrame.data[3], 0)) Serial.println(F("0x08 Short Term Fuel Trim B2"));
					if(bitRead(MyCANFrame.data[4], 7)) Serial.println(F("0x09 Long Term Fuel Trim B2"));
					if(bitRead(MyCANFrame.data[4], 6)) Serial.println(F("0x0A Fuel Pressure Gauge Pressure"));
					if(bitRead(MyCANFrame.data[4], 5)) Serial.println(F("0x0B Intake MAP"));
					if(bitRead(MyCANFrame.data[4], 4)) Serial.println(F("0x0C Engine RPM"));
					if(bitRead(MyCANFrame.data[4], 3)) Serial.println(F("0x0D Vehicle Speed"));
					if(bitRead(MyCANFrame.data[4], 2)) Serial.println(F("0x0E Timing Advance"));
					if(bitRead(MyCANFrame.data[4], 1)) Serial.println(F("0x0F Intake Air Temp"));
					if(bitRead(MyCANFrame.data[4], 0)) Serial.println(F("0x10 MAF Air Flow Rate"));
					if(bitRead(MyCANFrame.data[5], 7)) Serial.println(F("0x11 Throttle Position"));
					if(bitRead(MyCANFrame.data[5], 6)) Serial.println(F("0x12 Commanded secondary air status"));
					if(bitRead(MyCANFrame.data[5], 5)) Serial.println(F("0x13 Oxygen sensors present (in 2 banks) "));
					if(bitRead(MyCANFrame.data[5], 4)) Serial.println(F("0x14 Oxygen Sensor 1"));
					if(bitRead(MyCANFrame.data[5], 3)) Serial.println(F("0x15 Oxygen Sensor 2"));
					if(bitRead(MyCANFrame.data[5], 2)) Serial.println(F("0x16 Oxygen Sensor 3"));
					if(bitRead(MyCANFrame.data[5], 1)) Serial.println(F("0x17 Oxygen Sensor 4"));
					if(bitRead(MyCANFrame.data[5], 0)) Serial.println(F("0x18 Oxygen Sensor 5"));
					if(bitRead(MyCANFrame.data[6], 7)) Serial.println(F("0x19 Oxygen Sensor 6"));
					if(bitRead(MyCANFrame.data[6], 6)) Serial.println(F("0x1A Oxygen Sensor 7"));
					if(bitRead(MyCANFrame.data[6], 5)) Serial.println(F("0x1B Oxygen Sensor 8"));
					if(bitRead(MyCANFrame.data[6], 4)) Serial.println(F("0x1C Conforming OBD standards"));
					if(bitRead(MyCANFrame.data[6], 3)) Serial.println(F("0x1D Oxygen sensors present"));
					if(bitRead(MyCANFrame.data[6], 2)) Serial.println(F("0x1E Aux input status"));
					if(bitRead(MyCANFrame.data[6], 1)) Serial.println(F("0x1F Run time since engine start"));
					if(bitRead(MyCANFrame.data[6], 0)) Serial.println(F("0x20 PIDs supported [21 40]"));
				}	
				else if(PID_ID == PID_PIDsSupported21to40){
					if(bitRead(MyCANFrame.data[3], 7)) Serial.println(F("0x21 Distance with MIL on"));
					if(bitRead(MyCANFrame.data[3], 6)) Serial.println(F("0x22 Fuel Rail Pressure"));
					if(bitRead(MyCANFrame.data[3], 5)) Serial.println(F("0x23 Fuel Rail Gauge Pressure"));
					if(bitRead(MyCANFrame.data[3], 4)) Serial.println(F("0x24 Oxygen Sensor 1"));
					if(bitRead(MyCANFrame.data[3], 3)) Serial.println(F("0x25 Oxygen Sensor 2"));
					if(bitRead(MyCANFrame.data[3], 2)) Serial.println(F("0x26 Oxygen Sensor 3"));
					if(bitRead(MyCANFrame.data[3], 1)) Serial.println(F("0x27 Oxygen Sensor 4"));
					if(bitRead(MyCANFrame.data[3], 0)) Serial.println(F("0x28 Oxygen Sensor 5"));
					if(bitRead(MyCANFrame.data[4], 7)) Serial.println(F("0x29 Oxygen Sensor 6"));
					if(bitRead(MyCANFrame.data[4], 6)) Serial.println(F("0x2A Oxygen Sensor 7"));
					if(bitRead(MyCANFrame.data[4], 5)) Serial.println(F("0x2B Oxygen Sensor 8"));
					if(bitRead(MyCANFrame.data[4], 4)) Serial.println(F("0x2C Commanded EGR"));
					if(bitRead(MyCANFrame.data[4], 3)) Serial.println(F("0x2D EGR Error"));
					if(bitRead(MyCANFrame.data[4], 2)) Serial.println(F("0x2E Commanded evaporative purge"));
					if(bitRead(MyCANFrame.data[4], 1)) Serial.println(F("0x2F Fuel Tank Level Input"));
					if(bitRead(MyCANFrame.data[4], 0)) Serial.println(F("0x30 Warm-ups since codes cleared"));
					if(bitRead(MyCANFrame.data[5], 7)) Serial.println(F("0x31 Distance since codes cleared"));
					if(bitRead(MyCANFrame.data[5], 6)) Serial.println(F("0x32 Evap. System Vapor Pressure"));
					if(bitRead(MyCANFrame.data[5], 5)) Serial.println(F("0x33 Abs Barometric Pressure"));
					if(bitRead(MyCANFrame.data[5], 4)) Serial.println(F("0x34 Oxygen Sensor 1"));
					if(bitRead(MyCANFrame.data[5], 3)) Serial.println(F("0x35 Oxygen Sensor 2"));
					if(bitRead(MyCANFrame.data[5], 2)) Serial.println(F("0x36 Oxygen Sensor 3"));
					if(bitRead(MyCANFrame.data[5], 1)) Serial.println(F("0x37 Oxygen Sensor 4"));
					if(bitRead(MyCANFrame.data[5], 0)) Serial.println(F("0x38 Oxygen Sensor 5"));
					if(bitRead(MyCANFrame.data[6], 7)) Serial.println(F("0x39 Oxygen Sensor 6"));
					if(bitRead(MyCANFrame.data[6], 6)) Serial.println(F("0x3A Oxygen Sensor 7"));
					if(bitRead(MyCANFrame.data[6], 5)) Serial.println(F("0x3B Oxygen Sensor 8"));
					if(bitRead(MyCANFrame.data[6], 4)) Serial.println(F("0x3C Cat Temp: B1, S1"));
					if(bitRead(MyCANFrame.data[6], 3)) Serial.println(F("0x3D Cat Temp: B2, S1"));
					if(bitRead(MyCANFrame.data[6], 2)) Serial.println(F("0x3E Cat Temp: B1, S2"));
					if(bitRead(MyCANFrame.data[6], 1)) Serial.println(F("0x3F Cat Temp: B2, S2"));
					if(bitRead(MyCANFrame.data[6], 0)) Serial.println(F("0x40 PIDs supported [41 60]"));
					}
				else if(PID_ID == PID_PIDsSupported41to60){
					if(bitRead(MyCANFrame.data[3], 7)) Serial.println(F("0x41 Monitor status this drive cycle"));
					if(bitRead(MyCANFrame.data[3], 6)) Serial.println(F("0x42 Control Module Voltage"));
					if(bitRead(MyCANFrame.data[3], 5)) Serial.println(F("0x43 Absolute Load Value"));
					if(bitRead(MyCANFrame.data[3], 4)) Serial.println(F("0x44 Fuel–Air commanded equivalence ratio"));
					if(bitRead(MyCANFrame.data[3], 3)) Serial.println(F("0x45 Relative TPS"));
					if(bitRead(MyCANFrame.data[3], 2)) Serial.println(F("0x46 Ambient Air Temp"));
					if(bitRead(MyCANFrame.data[3], 1)) Serial.println(F("0x47 Absolute TPS B"));
					if(bitRead(MyCANFrame.data[3], 0)) Serial.println(F("0x48 Absolute TPS C"));
					if(bitRead(MyCANFrame.data[4], 7)) Serial.println(F("0x49 Absolute TPS D"));
					if(bitRead(MyCANFrame.data[4], 6)) Serial.println(F("0x4A Absolute TPS E"));
					if(bitRead(MyCANFrame.data[4], 5)) Serial.println(F("0x4B Absolute TPS F"));
					if(bitRead(MyCANFrame.data[4], 4)) Serial.println(F("0x4C Commanded throttle actuator"));
					if(bitRead(MyCANFrame.data[4], 3)) Serial.println(F("0x4D Time run with MIL on"));
					if(bitRead(MyCANFrame.data[4], 2)) Serial.println(F("0x4E Time since trouble codes cleared"));
					if(bitRead(MyCANFrame.data[4], 1)) Serial.println(F("0x4F Max value for AFR, oxygen sensor voltage, oxygen sensor current, and intake MAP"));
					if(bitRead(MyCANFrame.data[4], 0)) Serial.println(F("0x50 Max value for air flow rate from MAF sensor"));
					if(bitRead(MyCANFrame.data[5], 7)) Serial.println(F("0x51 Fuel Type"));
					if(bitRead(MyCANFrame.data[5], 6)) Serial.println(F("0x52 Ethanol fuel %"));
					if(bitRead(MyCANFrame.data[5], 5)) Serial.println(F("0x53 Absolute Evap system Vapor Pressure"));
					if(bitRead(MyCANFrame.data[5], 4)) Serial.println(F("0x54 Evap system vapor pressure"));
					if(bitRead(MyCANFrame.data[5], 3)) Serial.println(F("0x55 Short term secondary oxygen sensor trim"));
					if(bitRead(MyCANFrame.data[5], 2)) Serial.println(F("0x56 Long term secondary oxygen sensor trim"));
					if(bitRead(MyCANFrame.data[5], 1)) Serial.println(F("0x57 Short term secondary oxygen sensor trim, A: bank 2, B: bank 4"));
					if(bitRead(MyCANFrame.data[5], 0)) Serial.println(F("0x58 Long term secondary oxygen sensor trim, A: bank 2, B: bank 4"));
					if(bitRead(MyCANFrame.data[6], 7)) Serial.println(F("0x59 Fuel rail abs pressure"));
					if(bitRead(MyCANFrame.data[6], 6)) Serial.println(F("0x5A Relative accelerator pedal position"));
					if(bitRead(MyCANFrame.data[6], 5)) Serial.println(F("0x5B Hybrid battery remaining life"));
					if(bitRead(MyCANFrame.data[6], 4)) Serial.println(F("0x5C Engine oil temp"));
					if(bitRead(MyCANFrame.data[6], 3)) Serial.println(F("0x5D Fuel inj timing"));
					if(bitRead(MyCANFrame.data[6], 2)) Serial.println(F("0x5E Engine fuel rate"));
					if(bitRead(MyCANFrame.data[6], 1)) Serial.println(F("0x5F Emission requirements"));
					if(bitRead(MyCANFrame.data[6], 0)) Serial.println(F("0x60 PIDs supported [61 80]"));
				}
				else if(PID_ID == PID_PIDsSupported61to80){
					if(bitRead(MyCANFrame.data[3], 7)) Serial.println(F("0x61 Driver demand engine % torque"));
					if(bitRead(MyCANFrame.data[3], 6)) Serial.println(F("0x62 Actual engine % torque"));
					if(bitRead(MyCANFrame.data[3], 5)) Serial.println(F("0x63 Engine ref torque"));
					if(bitRead(MyCANFrame.data[3], 4)) Serial.println(F("0x64 Engine % torque data"));
					if(bitRead(MyCANFrame.data[3], 3)) Serial.println(F("0x65 Aux input / output supported"));
					if(bitRead(MyCANFrame.data[3], 2)) Serial.println(F("0x66 MAF sensor"));
					if(bitRead(MyCANFrame.data[3], 1)) Serial.println(F("0x67 Engine coolant temp"));
					if(bitRead(MyCANFrame.data[3], 0)) Serial.println(F("0x68 Intake air temp sensor"));
					if(bitRead(MyCANFrame.data[4], 7)) Serial.println(F("0x69 Commanded EGR and EGR Error"));
					if(bitRead(MyCANFrame.data[4], 6)) Serial.println(F("0x6A Commanded Diesel intake air flow control and rel intake air flow pos"));
					if(bitRead(MyCANFrame.data[4], 5)) Serial.println(F("0x6B Exhaust gas recirculation temp"));
					if(bitRead(MyCANFrame.data[4], 4)) Serial.println(F("0x6C Commanded throttle actuator control and relative throttle position"));
					if(bitRead(MyCANFrame.data[4], 3)) Serial.println(F("0x6D Fuel pressure control sys"));
					if(bitRead(MyCANFrame.data[4], 2)) Serial.println(F("0x6E Injection pressure control sys"));
					if(bitRead(MyCANFrame.data[4], 1)) Serial.println(F("0x6F Turbo compressor inlet pressure"));
					if(bitRead(MyCANFrame.data[4], 0)) Serial.println(F("0x70 Boost pressure control"));
					if(bitRead(MyCANFrame.data[5], 7)) Serial.println(F("0x71 Vari Geometry turbo (VGT) ctrl"));
					if(bitRead(MyCANFrame.data[5], 6)) Serial.println(F("0x72 Wastegate ctrl"));
					if(bitRead(MyCANFrame.data[5], 5)) Serial.println(F("0x73 Exhaust pressure"));
					if(bitRead(MyCANFrame.data[5], 4)) Serial.println(F("0x74 Turbo RPM"));
					if(bitRead(MyCANFrame.data[5], 3)) Serial.println(F("0x75 Turbo temp"));
					if(bitRead(MyCANFrame.data[5], 2)) Serial.println(F("0x76 Turbo temp"));
					if(bitRead(MyCANFrame.data[5], 1)) Serial.println(F("0x77 Charge air cooler temp (CACT)"));
					if(bitRead(MyCANFrame.data[5], 0)) Serial.println(F("0x78 EGT B1"));
					if(bitRead(MyCANFrame.data[6], 7)) Serial.println(F("0x79 EGT B2"));
					if(bitRead(MyCANFrame.data[6], 6)) Serial.println(F("0x7A Diesel particulate filter (DPF)"));
					if(bitRead(MyCANFrame.data[6], 5)) Serial.println(F("0x7B Diesel particulate filter (DPF)"));
					if(bitRead(MyCANFrame.data[6], 4)) Serial.println(F("0x7C Diesel Particulate filter (DPF) temp"));
					if(bitRead(MyCANFrame.data[6], 3)) Serial.println(F("0x7D NOx NTE (Not-To-Exceed) control area status"));
					if(bitRead(MyCANFrame.data[6], 2)) Serial.println(F("0x7E PM NTE (Not-To-Exceed) control area status"));
					if(bitRead(MyCANFrame.data[6], 1)) Serial.println(F("0x7F Engine run time"));
					if(bitRead(MyCANFrame.data[6], 0)) Serial.println(F("0x80 PIDs supported [81 A0]"));
				}
				else if(PID_ID == PID_PIDsSupported81toA0){
					if(bitRead(MyCANFrame.data[3], 7)) Serial.println(F("0x81 Engine run time for Auxiliary Emissions Control Device(AECD) "));
					if(bitRead(MyCANFrame.data[3], 6)) Serial.println(F("0x82 Engine run time for Auxiliary Emissions Control Device(AECD) "));
					if(bitRead(MyCANFrame.data[3], 5)) Serial.println(F("0x83 NOx sensor"));
					if(bitRead(MyCANFrame.data[3], 4)) Serial.println(F("0x84 Manifold surface temp"));
					if(bitRead(MyCANFrame.data[3], 3)) Serial.println(F("0x85 NOx reagent system"));
					if(bitRead(MyCANFrame.data[3], 2)) Serial.println(F("0x86 Particulate matter (PM) sensor"));
					if(bitRead(MyCANFrame.data[3], 1)) Serial.println(F("0x87 Intake MAP"));
					if(bitRead(MyCANFrame.data[3], 0)) Serial.println(F("0x88 SCR Induce System"));
					if(bitRead(MyCANFrame.data[4], 7)) Serial.println(F("0x89 Run Time for AECD #11-#15 "));
					if(bitRead(MyCANFrame.data[4], 6)) Serial.println(F("0x8A Run Time for AECD #16-#20"));
					if(bitRead(MyCANFrame.data[4], 5)) Serial.println(F("0x8B Diesel Aftertreatment"));
					if(bitRead(MyCANFrame.data[4], 4)) Serial.println(F("0x8C O2 Sensor (Wide Range)"));
					if(bitRead(MyCANFrame.data[4], 3)) Serial.println(F("0x8D TPS G"));
					if(bitRead(MyCANFrame.data[4], 2)) Serial.println(F("0x8E Engine Friction % Torque"));
					if(bitRead(MyCANFrame.data[4], 1)) Serial.println(F("0x8F PM Sensor Bank 1 & 2"));
					if(bitRead(MyCANFrame.data[4], 0)) Serial.println(F("0x90 WWH-OBD Vehicle OBD System Information"));
					if(bitRead(MyCANFrame.data[5], 7)) Serial.println(F("0x91 WWH-OBD Vehicle OBD System Information"));
					if(bitRead(MyCANFrame.data[5], 6)) Serial.println(F("0x92 Fuel Sys Ctrl"));
					if(bitRead(MyCANFrame.data[5], 5)) Serial.println(F("0x93 WWH-OBD Vehicle OBD Counters support"));
					if(bitRead(MyCANFrame.data[5], 4)) Serial.println(F("0x94 NOx Warning And Inducement System"));
					if(bitRead(MyCANFrame.data[5], 3)) Serial.println(F("0x95 Unknown PID"));
					if(bitRead(MyCANFrame.data[5], 2)) Serial.println(F("0x96 Unknown PID"));
					if(bitRead(MyCANFrame.data[5], 1)) Serial.println(F("0x97 Unknown PID"));
					if(bitRead(MyCANFrame.data[5], 0)) Serial.println(F("0x98 EGT Sensor"));
					if(bitRead(MyCANFrame.data[6], 7)) Serial.println(F("0x99 EGT Sensor"));
					if(bitRead(MyCANFrame.data[6], 6)) Serial.println(F("0x9A Hybrid/EV Sys Data, Bat, Volt"));
					if(bitRead(MyCANFrame.data[6], 5)) Serial.println(F("0x9B Diesel Exhaust Fluid Sensor Data"));
					if(bitRead(MyCANFrame.data[6], 4)) Serial.println(F("0x9C O2 Sensor Data"));
					if(bitRead(MyCANFrame.data[6], 3)) Serial.println(F("0x9D Engine Fuel Rate"));
					if(bitRead(MyCANFrame.data[6], 2)) Serial.println(F("0x9E Engine Exhaust Flow Rate"));
					if(bitRead(MyCANFrame.data[6], 1)) Serial.println(F("0x9F Fuel System % Use"));
					if(bitRead(MyCANFrame.data[6], 0)) Serial.println(F("0xA0 PIDs supported [A1 C0]"));
				}
				else if(PID_ID == PID_PIDsSupportedA1toC0){
					if(bitRead(MyCANFrame.data[3], 7)) Serial.println(F("0xA1 NOx Sensor Corrected Data"));
					if(bitRead(MyCANFrame.data[3], 6)) Serial.println(F("0xA2 Cylinder Fuel Rate"));
					if(bitRead(MyCANFrame.data[3], 5)) Serial.println(F("0xA3 Evap System Vapor Pressure"));
					if(bitRead(MyCANFrame.data[3], 4)) Serial.println(F("0xA4 Transmission Actual Gear"));
					if(bitRead(MyCANFrame.data[3], 3)) Serial.println(F("0xA5 Diesel Exhaust Fluid Dosing"));
					if(bitRead(MyCANFrame.data[3], 2)) Serial.println(F("0xA6 Odometer"));		
				}		
				++PIDArrayPtr;
				if(PIDArrayPtr == 6) PIDArrayPtr = 0;
			}
		}    
	}
}