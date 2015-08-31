#include <iostream>
#include <cassert>

#include "FakeArduino.h"
#include "FakeSerial.h"
#include "FakeMidi.h"

#include "FakePadIO.h"
#include "FakeSurfaceConfigurationIO.h"
#include "FakeMidiSettingIO.h"

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
    switch(pad) {
      case 0:
	return new Pad<Device::FakePadIO>(Device::padDevice0);
	break;
      case 1:
	return new Pad<Device::FakePadIO>(Device::padDevice1);
	break;
      default:
	return 0;
	break;
    }
  }
};

}
}

#include <Tranxen200/Tranxen200Application.h>

void checkLed(int pad, bool state)
{
  switch(pad) {
    case 0:
      assert(THCRecords::Device::padDevice0.led == state);
      break;
    case 1:
      assert(THCRecords::Device::padDevice1.led == state);
      break;
    default:
      break;
  }
}
void setPiezo(int pad, int value)
{
  switch(pad) {
    case 0:
      THCRecords::Device::padDevice0.piezo = value;
      break;
    case 1:
      THCRecords::Device::padDevice1.piezo = value;
      break;
    default:
      break;
  }
}

void checkMidiNote(int channel, int note, int volume)
{
  assert(MidiOut.channel == channel);
  assert(MidiOut.note == note);
  assert(MidiOut.volume == volume);
}

void onePadHit()
{
  std::cout << "#### onePadHit ####" << std::endl;
  THCRecords::Logic::PadFactory padFactory;
  THCRecords::Tranxen200Application<1> beatbox(padFactory,
					       THCRecords::Device::midiDevice,
					       THCRecords::Device::surfaceDevice);
  beatbox.setup();

  THCRecords::Device::surfaceDevice.mode = THCRecords::Tranxen200Application<1>::CONFIG;

  THCRecords::Device::surfaceDevice.relax = 2;
  THCRecords::Device::surfaceDevice.threshold = 650;
  setPiezo(0, 700);
  beatbox.loop();
  checkLed(0, true);
  setPiezo(0, 750);
  beatbox.loop();
  checkLed(0, true);
  setPiezo(0, 450);
  beatbox.loop();
  checkMidiNote(1,36,750*128/1024);
  checkLed(0, true);
  setPiezo(0,450);
  beatbox.loop();
  checkLed(0, false);

  THCRecords::Device::surfaceDevice.mode = THCRecords::Tranxen200Application<1>::PLAY;

  setPiezo(0, 600);
  beatbox.loop();
  checkLed(0, false);
  setPiezo(0, 640);
  beatbox.loop();
  checkLed(0, false);

  setPiezo(0, 700);
  beatbox.loop();
  checkLed(0, true);
  setPiezo(0, 710);
  beatbox.loop();
  checkLed(0, true);
  setPiezo(0, 750);
  beatbox.loop();
  checkLed(0, true);
  setPiezo(0, 725);
  beatbox.loop();
  checkLed(0, true);
  checkMidiNote(1,36,750*128/1024);

  setPiezo(0, 600);
  beatbox.loop();
  checkLed(0, true);

  setPiezo(0, 450);
  beatbox.loop();
  checkLed(0, false);
}

void twoPadsConfiguration()
{
  std::cout << "#### twoPadsConfiguration ####" << std::endl;
  THCRecords::Logic::PadFactory padFactory;
  THCRecords::Tranxen200Application<2> beatbox(padFactory,
					       THCRecords::Device::midiDevice,
					       THCRecords::Device::surfaceDevice);
  beatbox.setup();

  THCRecords::Device::surfaceDevice.mode = THCRecords::Tranxen200Application<1>::CONFIG;

  THCRecords::Device::surfaceDevice.relax = 3;
  THCRecords::Device::surfaceDevice.threshold = 800;
  beatbox.loop();
  checkLed(0, false);
  checkLed(1, false);

  setPiezo(1, 700);
  beatbox.loop();
  checkLed(0, false);
  checkLed(1, true);

  setPiezo(1, 750);
  beatbox.loop();
  checkLed(0, false);
  checkLed(1, true);

  setPiezo(1, 450);
  beatbox.loop();
  checkLed(0, false);
  checkMidiNote(1,37,750*128/1024);
  checkLed(1, true);

  beatbox.loop();
  checkLed(0, false);
  checkLed(1, false);

  THCRecords::Device::surfaceDevice.mode = THCRecords::Tranxen200Application<1>::PLAY;

  setPiezo(0, 500);
  setPiezo(1, 600);
  beatbox.loop();
  checkLed(0, false);
  checkLed(1, false);
  setPiezo(0, 550);
  setPiezo(1, 750);
  beatbox.loop();
  checkLed(0, false);
  checkLed(1, false);

  setPiezo(0, 601);
  setPiezo(1, 900);
  beatbox.loop();
  checkLed(0, true);
  checkLed(1, true);
  setPiezo(0, 650);
  setPiezo(1, 910);
  beatbox.loop();
  checkLed(0, true);
  checkLed(1, true);
  setPiezo(0, 625);
  setPiezo(1, 950);
  beatbox.loop();
  checkLed(0, true);
  checkLed(1, true);
  checkMidiNote(1,36,650*128/1024);
  setPiezo(0, 610);
  setPiezo(1, 925);
  beatbox.loop();
  checkLed(0, true);
  checkLed(1, true);
  checkMidiNote(1,37,950*128/1024);

  setPiezo(0, 500);
  setPiezo(1, 600);
  beatbox.loop();
  checkLed(0, true);
  checkLed(1, true);

  setPiezo(0, 450);
  setPiezo(1, 450);
  beatbox.loop();
  checkLed(0, true);
  checkLed(1, false);

  for(int relaxTime = 0; relaxTime < 22; ++relaxTime) {
    beatbox.loop();
    checkLed(0, true);
    checkLed(1, false);
  }
  setPiezo(0, 900);
  beatbox.loop();
  checkLed(0,true);
  checkLed(1, false);
  setPiezo(0, 850);
  beatbox.loop();
  checkLed(0,true);
  checkLed(1, false);
  setPiezo(0, 450);
  beatbox.loop();
  checkLed(0,true);
  checkLed(1, false);

  for(int relaxTime = 0; relaxTime < 21; ++relaxTime) {
    beatbox.loop();
    checkLed(0, true);
    checkLed(1, false);
  }

  beatbox.loop();
  checkLed(0, false);
  checkLed(1, false);
}

int main(int argc, char **argv)
{
  onePadHit();
  twoPadsConfiguration();

  return 0;
}
