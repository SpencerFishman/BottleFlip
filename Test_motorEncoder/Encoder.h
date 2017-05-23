#ifndef ENCODER_INCLUDEGUARD
#define ENCODER_INCLUDEGUARD

// Custom C++ Includes
#include "DueUtilities.h"

// Arduino Inc
#include <Arduino.h>

namespace Encoders {
  struct Encoder {
    volatile long position;
    volatile long directionMod;
    Pio* APIO;
    Pio* BPIO;
    byte APIOBit;
    byte BPIOBit;

    Encoder(){};
    Encoder(byte,byte);
    Encoder(byte,byte,byte);
    Encoder(byte,byte,byte,byte);

    void zero();
    void reverse();
  };


  Encoder* encoder(size_t);

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
  Encoder * beginEnc1(byte, byte, byte, byte);
  void enc1ARise();
  void enc1AFall();
  void enc1BRise();
  void enc1BFall();

  // Encoder 2: 4x Resolution Encoder;
  Encoder * beginEnc2(byte, byte, byte, byte);
  void enc2ARise();
  void enc2AFall();
  void enc2BRise();
  void enc2BFall();

  // Encoder 3: 2x Resolution Encoder
  Encoder * beginEnc3(byte, byte, byte);
  void enc3ARise();
  void enc3AFall();

  // Encoder 4: 2x Resolution Encoder
  Encoder * beginEnc4(byte, byte, byte);
  void enc4ARise();
  void enc4AFall();

  // Encoder 5: 1x Resolution Encoder
  Encoder * beginEnc5(byte, byte);
  void enc5ARise();

  // Encoder 6: 1x Resolution Encoder
  Encoder * beginEnc6(byte, byte);
  void enc6ARise();
}

#endif

