#include <MIDI.h>
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MidiOut);

#include "PadIO.h"
#include "MidiSettingIO.h"
#include "SurfaceConfiguration.h"
#include "MidiSetting.h"

namespace THCRecords 
{
namespace Device
{

//Compile-time wiring
typedef Pad<0,22> Pad0;
typedef Pad<1,23> Pad1;
typedef Pad<2,24> Pad2;
typedef Pad<3,25> Pad3;
typedef Pad<4,26> Pad4;
typedef Pad<5,27> Pad5;
typedef Pad<6,28> Pad6;
typedef Pad<7,29> Pad7;
typedef Pad<8,30> Pad8;
typedef Pad<9,31> Pad9;
typedef SurfaceConfiguration<14,15,40> TheSurfaceConfiguration;
typedef MidiSetting<42,44,46> TheMidiSetting;

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
        new Logic::Pad<Device::Pad0>();
        break;
      case 1:
        new Logic::Pad<Device::Pad1>();
        break;
      case 2:
        new Logic::Pad<Device::Pad2>();
        break;
      case 3:
        new Logic::Pad<Device::Pad3>();
        break;
      case 4:
        new Logic::Pad<Device::Pad4>();
        break;
      case 5:
        new Logic::Pad<Device::Pad5>();
        break;
      case 6:
        new Logic::Pad<Device::Pad6>();
        break;
      case 7:
        new Logic::Pad<Device::Pad7>();
        break;
      case 8:
        new Logic::Pad<Device::Pad8>();
        break;
      case 9:
        new Logic::Pad<Device::Pad9>();
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


THCRecords::Tranxen200Application<10> gTranxen200;

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

