#ifndef PID_INCLUDEGUARD
#define #PID_INCLUDEGUARD

struct PID {
  double sp, oMin, oMax;
  double kP;
  double kI, iMin, iMax, integral, kICD, coolDIntegral, coolDDirection;
  double kD, preError;
  bool iCoolD;

  PID();
  
  double calculate(double,double);
};

template <typename T> int sgn(T val);

#endif