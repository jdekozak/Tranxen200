#include <MIDI.h>
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MidiOut);

#include "Pad.h"
#include "SurfaceConfiguration.h"
#include "MidiSetting.h"

namespace THCRecords
{
namespace Interface
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

namespace Logic
{

struct TouchPadDevice
{
  Logic::Pad<Interface::Pad0> _pad0;
  Logic::Pad<Interface::Pad1> _pad1;
  Logic::Pad<Interface::Pad2> _pad2;
  Logic::Pad<Interface::Pad3> _pad3;
  Logic::Pad<Interface::Pad4> _pad4;
  Logic::Pad<Interface::Pad5> _pad5;
  Logic::Pad<Interface::Pad6> _pad6;
  Logic::Pad<Interface::Pad7> _pad7;
  Logic::Pad<Interface::Pad8> _pad8;
  Logic::Pad<Interface::Pad9> _pad9;

  void setup()
  {
    _pad0.setup();
    _pad1.setup();
    _pad2.setup();
    _pad3.setup();
    _pad4.setup();
    _pad5.setup();
    _pad6.setup();
    _pad7.setup();
    _pad8.setup();
    _pad9.setup();
  }

  int play(int channel)
  {
    int index = -1;
    index = _pad0.play(channel) ? 0 : index;
    index = _pad1.play(channel) ? 1 : index;
    index = _pad2.play(channel) ? 2 : index;
    index = _pad3.play(channel) ? 3 : index;
    index = _pad4.play(channel) ? 4 : index;
    index = _pad5.play(channel) ? 5 : index;
    index = _pad6.play(channel) ? 6 : index;
    index = _pad7.play(channel) ? 7 : index;
    index = _pad8.play(channel) ? 8 : index;
    index = _pad9.play(channel) ? 9 : index;
    return index;
  }

  void light(int index)
  {
    switch (index)
      {
      case 0:
	_pad0.light(true);
	break;
      case 1:
	_pad1.light(true);
	break;
      case 2:
	_pad2.light(true);
	break;
      case 3:
	_pad3.light(true);
	break;
      case 4:
	_pad4.light(true);
	break;
      case 5:
	_pad5.light(true);
	break;
      case 6:
	_pad6.light(true);
	break;
      case 7:
	_pad7.light(true);
	break;
      case 8:
	_pad8.light(true);
	break;
      case 9:
	_pad9.light(true);
	break;
      default:
	break;
      }
  }
  void configure(int index, int threshold, int relax, bool up, bool down)
  {
    switch (index)
      {
      case 0:
	_pad0.configure(threshold, relax, up, down);
	break;
      case 1:
	_pad1.configure(threshold, relax, up, down);
	break;
      case 2:
	_pad2.configure(threshold, relax, up, down);
	break;
      case 3:
	_pad3.configure(threshold, relax, up, down);
	break;
      case 4:
	_pad4.configure(threshold, relax, up, down);
	break;
      case 5:
	_pad5.configure(threshold, relax, up, down);
	break;
      case 6:
	_pad6.configure(threshold, relax, up, down);
	break;
      case 7:
	_pad7.configure(threshold, relax, up, down);
	break;
      case 8:
	_pad8.configure(threshold, relax, up, down);
	break;
      case 9:
	_pad9.configure(threshold, relax, up, down);
	break;
      default:
	break;
      }
  }
};

}

struct Tranxen200
{
  static const int CONFIG = HIGH;
  static const int PLAY   = LOW;

  Logic::TouchPadDevice _touchDevice;
  Interface::TheSurfaceConfiguration _surfaceDevice;
  Logic::MidiSetting<Interface::TheMidiSetting> _midiSetting;

  int _lastHitPad;
  int _mode;

  void setup()
  {
    _lastHitPad = -1;
    _mode = PLAY;

    _midiSetting.setup();
    _surfaceDevice.setup();
    _touchDevice.setup();
  }

  void loop()
  {
    _mode = _surfaceDevice.getMode();
    if (_mode == CONFIG)
    {
      _midiSetting.readValues();
      _touchDevice.light(_lastHitPad);
      _touchDevice.configure(_lastHitPad,
			     _surfaceDevice.readThreshold(), _surfaceDevice.readRelax(),
			     _midiSetting._up, _midiSetting._down);
    }
    _lastHitPad = _touchDevice.play(_midiSetting._channel);
  }
};

}

THCRecords::Tranxen200 gTranxen200;

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

