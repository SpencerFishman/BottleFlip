#ifndef INC_InterruptEncoder
#define INC_InterruptEncoder // Include Guard

#include <Arduino.h>

class InterruptEncoder {
		bool SensorStateA;
		bool SensorStateB;
		int position;
	public:
		InterruptEncoder(byte, byte);
		void InterruptSensorA (void);
		void InterruptSensorB (void);
		void Zero (void);
		int getPosition(void);
};

#endif // !INC_InterruptEncoder