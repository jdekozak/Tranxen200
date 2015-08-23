#pragma once

#include <iostream>

namespace THCRecords
{
namespace Device
{

struct FakeSurfaceConfigurationIO
{
  int threshold = 200;
  int relax = 300;
  int mode = 0;
  void setup()
  {
      std::cout << "FakeSurfaceConfigurationIO::setup" << std::endl;
  }
  int readThreshold()
  {
    std::cout << "FakeSurfaceConfigurationIO::readThreshold::" << threshold << std::endl;
    return threshold;
  }  
  int readRelax()
  {
    std::cout << "FakeSurfaceConfigurationIO::readRelax::" << relax << std::endl;
    return relax;
  }
  int getMode()
  {
    std::cout << "FakeSurfaceConfigurationIO::getMode::" << mode << std::endl;
    return mode;
  }
};

}
}
