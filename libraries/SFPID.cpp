SFPID::setGains(double p, double i, double d) {
	kP = p;
	kI = i;
	kD = d;
}

SFPID::setRange(double min, double max) {
	oMin = min;
	oMax = max;
}

SFPID::setIDomain(double min, double max) {
	iMin = min;
	iMax = max;
}

SFPID::setTarget(double target) {
	setpoint = target;
}

SFPID::reset(void) {
	integral = 0;
	preError = 0;
}

SFPID::calculate(double pv, double dt) {
	if (dt == 0.0)
		throw std::exception("Impossible to calculate a PID feedback loop with time interval of zero");

	double error = setpoint - pv;

	double oP = kP * error;

	integral += error * dt;
	integral = (integral < iMin) ? iMin : (integral > iMax) ? iMax : integral;
	double oI = kI * integral;

	double oD = kD * (error - preError) / dt;
	preError = error;

	double o = oP + oI + oD;
	return (o < oMin) ? oMin : (o > oMax) ? oMax : o;
}