#ifndef SERIALREAD_INCLUDEGUARD
#define SERIALREAD_INCLUDEGUARD

#include <Arduino.h>

namespace SerialRead {
  int Integer();
  int Integer(unsigned int);

  float Float();
  float Float(unsigned int);
}

#endif