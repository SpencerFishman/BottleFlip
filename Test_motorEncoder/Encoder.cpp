#include "Encoder.h"

namespace Encoders {
  struct Encoder {
    long position;
    Pio* APIO;
    Pio* BPIO;
    byte APIOBit;
    byte APIOBit;
    byte pinA1, pinA2;
    byte pinB1, pinB2;

    Encoder(byte pinA1, byte pinB1) {
      position = 0;

      APIO = DueUTIL::getPIOFromPin(pinA1);
      BPIO = DueUTIL::getPIOFromPin(pinB1);
      APIOBit = DueUTIL::getPinPIOBit(pinA1);
      BPIOBit = DueUTIL::getPinPIOBit(pinB1);
      
      pinMode(pinA1, INPUT);
      pinMode(pinB1, INPUT);
    }

    Encoder(byte pinA1, byte pinA2, byte pinB1) {
      position = 0;

      APIO = DueUTIL::getPIOFromPin(pinA1);
      BPIO = DueUTIL::getPIOFromPin(pinB1);
      APIOBit = DueUTIL::getPinPIOBit(pinA1);
      BPIOBit = DueUTIL::getPinPIOBit(pinB1);
      
      pinMode(pinA1, INPUT);
      pinMode(pinA2, INPUT);
      pinMode(pinB1, INPUT);
    }

    Encoder(byte pinA1, byte pinA2, byte pinB1, byte pinB2) {
      position = 0;

      APIO = DueUTIL::getPIOFromPin(pinA1);
      BPIO = DueUTIL::getPIOFromPin(pinB1);
      APIOBit = DueUTIL::getPinPIOBit(pinA1);
      BPIOBit = DueUTIL::getPinPIOBit(pinB1);
      
      pinMode(pinA1, INPUT);
      pinMode(pinA2, INPUT);
      pinMode(pinB1, INPUT);
      pinMode(pinB2, INPUT);
    }
  };

  Encoder encs[6];

  Encoder encoder(size_t encoderNum) {
    return encs[encoderNum - 1];
  }

  /**
   * Encoder Setups
   * 
   * Encoder setup resolutions:
   * 1 - 4x Resolution
   * 2 - 4x Resolution
   * 3 - 2x Resolution
   * 4 - 2x Resolution
   * 5 - 1x Resolution
   * 6 - 1x Resolution
   */


  // Encoder 1: 4x Resolution Encoder
  void beginEnc1(byte pinA1, byte pinA2, byte pinB1, byte pinB2) {
    encs[0] = new Encoder(pinA1,pinA2,pinB1,pinB2);

    attachInterrupt(pinA1, enc1ARise, RISING);
    attachInterrupt(pinA2, enc1AFall, FALLING);
    attachInterrupt(pinB1, enc1BRise, RISING);
    attachInterrupt(pinB1, enc1BFall, FALLING);
  }

  void enc1ARise() {
    encs[0]->position += (encs[0]->BPIO->PIO_PDSR & (1 << encs[0]->BPIOBit)) ? +1 : -1;
  }

  void enc1AFall() {
    encs[0]->position += (encs[0]->BPIO->PIO_PDSR & (1 << encs[0]->BPIOBit)) ? -1 : +1;
  }

  void enc1BRise() {
    encs[0]->position += (encs[0]->APIO->PIO_PDSR & (1 << encs[0]->APIOBit)) ? -1 : +1;
  }

  void enc1BFall() {
    encs[0]->position += (encs[0]->APIO->PIO_PDSR & (1 << encs[0]->APIOBit)) ? +1 : -1;
  }

  // Encoder 2: 4x Resolution Encoder
  void beginEnc2(byte pinA1, byte pinA2, byte pinB1, byte pinB2) {
    encs[1] = new Encoder(pinA1,pinA2,pinB1,pinB2);

    attachInterrupt(pinA1, enc2ARise, RISING);
    attachInterrupt(pinA2, enc2AFall, FALLING);
    attachInterrupt(pinB1, enc2BRise, RISING);
    attachInterrupt(pinB1, enc2BFall, FALLING);
  }

  void enc2ARise() {
    encs[1]->position += (encs[1]->BPIO->PIO_PDSR & (1 << encs[1]->BPIOBit)) ? +1 : -1;
  }

  void enc2AFall() {
    encs[1]->position += (encs[1]->BPIO->PIO_PDSR & (1 << encs[1]->BPIOBit)) ? -1 : +1;
  }

  void enc2BRise() {
    encs[1]->position += (encs[1]->APIO->PIO_PDSR & (1 << encs[1]->APIOBit)) ? -1 : +1;
  }

  void enc2BFall() {
    encs[1]->position += (encs[1]->APIO->PIO_PDSR & (1 << encs[1]->APIOBit)) ? +1 : -1;
  }

  // Encoder 3: 2x Resolution Encoder
  void beginEnc3(byte pinA1, byte pinA2, byte pinB1) {
    encs[2] = new Encoder(pinA1,pinA2,pinB1);

    attachInterrupt(pinA1, enc3ARise, RISING);
    attachInterrupt(pinA2, enc3AFall, FALLING);
  }

  void enc3ARise() {
    encs[2]->position += (encs[2]->BPIO->PIO_PDSR & (1 << encs[2]->BPIOBit)) ? +1 : -1;
  }

  void enc3AFall() {
    encs[2]->position += (encs[2]->BPIO->PIO_PDSR & (1 << encs[2]->BPIOBit)) ? -1 : +1;
  }

  // Encoder 4: 2x Resolution Encoder
  void beginEnc4(byte pinA1, byte pinA2, byte pinB1) {
    encs[3] = new Encoder(pinA1,pinA2,pinB1);

    attachInterrupt(pinA1, enc4ARise, RISING);
    attachInterrupt(pinA2, enc4AFall, FALLING);
  }

  void enc4ARise() {
    encs[3]->position += (encs[3]->BPIO->PIO_PDSR & (1 << encs[3]->BPIOBit)) ? +1 : -1;
  }

  void enc4AFall() {
    encs[3]->position += (encs[3]->BPIO->PIO_PDSR & (1 << encs[3]->BPIOBit)) ? -1 : +1;
  }

  // Encoder 5: 1x Resolution Encoder
  void beginEnc5(byte pinA1, byte pinB1) {
    encs[4] = new Encoder(pinA1,pinB1);

    attachInterrupt(pinA1, enc5ARise, RISING);
  }

  void enc5ARise() {
    encs[4]->position += (encs[4]->BPIO->PIO_PDSR & (1 << encs[4]->BPIOBit)) ? +1 : -1;
  }

  // Encoder 6: 1x Resolution Encoder
  void beginEnc6(byte pinA1, byte pinB1) {
    encs[5] = new Encoder(pinA1,pinB1);

    attachInterrupt(pinA1, enc6ARise, RISING);
  }

  void enc6ARise() {
    encs[5]->position += (encs[5]->BPIO->PIO_PDSR & (1 << encs[5]->BPIOBit)) ? +1 : -1;
  }
}