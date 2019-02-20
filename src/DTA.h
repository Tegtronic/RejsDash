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
		int16_t RPM;                                // Factor 1, unit rpm
		int16_t TPS;                                // Factor 1, unit %
		int16_t WaterTemp;                          // Factor 1, Celsius
		int16_t AirTemp;                            // Factor 1, Celsius
		int16_t MAP;                                // Factor 1, unit kPa
		int16_t Lambda;                             // Factor 0.001, unit lambda
		int16_t KPH;                                // Factor 0.1, unit km/h
		int16_t OilP;                               // Factor 1, unit kPa
		int16_t FuelP;                              // Factor 1, unit kPa   
		int16_t OilTemp;                            // Factor 1, unit Celsius
		int16_t Volts;                              // Factor 0.1, unit Volt
		int16_t FuelConPerDist;                     // Factor 0.1, unit L/100Km
		int16_t Gear;                               // Factor 1
		int16_t AdvanceDeg;                         // Factor 0.1, unit degrees BTDC
		int16_t InjectionMS;                        // Factor 0.01, unit ms
		int16_t FuelConPerH;                        // Factor 0.1, unit L/h
		int16_t Ana1;                               // Factor 1, unit mV
		int16_t Ana2;                               // Factor 1, unit mV
		int16_t Ana3;                               // Factor 1, unit mV
		int16_t CamAdvance;                         // Factor 0.1, unit degrees
		int16_t CamTarg;                            // Factor 0.1, unit degrees
		int16_t CamPWM;                             // Factor 1, unit %
		int16_t CrankErrors;                        // Factor 1
		int16_t CamErrors;                          // Factor 1
		int16_t Cam2Adv;                            // Factor 0.1, unit degrees
		int16_t Cam2Targ;                           // Factor 0.1, unit degrees
		int16_t Cam2PWM;                            // Factor 1, unit %
		int16_t External5V;                         // Factor unknown
		int16_t InjDutyCycle;                       // Factor 0.1, unit %
		int16_t LambdaPIDTarg;                      // Factor unknown
		int16_t LambdaPIDAdj;                       // Factor unknown
		int16_t ECUSwitches;                        // 0 LAUNCH BUTTON PRESSED, 1 LAUNCH ACTIVE, 2 TRACTION ON, 3 TRACTION WET, 4 FUEL PUMP ON, 5 FAN OUTPUT ON
		int16_t RDSpeed;                            // Factor unknown
		int16_t RUDSpeed;                           // Factor unknown
		int16_t LDSpeed;                            // Factor unknown
		int16_t LUDSpeed;                           // Factor unknown
	};

	void initStruct(Signals& mySignals);

	void processFrame(CANMessage MyCANFrame, Signals& mySignals);
}

