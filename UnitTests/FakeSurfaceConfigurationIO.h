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
  int readThreshold() const
  {
    std::cout << "FakeSurfaceConfigurationIO::readThreshold::" << threshold << std::endl;
    return threshold;
  }  
  int readRelax() const
  {
    std::cout << "FakeSurfaceConfigurationIO::readRelax::" << relax << std::endl;
    return relax;
  }
  int getMode() const
  {
    std::cout << "FakeSurfaceConfigurationIO::getMode::" << (mode == 1 ? "HIGH" : "LOW") << std::endl;
    return mode;
  }
};

typedef FakeSurfaceConfigurationIO TheSurfaceConfiguration;
TheSurfaceConfiguration surfaceDevice;

}
}
