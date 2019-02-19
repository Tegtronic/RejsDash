#include "DTA.h"

void DTA::initStruct(Signals& mySignals){
	mySignals.RPM = 0;
	mySignals.TPS = 0;
	mySignals.WaterTemp = 0;
	mySignals.AirTemp = 0;
	mySignals.MAP = 0;
	mySignals.Lambda = 0;
	mySignals.KPH = 0;
	mySignals.OilP = 0;
	mySignals.FuelP = 0;
	mySignals.OilTemp = 0;
	mySignals.Volts = 0;
	mySignals.FuelConPerDist = 0;
	mySignals.Gear = 0;
	mySignals.AdvanceDeg = 0;
	mySignals.InjectionMS = 0;
	mySignals.FuelConPerH = 0;
	mySignals.Ana1 = 0;
	mySignals.Ana2 = 0;
	mySignals.Ana3 = 0;
	mySignals.CamAdvance = 0;
	mySignals.CamTarg = 0;
	mySignals.CamPWM = 0;
	mySignals.CrankErrors = 0;
	mySignals.CamErrors = 0;
	mySignals.Cam2Adv = 0;
	mySignals.Cam2Targ = 0;
	mySignals.Cam2PWM  = 0;
	mySignals.External5V  = 0;
	mySignals.InjDutyCycle = 0;
	mySignals.LambdaPIDTarg = 0;
	mySignals.LambdaPIDAdj = 0;
	mySignals.ECUSwitches = 0;
	mySignals.RDSpeed = 0;
	mySignals.RUDSpeed = 0;
	mySignals.LDSpeed = 0;
	mySignals.LUDSpeed = 0;
}

void DTA::processFrame(CANMessage MyCANFrame, Signals& mySignals){
	switch(MyCANFrame.id){
	case 0x2000:
		mySignals.RPM = MyCANFrame.data16[0];
		mySignals.TPS = MyCANFrame.data16[1];
		mySignals.WaterTemp = MyCANFrame.data16[2];
		mySignals.AirTemp = MyCANFrame.data16[3];
		break;
	case 0x2001:
		mySignals.MAP = MyCANFrame.data16[0];
		mySignals.Lambda = MyCANFrame.data16[1];
		mySignals.KPH = MyCANFrame.data16[2];
		mySignals.OilP = MyCANFrame.data16[3];
		break;
	case 0x2002:
		mySignals.FuelP = MyCANFrame.data16[0];
		mySignals.OilTemp = MyCANFrame.data16[1];
		mySignals.Volts = MyCANFrame.data16[2];
		mySignals.FuelConPerDist = MyCANFrame.data16[3];
		break;
	case 0x2003:
		mySignals.Gear = MyCANFrame.data16[0];
		mySignals.AdvanceDeg = MyCANFrame.data16[1];
		mySignals.InjectionMS = MyCANFrame.data16[2];
		mySignals.FuelConPerH = MyCANFrame.data16[3];
		break;
	case 0x2004:
		mySignals.Ana1 = MyCANFrame.data16[0];
		mySignals.Ana2 = MyCANFrame.data16[1];
		mySignals.Ana3= MyCANFrame.data16[2];
		mySignals.CamAdvance = MyCANFrame.data16[3];
		break;
	case 0x2005:
		mySignals.CamTarg = MyCANFrame.data16[0];
		mySignals.CamPWM = MyCANFrame.data16[1];
		mySignals.CrankErrors = MyCANFrame.data16[2];
		mySignals.CamErrors = MyCANFrame.data16[3];
		break;
	case 0x2006:
		mySignals.Cam2Adv = MyCANFrame.data16[0];
		mySignals.Cam2Targ = MyCANFrame.data16[1];
		mySignals.Cam2PWM = MyCANFrame.data16[2];
		mySignals.External5V = MyCANFrame.data16[3];
		break;
	case 0x2007:
		mySignals.InjDutyCycle = MyCANFrame.data16[0];
		mySignals.LambdaPIDTarg = MyCANFrame.data16[1];
		mySignals.LambdaPIDAdj = MyCANFrame.data16[2];
		mySignals.ECUSwitches = MyCANFrame.data16[3];
		break;
	case 0x2008:
		mySignals.RDSpeed = MyCANFrame.data16[0];
		mySignals.RUDSpeed = MyCANFrame.data16[1];
		mySignals.LDSpeed = MyCANFrame.data16[2];
		mySignals.LUDSpeed = MyCANFrame.data16[3];
		break;
	}  
}
