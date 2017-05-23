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

// Motor
struct Motor {
  Adafruit_DCMotor *adMotor;
  Encoders::Encoder *enc;
  PID *pid;

  bool runPID;
  bool revM;

  Motor(int motNum) {
    adMotor = AFMS.getMotor(motNum);

    pid = new PID(0,0,0,0);
    pid->oMax = 255;
    pid->oMin = -255;

    runPID = false;
    revM = false;
  }

  void setEnc(Encoders::Encoder *encP) {
    enc = encP;
    enc->zero();
  }

  long getPosition() {
    return enc->position;
  }

  void setPower(int power) {
    power = (power > 255) ? 255 : ((power < -255) ? -255 : power);
    adMotor->run((power >= 0 && !revM) ? FORWARD : BACKWARD);
    adMotor->setSpeed(abs(power));
  }

  void reverseMotor() {
    revM = !revM;
  }

  void reverse() {
    reverseMotor();
    enc->reverse();
  }

  void startGoto(int target) {
    pid->sp = target;
    runPID = true;
  }

  void stopGoto() {
    pid->sp = enc->position;
    runPID = false;
  }

  void tick(long dt) {
    if (runPID) {
      double di = pid->calculate(enc->position,dt);
      setPower(di);
    }
  }

  void print() {
    Serial.print("Position: ");
    Serial.print(enc->position);
    Serial.print("    SetPoint: ");
    Serial.println(pid->sp);
  }
};

Motor *mot;
unsigned long t;

void setup() {
  Serial.begin(9600);

  AFMS.begin();
  
  mot = new Motor(1);
  mot->pid->kP = 1;
  mot->setEnc(Encoders::beginEnc6(2, 3));

  mot->startGoto(-1700);

  t = micros();
}

void loop() {
  mot->tick(micros() - t);
  mot->print();

  t = micros();
}



