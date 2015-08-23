#pragma once

#include <iostream>

namespace THCRecords
{
namespace Device
{

struct FakePadIO
{
  int piezo = 450;
  bool led = false;
  void setup()
  {
    std::cout << "FakePadIO::setup" << std::endl;
  }
  int readPiezo() const
  {
    std::cout << "FakePadIO::readPiezo::" << piezo << std::endl;
    return piezo;
  }
  void light(bool value)
  {
    led = value;
    std::cout << "FakePadIO::turn::" << (led ? "ON" : "OFF") << std::endl;
  }
};

FakePadIO padDevice;
}
}
