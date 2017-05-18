#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <typeinfo>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *motor1 = AFMS.getMotor(1);

volatile long enc1Position = 0;
Pio* enc1APIO;
Pio* enc1BPIO;
byte enc1APIOBit;
byte enc1BPIOBit;

void setup() {
  Serial.begin(9600);
  Serial.println("Begin Motor Encoder Test");

  AFMS.begin();

  motor1->setSpeed(150);
  motor1->run(FORWARD);

  beginEnc1(2,4,3,5);

  //pinMode(encoderAPort, INPUT);
  //pinMode(encoderBPort, INPUT);

  //attachInterrupt(digitalPinToInterrupt(encoderAPort), enc1IntA, CHANGE );
  //attachInterrupt(digitalPinToInterrupt(encoderBPort), enc1IntB, CHANGE );
  //attachInterrupt(digitalPinToInterrupt(encoderAPort), lowRes1Int, RISING );
  //attachInterrupt(digitalPinToInterrupt(4), lowRes1Int2, FALLING );
  //attachInterrupt(digitalPinToInterrupt(encoderBPort), lowRes2Int, RISING );
  //attachInterrupt(digitalPinToInterrupt(5), lowRes2Int2, FALLING );
}

void loop() {
  Serial.println(enc1Position);
  delay(10);
}

/**
 * Encoder Setup
 */



void beginEnc1(byte pinA1, byte pinA2, byte pinB1, byte pinB2) {
  enc1Position = 0;
  
  enc1APIO = getPinPIO(pinA1);
  enc1BPIO = getPinPIO(pinB1);
  enc1APIOBit = getPinPIOBit(pinA1);
  enc1BPIOBit = getPinPIOBit(pinB1);

  Serial.println("Enc1 Init");
  Serial.print("A1 bit: ");
  Serial.println(enc1APIOBit);
  Serial.print("B1 bit: ");
  Serial.println(enc1BPIOBit);

  pinMode(pinA1, INPUT);
  pinMode(pinA2, INPUT);
  pinMode(pinB1, INPUT);
  pinMode(pinB2, INPUT);

  attachInterrupt(pinA1, enc1ARise, RISING);
  attachInterrupt(pinA2, enc1AFall, FALLING);
  attachInterrupt(pinB1, enc1BRise, RISING);
  attachInterrupt(pinB1, enc1BFall, FALLING);
}

void enc1ARise() {
  enc1Position += (enc1BPIO->PIO_PDSR & (1 << enc1BPIOBit)) ? +1 : -1;
}

void enc1AFall() {
  enc1Position += (enc1BPIO->PIO_PDSR & (1 << enc1BPIOBit)) ? -1 : +1;
}

void enc1BRise() {
  enc1Position += (enc1APIO->PIO_PDSR & (1 << enc1APIOBit)) ? -1 : +1;
}

void enc1BFall() {
  enc1Position += (enc1APIO->PIO_PDSR & (1 << enc1APIOBit)) ? +1 : -1;
}
 

/**
 *  DUE UTILITIES
 *  
 *  Bit Mapping: https://www.arduino.cc/en/Hacking/PinMappingSAM3X
 */
Pio* getPinPIO(byte pinNumber) {
  byte pios[79] = {
      //0      1      2      3      4      5      6      7      8      9
      B0001, B0001, B0010, B0100, B0101, B0100, B0100, B0100, B0100, B0100, // 0
      B0101, B1000, B1000, B0010, B1000, B1000, B0001, B0001, B0001, B0001, // 1
      B0010, B0010, B0010, B0001, B0001, B1000, B1000, B1000, B1000, B1000, // 2
      B1000, B0001, B1000, B0100, B0100, B0100, B0100, B0100, B0100, B0100, // 3
      B0100, B0100, B0001, B0001, B0100, B0100, B0100, B0100, B0100, B0100, // 4
      B0100, B0100, B0010, B0010, B0001, B0001, B0001, B0001, B0001, B0001, // 5
      B0001, B0001, B0010, B0010, B0010, B0010, B0010, B0010, B0001, B0001, // 6
      B0001, B0001, B0100, B0001, B0001, B0001, B0001, B0001, B0100         // 7
  };
  
  byte pio = pios[pinNumber];

  if (pio & B0001)
    return PIOA;
  else if (pio & B0010)
    return PIOB;
  else if (pio & B0100)
    return PIOC;
  else if (pio & B1000)
    return PIOD;
  return PIOA;
}

byte getPinPIOBit(byte pinNumber) {
  byte pioBits[79] {
      //0   1   2   3   4   5   6   7   8   9
      8, 9, 25, 28, 29, 25, 24, 23, 22, 21, // 0
      28, 7, 8, 27, 4, 5, 13, 12, 11, 10,   // 1
      12, 13, 26, 14, 15, 0, 1, 2, 3, 6,    // 2
      9, 7, 10, 1, 2, 3, 4, 5, 6, 7,        // 3
      8, 9, 19, 20, 19, 18, 17, 16, 15, 14, // 4
      13, 12, 21, 14, 16, 24, 23, 22, 6, 4, // 5
      3, 2, 17, 18, 19, 20, 15, 16, 1, 0,   // 6
      17, 19, 30, 21, 25, 26, 27, 28, 23    // 7
  };

  return pioBits[pinNumber];
}
