#include "PID.h"

struct PID {
  double sp, oMin, oMax;
  double kP;
  double kI, iMin, iMax, integral, kICD, coolDIntegral, coolDDirection;
  double kD, preError;
  bool iCoolD;

  PID() {
    iMin = -1;
    iMax = -1;
    oMin = -1;
    oMax = -1;
  }  
  
  double calculate(double pv, double dt) {
    double error = sp - pv;

    double oP = kP * error;
  
    integral += error * dt;
    if (iMin != -1 && iMax != -1)
      integral = (integral < iMin) ? iMin : (integral > iMax) ? iMax : integral;
    double oI = kP / kI * integral;

    if (!iCoolD && !((preError >= 0) ^ (error < 0))) {
      iCoolD = true;
      coolDIntegral = 0;
      coolDDirection = sgn(integral) * -1;
    }
    
    if (iCoolD) {
      coolDIntegral += coolDDirection * kICD * dt;
      oI += coolDIntegral;
      if ((oI >= 0) ^ (coolDDirection < 0)) {
        coolDIntegral = 0;
        integral = 0;
        oI = 0;
        iCoolD = false;
      }
    }
  
    double oD = kP * kD * (error - preError) / dt;
    preError = error;
  
    double o = oP + oI + oD;
    if (oMin != -1 && oMax != -1)
      return (o < oMin) ? oMin : (o > oMax) ? oMax : o;
    return o;
  }
};

template <typename T> int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}