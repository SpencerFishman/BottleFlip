InterruptEncoder::InterruptEncoder(byte SensorPortA, byte SensorPortB) {
	SensorStateA = false;
	SensorStateB = false;
	position = 0;
	attachInterrupt(SensorPortA, InterruptSensorA, CHANGE);
	attachInterrupt(SensorPortB, InterruptSensorB, CHANGE);
}

InterruptEncoder::InterruptSensorA(void) {
	position += (SensorStateA == SensorStateB) ? +1 : -1;
	SensorSateA = !SensorStateA;
}

InterruptEncoder::InterruptSensorB(void) {
	position += (SensorStateA == SensorStateB) ? -1 : +1;
	SensorSateB = !SensorStateB;
}

InterruptEncoder::Zero(void) {
	SensorStateA = false;
	SensorStateB = false;
	position = 0;
}

InterruptEncoder::getPostition(void) {
	return position;
}