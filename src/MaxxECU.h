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

namespace Maxx{
	struct Signals{
		int16_t RPM;                                // Factor 1, unit rpm
		int16_t TPS;                                // Factor 0.1, unit %
		int16_t MAP;                                // Factor 0.1, unit kPa
		int16_t Lambda;                             // Factor 0.001, unit lambda
		int16_t LambdaA;                            // Factor 0.001, unit lambda
		int16_t LambdaB;                            // Factor 0.001, unit lambda
		int16_t IgnitionAngle;                      // Factor 0.1, unit degrees BTDC
		int16_t IgnitionCut;                        // Factor 1, unit %
		int16_t FuelPulsewidth;                     // Factor 0.01, unit ms
		int16_t FuelDuty;                           // Factor 0.1, unit %
		int16_t FuelCut;                            // Factor 1, unit %
		int16_t VehicleSpeed;                       // Factor 0.1, unit km/h
		int16_t UndrivenWheelsAvgSpeed;             // Factor 0.1, unit km/h
		int16_t DrivenWheelsAvgSpeed;               // Factor 0.1, unit km/h
		int16_t WheelSlip;                          // Factor 0.1, unit %
		int16_t TargetSlip;                         // Factor 0.1, unit %
		int16_t TractionCtrlPwrLimit;               // Factor 0.1, unit %
		int16_t LambdaCorrA;                        // Factor 0.1, unit %
		int16_t LambdaCorrB;                        // Factor 0.1, unit %
		int16_t FirmwareVersion;                    // Factor 0.01 
		int16_t BatteryVoltage;                     // Factor 0.01, unit Volt
		int16_t BaroPressure;                       // Factor 0.1, unit kPa
		int16_t IntakeAirTemp;                      // Factor 0.1, unit Celsius
		int16_t CoolantTemp;                        // Factor 0.1, unit Celsius
		int16_t TotalFuelTrim;                      // Factor 0.1, unit %
		int16_t EthanolConcentration;               // Factor 0.1, unit %
		int16_t TotalIgnitionComp;                  // Factor 0.1, unit degrees
		int16_t EGT1;                               // Factor 1, unit Celsius
		int16_t EGT2;                               // Factor 1, unit Celsius
		int16_t EGT3;                               // Factor 1, unit Celsius
		int16_t EGT4;                               // Factor 1, unit Celsius
		int16_t EGT5;                               // Factor 1, unit Celsius
		int16_t EGT6;                               // Factor 1, unit Celsius
		int16_t EGT7;                               // Factor 1, unit Celsius
		int16_t EGT8;                               // Factor 1, unit Celsius
		int16_t EGTHighest;                         // Factor 1, unit Celsius
		int16_t EGTDifference;                      // Factor 1, unit Celsius
		int16_t CPUTemp;                            // Factor 1, unit Celsius
		int16_t ErrorCodeCount;                     // Factor 1
		int16_t LostSyncCount;                      // Factor 1
		int16_t UserAnalogInput1;                   // Factor 0.1
		int16_t UserAnalogInput2;                   // Factor 0.1
		int16_t UserAnalogInput3;                   // Factor 0.1
		int16_t UserAnalogInput4;                   // Factor 0.1
		int16_t Gear;                               // Factor 1
		int16_t BoostSolenoidDuty;                  // Factor 0.1, unit %
		int16_t Spare1;                             // Factor 1
		int16_t Spare2;                             // Factor 1 
	};

	void initStruct(Signals& mySignals);

	void processFrame(CANMessage MyCANFrame, Signals& mySignals);
}

