#include "DueUtilities.h"

/*
 *	Bit Mapping: https://www.arduino.cc/en/Hacking/PinMappingSAM3X
 */

namespace DueUTIL {
	Pio* getPIOFromPin(byte pinNumber) {
		byte pios[79] = {
			//0      1      2      3      4      5      6      7      8      9
			B0001, B0001, B0010, B0100, B0101, B0100, B0100, B0100, B0100, B0100, // 0
			B0101, B1000, B1000, B0010, B1000, B1000, B0001, B0001, B0001, B0001, // 1
			B0010, B0010, B0010, B0001, B0001, B1000, B1000, B1000, B1000, B1000, // 2
			B1000, B0001, B1000, B0100, B0100, B0100, B0100, B0100, B0100, B0100, // 3
			B0100, B0100, B0001, B0001, B0100, B0100, B0100, B0100, B0100, B0100, // 4
			B0100, B0100, B0010, B0010, B0001, B0001, B0001, B0001, B0001, B0001, // 5
			B0001, B0001, B0010, B0010, B0010, B0010, B0010, B0010, B0001, B0001, // 6
			B0001, B0001, B0100, B0001, B0001, B0001, B0001, B0001, B0100         // 7
		};

		byte pio = pios[pinNumber];

		if (pio & B0001)
			return PIOA;
		else if (pio & B0010)
			return PIOB;
		else if (pio & B0100)
			return PIOC;
		else if (pio & B1000)
			return PIOD;
		return PIOA;
	}

	byte getPinPIOBit(byte pinNumber) {
		byte pioBits[79] {
			//0   1   2   3   4   5   6   7   8   9
			8, 9, 25, 28, 29, 25, 24, 23, 22, 21, // 0
			28, 7, 8, 27, 4, 5, 13, 12, 11, 10,   // 1
			12, 13, 26, 14, 15, 0, 1, 2, 3, 6,    // 2
			9, 7, 10, 1, 2, 3, 4, 5, 6, 7,        // 3
			8, 9, 19, 20, 19, 18, 17, 16, 15, 14, // 4
			13, 12, 21, 14, 16, 24, 23, 22, 6, 4, // 5
			3, 2, 17, 18, 19, 20, 15, 16, 1, 0,   // 6
			17, 19, 30, 21, 25, 26, 27, 28, 23    // 7
		};

		return pioBits[pinNumber];
	}
}

