#ifndef __SURFACE_CONFIGURATION_H__
#define __SURFACE_CONFIGURATION_H__

namespace THCRecords
{
namespace Interface
{

template<int THRESHOLD_PIN, int RELAX_PIN, int MODE_PIN>
struct SurfaceConfiguration
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

#endif
