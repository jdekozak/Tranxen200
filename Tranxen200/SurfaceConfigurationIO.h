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

  int readThreshold() const
  {
    return analogRead(THRESHOLD_PIN);
  }  
  int readRelax() const
  {
    return analogRead(RELAX_PIN);
  }
  int getMode() const
  {
    return digitalRead(MODE_PIN);
  }
};

}
}

