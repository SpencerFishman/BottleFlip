// C++ Includes
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

// Motor
PID *pid;


long dt;
long pods[4];
bool up;

void setup() {
  Serial.begin(9600);

  AFMS.begin();
  
  Encoders::beginEnc1(2,4,3,5);
  pid = new PID(-2500,0.35,0,0);
  pid->oMax = 255;
  pid->oMin = -255;
  dt=1;

  pods[0] = 0;
  pods[1] = 0;
  pods[2] = 0;
  pods[3] = 0;

  up = true;
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
  if (pods[0] == Encoders::encoder(1)->position && (pods[0] <= -2000 || up == false) ) {
    pods[0] = 0;
    pods[1] = 0;
    pods[2] = 0;
    pods[3] = 0;

    if (up)
      pid->sp = 0;
    else
      pid->sp = -2500;
    up = !up;
  }

  pods[0] = pods[1];
  pods[1] = pods[2];
  pods[2] = pods[3];
  pods[3] = Encoders::encoder(1)->position;
}



