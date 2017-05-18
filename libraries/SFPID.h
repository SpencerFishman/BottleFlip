#ifndef INC_SFPID
#define INC_SFPID // Include Guard

class SFPID {
		double kP;
		double kI;
		double kD;
		double oMin;
		double oMax;
		double iMin;
		double iMax;
		double setpoint;
		double preError;
	public:
		SFPID(void);
		void setGains(double, double, double);
		void setRange(double, double);
		void setIDomain(double, double);
		void setTarget(double);
		void reset(void);
		double calculate(double, double);
};

#endif // !INC_SFPID