#pragma once

#include <iostream>

namespace THCRecords
{
namespace Device
{

struct FakePadIO
{
  explicit FakePadIO(int ID) : id(ID) {}

  int id;
  int piezo = 450;
  bool led = false;
  void setup()
  {
    std::cout << "FakePadIO::" << id << "::setup" << std::endl;
  }
  int readPiezo() const
  {
    std::cout << "FakePadIO::" << id << "::readPiezo::" << piezo << std::endl;
    return piezo;
  }
  void light(bool value)
  {
    led = value;
    std::cout << "FakePadIO::" << id << "::turn::" << (led ? "ON" : "OFF") << std::endl;
  }
};

FakePadIO padDevice0(0);
FakePadIO padDevice1(1);

}
}
