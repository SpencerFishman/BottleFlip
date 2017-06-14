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

  long lastEncPos = 0;

  const byte PIDTickTimeout = 5;
  byte tickTimeout = 0;

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
    //Serial.print("Power: ");
    //Serial.println(power);
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
    tickTimeout = 0;
    runPID = true;
  }

  void stopGoto() {
    pid->sp = enc->position;
    runPID = false;
  }

  void tick(long dt) {
    if (runPID) {
      double di = pid->calculate(enc->position,dt);
      
      if (lastEncPos != enc->position)
        tickTimeout = 0;
      else
        tickTimeout += 1;
        
      if (tickTimeout <= PIDTickTimeout)
        setPower(di);
      else
        stopGoto();
        
      lastEncPos = enc->position;
    } else {
      setPower(0);
    }
  }

  void zero() {
    enc->zero();
    pid->zero();
  }

  void print() {
    Serial.print("Position: ");
    Serial.print(enc->position);
    Serial.print("    SetPoint: ");
    Serial.println(pid->sp);
  }
};

 

Motor *motLift1;
Motor *motLift2;
Motor *motRot1;
Motor *motRot2;
Motor *mot;
unsigned long t;

bool lift;

void setup() {
  Serial.begin(9600);

  AFMS.begin();

  

  motRot1 = new Motor(4);
  motRot1->pid->kP = 1;
  motRot1->setEnc(Encoders::beginEnc5(25, 24));

  motLift1 = new Motor(3);
  motLift1->pid->kP = 2;
  motLift1->setEnc(Encoders::beginEnc6(23, 22));

  motRot2 = new Motor(2);
  motRot2->pid->kP = 1;
  motRot2->setEnc(Encoders::beginEnc7(2, 3));

  motLift2 = new Motor(1);
  motLift2->pid->kP = 2;
  //motLift2->setEnc(Encoders::beginEnc8(22, 23));

  mot = motRot1;

  Serial.println("Set P Gain");
  while (false) {
    if (Serial.available() > 0) {
      float kP = Serial.parseFloat();
      mot->pid->kP = kP;
      break;
    }
  }

  lift = true;

  t = micros();
}

void loop() {
  if (lift) {
    motLift1->tick(micros() - t);
    motLift1->print();
  
    t = micros();
  
    if (Serial.available() > 0) {
      float newTarget = Serial.parseFloat();
      if (newTarget == 0) {
        motLift1->stopGoto();
        motLift1->zero();
        delay(200);
        motLift1->stopGoto();
        motLift1->zero();
        lift = !lift;
      } else if (newTarget == 0.001) {
        lift = !lift;
      } else {
        motLift1->startGoto(newTarget / 22.5 * 1751);
      }
    }
  } else {
    motRot1->tick(micros() - t);
    motRot1->print();
  
    t = micros();
  
    if (Serial.available() > 0) {
      float newTarget = Serial.parseFloat();
      if (newTarget == 0) {
        motRot1->stopGoto();
        motRot1->zero();
        delay(200);
        motRot1->stopGoto();
        motRot1->zero();
        lift = !lift;
      } else {
        motRot1->startGoto(newTarget * 1200);
      }
    }
  }
}



