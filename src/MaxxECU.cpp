#include "MaxxECU.h"

void Maxx::initStruct(Signals& mySignals){
	mySignals.RPM = 0;
	mySignals.TPS = 0;
	mySignals.MAP = 0;
	mySignals.Lambda = 0;
	mySignals.LambdaA = 0;
	mySignals.LambdaB = 0;
	mySignals.IgnitionAngle = 0;
	mySignals.IgnitionCut = 0;
	mySignals.FuelPulsewidth = 0;
	mySignals.FuelDuty = 0;
	mySignals.FuelCut = 0;
	mySignals.VehicleSpeed = 0;
	mySignals.UndrivenWheelsAvgSpeed = 0;
	mySignals.DrivenWheelsAvgSpeed = 0;
	mySignals.WheelSlip = 0;
	mySignals.TargetSlip = 0;
	mySignals.TractionCtrlPwrLimit = 0;
	mySignals.LambdaCorrA = 0;
	mySignals.LambdaCorrB = 0;
	mySignals.FirmwareVersion = 0;
	mySignals.BatteryVoltage = 0;
	mySignals.BaroPressure = 0;
	mySignals.IntakeAirTemp = 0;
	mySignals.CoolantTemp = 0;
	mySignals.TotalFuelTrim = 0;
	mySignals.EthanolConcentration = 0;
	mySignals.TotalIgnitionComp = 0;
	mySignals.EGT1 = 0;
	mySignals.EGT2 = 0;
	mySignals.EGT3 = 0;
	mySignals.EGT4 = 0;
	mySignals.EGT5 = 0;
	mySignals.EGT6 = 0;
	mySignals.EGT7 = 0;
	mySignals.EGT8 = 0;
	mySignals.EGTHighest = 0;
	mySignals.EGTDifference = 0;
	mySignals.CPUTemp = 0;
	mySignals.ErrorCodeCount = 0;
	mySignals.LostSyncCount = 0;
	mySignals.UserAnalogInput1 = 0;
	mySignals.UserAnalogInput2 = 0;
	mySignals.UserAnalogInput3 = 0;
	mySignals.UserAnalogInput4 = 0;
	mySignals.Gear = 0;
	mySignals.BoostSolenoidDuty = 0;
	mySignals.Spare1 = 0;
	mySignals.Spare2 = 0;  
}

void Maxx::processFrame(CANMessage MyCANFrame, Signals& mySignals){
	switch(MyCANFrame.id){
	case 0x520:
		mySignals.RPM = MyCANFrame.data16[0];
		mySignals.TPS = MyCANFrame.data16[1];
		mySignals.MAP = MyCANFrame.data16[2];
		mySignals.Lambda = MyCANFrame.data16[3];
		break;
	case 0x521:
		mySignals.LambdaA = MyCANFrame.data16[0];
		mySignals.LambdaB = MyCANFrame.data16[1];
		mySignals.IgnitionAngle = MyCANFrame.data16[2];
		mySignals.IgnitionCut = MyCANFrame.data16[3];
		break;
	case 0x522:
		mySignals.FuelPulsewidth = MyCANFrame.data16[0];
		mySignals.FuelDuty = MyCANFrame.data16[1];
		mySignals.FuelCut = MyCANFrame.data16[2];
		mySignals.VehicleSpeed = MyCANFrame.data16[3];
		break;
	case 0x523:
		mySignals.UndrivenWheelsAvgSpeed = MyCANFrame.data16[0];
		mySignals.DrivenWheelsAvgSpeed = MyCANFrame.data16[1];
		mySignals.WheelSlip = MyCANFrame.data16[2];
		mySignals.TargetSlip = MyCANFrame.data16[3];
		break;
	case 0x524:
		mySignals.TractionCtrlPwrLimit = MyCANFrame.data16[0];
		mySignals.LambdaCorrA = MyCANFrame.data16[1];
		mySignals.LambdaCorrB = MyCANFrame.data16[2];
		mySignals.FirmwareVersion = MyCANFrame.data16[3];
		break;
	case 0x530:
		mySignals.BatteryVoltage = MyCANFrame.data16[0];
		mySignals.BaroPressure = MyCANFrame.data16[1];
		mySignals.IntakeAirTemp = MyCANFrame.data16[2];
		mySignals.CoolantTemp = MyCANFrame.data16[3];
		break;
	case 0x531:
		mySignals.TotalFuelTrim = MyCANFrame.data16[0];
		mySignals.EthanolConcentration = MyCANFrame.data16[1];
		mySignals.TotalIgnitionComp = MyCANFrame.data16[2];
		mySignals.EGT1 = MyCANFrame.data16[3];
		break;
	case 0x532:
		mySignals.EGT2 = MyCANFrame.data16[0];
		mySignals.EGT3 = MyCANFrame.data16[1];
		mySignals.EGT4 = MyCANFrame.data16[2];
		mySignals.EGT5 = MyCANFrame.data16[3];
		break;
	case 0x533:
		mySignals.EGT6 = MyCANFrame.data16[0];
		mySignals.EGT7 = MyCANFrame.data16[1];
		mySignals.EGT8 = MyCANFrame.data16[2];
		mySignals.EGTHighest = MyCANFrame.data16[3];
		break;
	case 0x534:
		mySignals.EGTDifference = MyCANFrame.data16[0];
		mySignals.CPUTemp = MyCANFrame.data16[1];
		mySignals.ErrorCodeCount = MyCANFrame.data16[2];
		mySignals.LostSyncCount = MyCANFrame.data16[3];
		break;
	case 0x535:
		mySignals.UserAnalogInput1 = MyCANFrame.data16[0];
		mySignals.UserAnalogInput2 = MyCANFrame.data16[1];
		mySignals.UserAnalogInput3 = MyCANFrame.data16[2];
		mySignals.UserAnalogInput4 = MyCANFrame.data16[3];
		break;
	case 0x536:
		mySignals.Gear = MyCANFrame.data16[0];
		mySignals.BoostSolenoidDuty = MyCANFrame.data16[1];
		mySignals.Spare1 = MyCANFrame.data16[2];
		mySignals.Spare2 = MyCANFrame.data16[3];
		break;
	}  
}
