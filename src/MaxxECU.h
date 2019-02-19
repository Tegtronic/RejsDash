#include <CANMessage.h>

#include <arduino.h>

/*
* http://www.maxxecu.com/webhelp/can-default_maxxecu_protocol.html
* Specification:
* •Can baud rate: 500kbit, 11-bit ID.
* •Little endian (least significant byte first).
* •All messages contains 4 16-bit values, 8 bytes per message.
* •MaxxECU has a built in termination resistor. External termination (120 ohm) is recommended for bus lengths over 1m.
* •Main connector: pin E1 = CAN H, pin E2 = CAN L.
* •Wiring loom: Twisted pink / gray, pink = CAN L, gray = CAN H.
* •Requires MaxxECU Firmware version 1.67 or newer.
*/

namespace Maxx
{
	struct Signals
	{
		int RPM;                                // Factor 1, unit rpm
		int TPS;                                // Factor 0.1, unit %
		int MAP;                                // Factor 0.1, unit kPa
		int Lambda;                             // Factor 0.001, unit lambda
		int LambdaA;                            // Factor 0.001, unit lambda
		int LambdaB;                            // Factor 0.001, unit lambda
		int IgnitionAngle;                      // Factor 0.1, unit degrees BTDC
		int IgnitionCut;                        // Factor 1, unit %
		int FuelPulsewidth;                     // Factor 0.01, unit ms
		int FuelDuty;                           // Factor 0.1, unit %
		int FuelCut;                            // Factor 1, unit %
		int VehicleSpeed;                       // Factor 0.1, unit km/h
		int UndrivenWheelsAvgSpeed;             // Factor 0.1, unit km/h
		int DrivenWheelsAvgSpeed;               // Factor 0.1, unit km/h
		int WheelSlip;                          // Factor 0.1, unit %
		int TargetSlip;                         // Factor 0.1, unit %
		int TractionCtrlPwrLimit;               // Factor 0.1, unit %
		int LambdaCorrA;                        // Factor 0.1, unit %
		int LambdaCorrB;                        // Factor 0.1, unit %
		int FirmwareVersion;                    // Factor 0.01 
		int BatteryVoltage;                     // Factor 0.01, unit Volt
		int BaroPressure;                       // Factor 0.1, unit kPa
		int IntakeAirTemp;                      // Factor 0.1, unit Celsius
		int CoolantTemp;                        // Factor 0.1, unit Celsius
		int TotalFuelTrim;                      // Factor 0.1, unit %
		int EthanolConcentration;               // Factor 0.1, unit %
		int TotalIgnitionComp;                  // Factor 0.1, unit degrees
		int EGT1;                               // Factor 1, unit Celsius
		int EGT2;                               // Factor 1, unit Celsius
		int EGT3;                               // Factor 1, unit Celsius
		int EGT4;                               // Factor 1, unit Celsius
		int EGT5;                               // Factor 1, unit Celsius
		int EGT6;                               // Factor 1, unit Celsius
		int EGT7;                               // Factor 1, unit Celsius
		int EGT8;                               // Factor 1, unit Celsius
		int EGTHighest;                         // Factor 1, unit Celsius
		int EGTDifference;                      // Factor 1, unit Celsius
		int CPUTemp;                            // Factor 1, unit Celsius
		int ErrorCodeCount;                     // Factor 1
		int LostSyncCount;                      // Factor 1
		int UserAnalogInput1;                   // Factor 0.1
		int UserAnalogInput2;                   // Factor 0.1
		int UserAnalogInput3;                   // Factor 0.1
		int UserAnalogInput4;                   // Factor 0.1
		int Gear;                               // Factor 1
		int BoostSolenoidDuty;                  // Factor 0.1, unit %
		int Spare1;                             // Factor 1
		int Spare2;                             // Factor 1 
	};

	void initStruct(Signals& mySignals);

	void processFrame(CANMessage MyCANFrame, Signals& mySignals);
}

