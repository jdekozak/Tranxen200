#pragma once

namespace THCRecords
{
namespace Device
{

template<int THRESHOLD_PIN, int RELAX_PIN, int MODE_PIN>
struct SurfaceConfigurationIO
{
  void setup()
  {
    pinMode(MODE_PIN, INPUT);
  }

  int readThreshold()
  {
    return analogRead(THRESHOLD_PIN);
  }  
  int readRelax()
  {
    return analogRead(RELAX_PIN);
  }
  int getMode()
  {
    return digitalRead(MODE_PIN);
  }
};

}
}

