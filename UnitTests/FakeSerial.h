#pragma once

#include <iostream>

struct FakeSerial
{
  void println(const char* message)
  {
    std::cout << "FakeSerial::" << message << std::endl;
  }
  void println(int value)
  {
    std::cout << "FakeSerial::" << value << std::endl;
  }
};

FakeSerial Serial;
