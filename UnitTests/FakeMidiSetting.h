#pragma once

#include <iostream>

namespace THCRecords
{
namespace Device
{

struct FakeMidiSetting
{
  void setup()
  {
    std::cout << "setup" << std::endl;
  }
  int getUp()
  {
    return 0;
  }
  int getDown()
  {
    return 0;
  }
  int getNext()
  {
    return 0;
  }
};

}
}