#include <iostream>

#include "FakeArduino.h"
#include "FakeSerial.h"
#include "FakeMidi.h"
#include "FakePadIO.h"
#include "FakeSurfaceConfiguration.h"
namespace THCRecords
{
namespace Device
{
    typedef FakeSurfaceConfiguration TheSurfaceConfiguration;
}
}
#include "FakeMidiSetting.h"
namespace THCRecords
{
namespace Device
{
    typedef FakeMidiSetting TheMidiSetting;
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
    return 0;
}
