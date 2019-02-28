# RejsDash
Drivers and examples of RejsDash
## Features
* 15 individually addressable RGB-leds with 8-bit resolution per color
* Big 7-segment display for gear indication
* 2x4 14-segment configurable displays for data values
* CAN-interface for data acquisition
* ItsyBitsy32u4 Arduino-compatible microcontroller

## Supported data sources
Primarly CAN-bus source data. This can either be CAN-bus interface of a third party ECU (MaxxECU, DTA, Motec and others) or a car compliant with CAN-based OBD2 (Check if your car's OBD-plug has pin 6 & 14 populated)

Example of alternative sources:
1) Digital or analog inputs at the expansion header connected directly to sensors.
2) RS232 (Motec M4, DTA P8Pro etc) through a voltage shifter (https://www.sparkfun.com/products/449) connected to UART on expansion header.
3) Serial port through USB connector (could be used in racing sim rig build sourcing data from iRacing and others)

## Example video
https://youtu.be/iicIpTxv9EI
