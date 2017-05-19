#ifndef DUEUTILITIES_INCLUDEGUARD
#define #DUEUTILITIES_INCLUDEGUARD

#include <Arduino.h>

namespace DueUTIL {
	Pio* getPIOFromPin(byte);
	byte getPinPIOBit(byte);
}

#endif