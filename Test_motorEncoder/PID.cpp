#include "PID.h"

PID::PID(double x) {
  sp = x;
  kP = 1;
  kI = 0;
  kD = 0;
  init();
}

PID::PID(double x, double p, double i, double d) {
  sp = x;
  kP = p;
  kI = i;
  kD = d;
  init();
}

void PID::init() {
  integral = 0;
  kICD = 1;
  coolDIntegral = 0;
  iCoolD = false;
  iMin = -1;
  iMax = -1;
  oMin = -1;
  oMax = -1;
}

double PID::calculate(double pv, double dt) {
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
  /*Serial.print(error);
  Serial.print(" - ");
  Serial.print(preError);
  Serial.print(" / ");
  Serial.print(dt);
  Serial.print(" = ");
  Serial.println(oD);*/
  preError = error;

  double o = oP + ((kI != 0) ? oI : 0) + oD;
  if (oMin != -1 && oMax != -1)
    return (o < oMin) ? oMin : (o > oMax) ? oMax : o;
  return o;
}

template <typename T> int sgn(T val) {
  return (T(0) < val) - (val < T(0));
}

