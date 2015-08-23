#pragma once

#include <iostream>

namespace THCRecords
{
namespace Device
{

struct FakeMidiSettingIO
{
  int up = 0;
  int down = 0;
  int next = 0;
  void setup()
  {
    std::cout << "FakeMidiSetting::setup" << std::endl;
  }
  int getUp()
  {
    std::cout << "FakeMidiSetting::getUp::" << up << std::endl;
    return up;
  }
  int getDown()
  {
    std::cout << "FakeMidiSetting::getDown::" << down << std::endl;
    return down;
  }
  int getNext()
  {
    std::cout << "FakeMidiSetting::getNext::" << next << std::endl;
    return next;
  }
};

}
}
