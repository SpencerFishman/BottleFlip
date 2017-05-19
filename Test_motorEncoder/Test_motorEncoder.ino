// C++ Includes
#include <vector>

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
std::vector<PID> pids;

void setup() {
  Serial.begin(9600);

  AFMS.begin();
  motor1->setSpeed(150);
  motor1->run(FORWARD);
  
  Encoders::beginEnc1(2,4,3,5);
}

void loop() {
  Serial.println(Encoders::encoder(1)->position);
  delay(10);
}