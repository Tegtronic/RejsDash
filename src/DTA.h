#include <CANMessage.h>

#include <arduino.h>

/*
* http://www.dtafast.co.uk/download_files/Manuals/S%20Series%20CAN%20Stream%20Generic.pdf
* CAN bus Baud Rate 1 MBd
* Identifiers All 29Bit
* 6 Data Packets
* All 8 Bytes Ea.
* Send Frequency10 -50Hz
* All Data Values 16 Bit Signed Sent LSB First (Little Endian)
*/

namespace DTA{
	struct Signals{
		int RPM;                                // Factor 1, unit rpm
		int TPS;                                // Factor 1, unit %
		int WaterTemp;                          // Factor 1, Celsius
		int AirTemp;                            // Factor 1, Celsius
		int MAP;                                // Factor 1, unit kPa
		int Lambda;                             // Factor 0.001, unit lambda
		int KPH;                                // Factor 0.1, unit km/h
		int OilP;                               // Factor 1, unit kPa
		int FuelP;                              // Factor 1, unit kPa   
		int OilTemp;                            // Factor 1, unit Celsius
		int Volts;                              // Factor 0.1, unit Volt
		int FuelConPerDist;                     // Factor 0.1, unit L/100Km
		int Gear;                               // Factor 1
		int AdvanceDeg;                         // Factor 0.1, unit degrees BTDC
		int InjectionMS;                        // Factor 0.01, unit ms
		int FuelConPerH;                        // Factor 0.1, unit L/h
		int Ana1;                               // Factor 1, unit mV
		int Ana2;                               // Factor 1, unit mV
		int Ana3;                               // Factor 1, unit mV
		int CamAdvance;                         // Factor 0.1, unit degrees
		int CamTarg;                            // Factor 0.1, unit degrees
		int CamPWM;                             // Factor 1, unit %
		int CrankErrors;                        // Factor 1
		int CamErrors;                          // Factor 1
		int Cam2Adv;                            // Factor 0.1, unit degrees
		int Cam2Targ;                           // Factor 0.1, unit degrees
		int Cam2PWM;                            // Factor 1, unit %
		int External5V;                         // Factor unknown
		int InjDutyCycle;                       // Factor 0.1, unit %
		int LambdaPIDTarg;                      // Factor unknown
		int LambdaPIDAdj;                       // Factor unknown
		int ECUSwitches;                        // 0 LAUNCH BUTTON PRESSED, 1 LAUNCH ACTIVE, 2 TRACTION ON, 3 TRACTION WET, 4 FUEL PUMP ON, 5 FAN OUTPUT ON
		int RDSpeed;                            // Factor unknown
		int RUDSpeed;                           // Factor unknown
		int LDSpeed;                            // Factor unknown
		int LUDSpeed;                           // Factor unknown
	};

	void initStruct(Signals& mySignals);

	void processFrame(CANMessage MyCANFrame, Signals& mySignals);
}

