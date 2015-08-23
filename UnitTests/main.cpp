#include <iostream>

#include "FakeArduino.h"
#include "FakeSerial.h"
#include "FakeMidi.h"

#include "FakePadIO.h"
#include "FakeSurfaceConfigurationIO.h"
namespace THCRecords
{
namespace Device
{
  typedef FakeSurfaceConfigurationIO TheSurfaceConfiguration;
}
}
#include "FakeMidiSettingIO.h"
namespace THCRecords
{
namespace Device
{
  typedef FakeMidiSettingIO TheMidiSetting;
}
}
#include <Tranxen200/MidiSetting.h>

#include <Tranxen200/Pad.h>
namespace THCRecords
{
namespace Logic
{

struct PadFactory
{
  PadInterface* create(int pad) const
  {
    return new Pad<FakePadIO>();
  }
};

}
}

#include <Tranxen200/Tranxen200Application.h>

int main(int argc, char **argv) {
  THCRecords::Tranxen200Application<1> beatbox;
  beatbox.setup();
  beatbox.loop();
  beatbox.loop();
  return 0;
}
