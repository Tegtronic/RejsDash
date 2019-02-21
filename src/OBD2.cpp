#include "OBD2.h"

namespace{
	bool RequestPending;  
}

bool OBD2::requestIsPending(){
	return RequestPending;
}

void OBD2::setRequestPending(bool cmd)
{
	RequestPending = cmd;
}

void OBD2::requestPID(ACAN2515& myCAN, uint8_t TargetPID){
	CANMessage frame;
	frame.id = 0x7DF;
	frame.len = 8;
	frame.data[0] = 0x02;    		// Number of additional bytes
	frame.data[1] = 0x01;     		// Service 01 = show current data
	frame.data[2] = TargetPID;      // Requested PID
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
		
		if(PID_ID == PID_EngineCoolantTemperature){
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
		else{
			Serial.print(F("PID: "));
			Serial.print(PID_ID);
			Serial.println(F(" does not have a decoding routine yet, please add it in OBD2.cpp - Don't forget to add conversion formulas listed in OBD2 PID's wiki page!"));
		}
	}
	else{
		Serial.println(F("Error: Unexpected custom service response!"));
		return false;
	}
	RequestPending = false;
	return true;
}
