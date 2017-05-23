#ifndef PID_INCLUDEGUARD
#define PID_INCLUDEGUARD

#include <Arduino.h>

struct PID {
  double sp, oMin, oMax;
  double kP;
  double kI, iMin, iMax, integral, kICD, coolDIntegral, coolDDirection;
  double kD, preError;
  bool iCoolD;

  PID(double);
  PID(double,double,double,double);
  
  void init();
  double calculate(double,double);
  void zero();
  void zero(double);
};

template <typename T> int sgn(T val);

#endif

