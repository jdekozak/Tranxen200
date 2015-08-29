#pragma once

#include <iostream>

#define HIGH 1
#define LOW 0

int millis() {
  static unsigned long long counter = 0;
  std::cout << "millis::" << counter << std::endl;
  return ++counter;
}
