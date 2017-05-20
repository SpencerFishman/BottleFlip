// C++ Includes
#include <vector>
#include <stdlib.h> 

// Custom C++ Includes
#include "PID.h"
#include "Encoder.h"

// Arduino Includes
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Motor functions
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);

// PID
//std::vector<PID*> pids;
PID *pid;


long dt;

void setup() {
  Serial.begin(9600);

  AFMS.begin();
  
  Encoders::beginEnc1(2,4,3,5);
  pid = new PID(8000,0.25,0,7000);
  pid->oMax = 255;
  pid->oMin = -255;
  dt=1;
}

void loop() {
  long pos = Encoders::encoder(1)->position;
  int cO = (int) pid->calculate(pos, micros() - dt);
  dt = micros();
  Serial.print("Position: ");
  Serial.print(pos);
  Serial.print("    ControlValue: ");
  Serial.print(cO);
  Serial.print("    SetPoint: ");
  Serial.println(pid->sp);
  if (cO > 0)
    motor1->run(BACKWARD);
  else
    motor1->run(FORWARD);
  motor1->setSpeed(abs(cO));
}



