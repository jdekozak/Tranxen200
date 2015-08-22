#pragma once

#include <iostream>

class FakeSerial
{
public:
  void println(const char* message)
  {
      std::cout << message << std::endl;
  }
  void println(int value)
  {
      std::cout << value << std::endl;
  }
};

FakeSerial Serial;