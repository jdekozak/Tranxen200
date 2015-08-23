#pragma once

#include <iostream>

namespace THCRecords
{
namespace Logic
{
struct FakePadIO
{
  int piezo = 450;
  void setup()
  {
    std::cout << "FakePadIO::setup" << std::endl;
  }
  int readPiezo()
  {
    std::cout << "FakePadIO::readPiezo::" << piezo << std::endl;
    return piezo;
  }
  void light(bool value)
  {
    std::cout << "FakePadIO::turn::" << (value ? "ON" : "OFF") << std::endl;
  }
};


}
}
