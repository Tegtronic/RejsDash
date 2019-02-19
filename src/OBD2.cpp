#include "OBD2.h"

namespace{
	bool RequestPending;  
}

bool OBD2::requestIsPending(){
	return RequestPending;
}

void OBD2::requestPID(ACAN2515& myCAN, uint8_t TargetPID){
	CANMessage frame;
	frame.id = 0x7DF;
	frame.len = 8;
	frame.data[0] = 0x02;    		// Number of additional bytes
	frame.data[1] = 0x01;     		// Service 01 = show current data
	frame.data[2] = TargetPID;      // 0x0C = PID "Engine RPM"
	frame.data[3] = 0x55;     		// Rest of bytes is "Don't Care" represented by 0x55
	frame.data[4] = 0x55;
	frame.data[5] = 0x55;
	frame.data[6] = 0x55;
	frame.data[7] = 0x55;

	const bool ok = myCAN.tryToSend (frame);
	if (!ok) {
		Serial.println("CAN TX Error!");
	}
	else RequestPending = true;  
}

bool OBD2::processFrame(float &val, byte &PID_ID, CANMessage &MyCANFrame){
	if(MyCANFrame.data[1] == 0x41){
		PID_ID = MyCANFrame.data[2];
		
		if(PID_ID == PID_PIDsSupported0to20){
			if(bitRead(MyCANFrame.data[3], 4)) Serial.println("Supports PID 0x04 - Calculated engine load");
			if(bitRead(MyCANFrame.data[3], 3)) Serial.println("Supports PID 0x05 - Engine Coolant Temperature");
			if(bitRead(MyCANFrame.data[3], 2)) Serial.println("Supports PID 0x06 - Short Term Fuel Trim Bank1");
			if(bitRead(MyCANFrame.data[3], 1)) Serial.println("Supports PID 0x07 - Long Term Fuel Trim Bank1");
			if(bitRead(MyCANFrame.data[3], 0)) Serial.println("Supports PID 0x08 - Short Term Fuel Trim Bank2");
			if(bitRead(MyCANFrame.data[4], 7)) Serial.println("Supports PID 0x09 - Long Term Fuel Trim Bank2");
			if(bitRead(MyCANFrame.data[4], 6)) Serial.println("Supports PID 0x0A - Fuel Pressure Gauge Pressure");
			if(bitRead(MyCANFrame.data[4], 5)) Serial.println("Supports PID 0x0B - Intake Manifold Absolute Pressure");
			if(bitRead(MyCANFrame.data[4], 4)) Serial.println("Supports PID 0x0C - Engine RPM");
			if(bitRead(MyCANFrame.data[4], 3)) Serial.println("Supports PID 0x0D - Vehicle Speed");
			if(bitRead(MyCANFrame.data[4], 2)) Serial.println("Supports PID 0x0E - Timing Advance");
			if(bitRead(MyCANFrame.data[4], 1)) Serial.println("Supports PID 0x0F - Intake Air Temperature");
			if(bitRead(MyCANFrame.data[4], 0)) Serial.println("Supports PID 0x10 - MAF Air Flow Rate");
			if(bitRead(MyCANFrame.data[5], 7)) Serial.println("Supports PID 0x11 - Throttle Position");
		}
		else if(PID_ID == PID_EngineCoolantTemperature){
			val = (float)MyCANFrame.data[3]-40.0;
		}
		else if(PID_ID == PID_EngineRPM){
			uint16_t tmpval = MyCANFrame.data[3];
			tmpval = tmpval << 8;
			tmpval += MyCANFrame.data[4];
			val = tmpval;
			val = val/4;
		}
		else if(PID_ID == PID_VehicleSpeed){
			val = (float)MyCANFrame.data[3];
		}
	}
	else{
		Serial.println("Error: Unexpected custom service response!");
		return false;
	}
	RequestPending = false;
	return true;
}
