#include <ACAN2515.h>
#include <CANMessage.h>
#include <arduino.h>

#define REQUEST_TIMEOUT_MS 5000

/*
* https://en.wikipedia.org/wiki/OBD-II_PIDs
*/
#define PID_PIDsSupported0to20 0x00
#define PID_CalculatedEngineLoad 0x04
#define PID_EngineCoolantTemperature 0x05
#define PID_ShortTermFuelTrimBank1 0x06
#define PID_LongTermFuelTrimBank1 0x07
#define PID_ShortTermFuelTrimBank2 0x08
#define PID_LongTermFuelTrimBank2 0x09
#define PID_FuelPressureGaugePressure 0x0A
#define PID_IntakeManifoldAbsolutePressure 0x0B
#define PID_EngineRPM 0x0C
#define PID_VehicleSpeed 0x0D
#define PID_TimingAdvance 0x0E
#define PID_IntakeAirTemperature 0x0F
#define PID_MAFAirFlowRate 0x10
#define PID_ThrottlePosition 0x11
#define PID_PIDsSupported21to40 0x20
#define PID_FuelRailPressure 0x22
#define PID_FuelRailGaugePressure 0x23
#define PID_FuelTankLevelInput 0x2F
#define PID_AbsoluteBarometricPressure 0x33
#define PID_PIDsSupported41to60 0x40
#define PID_ControlModuleVoltage 0x42
#define PID_AbsoluteLoadValue 0x43
#define PID_AmbientAirTemperature 0x46
#define PID_EthanolFuelPercent 0x52
#define PID_FuelRailAbsolutePressure 0x59
#define PID_HybridBatteryPackRemainingLife 0x5B
#define PID_EngineOilTemperature 0x5C
#define PID_FuelInjectionTiming 0x5D
#define PID_EngineFuelRate 0x5E
#define PID_PIDsSupported61to80 0x60
#define PID_DriversDemandEnginePercentTorque 0x61
#define PID_ActualEnginePercentTorque 0x62
#define PID_EngineReferenceTorque 0x63
#define PID_PIDsSupported81toA0 0x80
#define PID_PIDsSupportedA1toC0 0xA0
#define PID_TransmissionActualGear 0xA4
#define PID_Odometer 0xA6

namespace OBD2{
	bool requestIsPending(uint32_t CurrentTime);
	void setRequestPending(bool cmd);
	void requestPID(ACAN2515& myCAN, uint8_t TargetPID);
	bool processFrame(float &val, byte &PID_ID, CANMessage &MyCANFrame);
}

