#include <iostream>
#include <cassert>

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
  TheSurfaceConfiguration surfaceDevice;
}
}
#include "FakeMidiSettingIO.h"
namespace THCRecords
{
namespace Device
{
  typedef FakeMidiSettingIO TheMidiSetting;
  TheMidiSetting midiDevice;
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
    return new Pad<Device::FakePadIO>(Device::padDevice);
  }
};

}
}

#include <Tranxen200/Tranxen200Application.h>

int main(int argc, char **argv)
{
  THCRecords::Logic::PadFactory padFactory;
  THCRecords::Tranxen200Application<1> beatbox(padFactory,
					       THCRecords::Device::midiDevice,
					       THCRecords::Device::surfaceDevice);
  beatbox.setup();

  THCRecords::Device::surfaceDevice.mode = THCRecords::Tranxen200Application<1>::CONFIG;

  THCRecords::Device::surfaceDevice.relax = 1;
  THCRecords::Device::surfaceDevice.threshold = 650;
  beatbox.loop();

  THCRecords::Device::surfaceDevice.mode = THCRecords::Tranxen200Application<1>::PLAY;

  THCRecords::Device::padDevice.piezo = 700;
  beatbox.loop();
  THCRecords::Device::padDevice.piezo = 750;
  beatbox.loop();
  THCRecords::Device::padDevice.piezo = 725;
  beatbox.loop();
  assert(THCRecords::Device::padDevice.led == true);
  assert(MidiOut.channel == 1);
  assert(MidiOut.note == 36);
  assert(MidiOut.volume == 750*128/1024);

  THCRecords::Device::padDevice.piezo = 600;
  beatbox.loop();
  assert(THCRecords::Device::padDevice.led == false);

  THCRecords::Device::padDevice.piezo = 500;
  beatbox.loop();


  return 0;
}
