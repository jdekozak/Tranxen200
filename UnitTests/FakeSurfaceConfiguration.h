#pragma once

namespace THCRecords
{
namespace Device
{

struct FakeSurfaceConfiguration
{
  void setup()
  {
      std::cout << "setup" << std::endl;
  }
  int readThreshold()
  {
    return 200;
  }  
  int readRelax()
  {
    return 300;
  }
  int getMode()
  {
    return 0;
  }
};

}
}