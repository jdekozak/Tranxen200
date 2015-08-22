#pragma once

namespace THCRecords
{
namespace Logic
{
  struct FakePadIO
  {
      void setup()
      {
	  std::cout << "setup" << std::endl;
      }
      int readPiezo()
      {
	  return 450;
      }
      void light(bool value)
      {
	  std::cout << "turn " << (value ? "ON" : "OFF") << std::endl;
      }
  };
}
}
