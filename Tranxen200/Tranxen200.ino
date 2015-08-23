#include <MIDI.h>
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MidiOut);

#include "PadIO.h"
#include "MidiSettingIO.h"
#include "SurfaceConfigurationIO.h"
#include "MidiSetting.h"

namespace THCRecords 
{
namespace Device
{

//Compile-time wiring
typedef PadIO<0,22> Pad0;
Pad0 pad0;
typedef PadIO<1,23> Pad1;
Pad1 pad1;
typedef PadIO<2,24> Pad2;
Pad2 pad2;
typedef PadIO<3,25> Pad3;
Pad3 pad3;
typedef PadIO<4,26> Pad4;
Pad4 pad4;
typedef PadIO<5,27> Pad5;
Pad5 pad5;
typedef PadIO<6,28> Pad6;
Pad6 pad6;
typedef PadIO<7,29> Pad7;
Pad7 pad7;
typedef PadIO<8,30> Pad8;
Pad8 pad8;
typedef PadIO<9,31> Pad9;
Pad9 pad9;
typedef SurfaceConfigurationIO<14,15,40> TheSurfaceConfiguration;
TheSurfaceConfiguration surfaceDevice;
typedef MidiSettingIO<42,44,46> TheMidiSetting;
TheMidiSetting midiDevice;

}
}

#include "Pad.h"

namespace THCRecords
{
namespace Logic
{

struct PadFactory
{
  Logic::PadInterface* create(int pad) const
  {
    Logic::PadInterface* thePad = 0;
    switch(pad) {
      case 0:
        new Logic::Pad<Device::Pad0>(Device::pad0);
        break;
      case 1:
        new Logic::Pad<Device::Pad1>(Device::pad1);
        break;
      case 2:
        new Logic::Pad<Device::Pad2>(Device::pad2);
        break;
      case 3:
        new Logic::Pad<Device::Pad3>(Device::pad3);
        break;
      case 4:
        new Logic::Pad<Device::Pad4>(Device::pad4);
        break;
      case 5:
        new Logic::Pad<Device::Pad5>(Device::pad5);
        break;
      case 6:
        new Logic::Pad<Device::Pad6>(Device::pad6);
        break;
      case 7:
        new Logic::Pad<Device::Pad7>(Device::pad7);
        break;
      case 8:
        new Logic::Pad<Device::Pad8>(Device::pad8);
        break;
      case 9:
        new Logic::Pad<Device::Pad9>(Device::pad9);
        break;  
      default:
        break;
    }
    return thePad;
  }
};

}
}

#include "Tranxen200Application.h"

THCRecords::Logic::PadFactory padFactory;
THCRecords::Tranxen200Application<10> gTranxen200(padFactory, THCRecords::Device::midiDevice, THCRecords::Device::surfaceDevice);

void setup()
{
  Serial.begin(9600);
  MidiOut.begin(1);
  gTranxen200.setup();
}

void loop()
{
  gTranxen200.loop();
}


