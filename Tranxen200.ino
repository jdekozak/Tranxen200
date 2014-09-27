#include <MIDI.h>
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MidiOut);

#include "Pad.h"
#include "SurfaceConfiguration.h"
#include "MidiSetting.h"

#include "Utils.h"

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

typedef Utils::Cons<Pad<Interface::Pad9>,
             Utils::Cons<Pad<Interface::Pad8>,
                  Utils::Cons<Pad<Interface::Pad7>,
                       Utils::Cons<Pad<Interface::Pad6>,
                            Utils::Cons<Pad<Interface::Pad5>,
                                 Utils::Cons<Pad<Interface::Pad4>,
                                      Utils::Cons<Pad<Interface::Pad3>,
                                           Utils::Cons<Pad<Interface::Pad2>,
                                                Utils::Cons<Pad<Interface::Pad1>,
                                                     Utils::Cons<Pad<Interface::Pad0> >
                                                >
                                           >
                                      >
                                 >
                            >
                       >
                  >
             >
        > PadList;

template<typename Pads>
struct TouchPadDevice : TouchPadDevice<typename Pads::tail>
{
  typename Pads::head _pad;

  void setup()
  {
    _pad.setup();
    TouchPadDevice<typename Pads::tail>::setup();
  }

  int play(int channel)
  {
    int index = TouchPadDevice<typename Pads::tail>::play(channel);
    if(_pad.play(channel))
    {
      index = Utils::length<typename Pads::tail>::size;
    }
    return index;
  }

  void light(int index)
  {
    if (index == Utils::length<typename Pads::tail>::size)
    {
      _pad.light(true);
    }
    else
    {
      TouchPadDevice<typename Pads::tail>::light(index);
    }
  }

  void configure(int index, int threshold, int relax, const MidiSetting<Interface::TheMidiSetting>& midiSetting)
  {
    if (index == Utils::length<typename Pads::tail>::size)
    {
      _pad.configure(threshold,relax);
      if (midiSetting._up)
      {
	++(_pad._note);
      }
      else if (midiSetting._down)
      {
	--(_pad._note);
      }
    }
    else
    {
      TouchPadDevice<typename Pads::tail>::configure(index, threshold, relax, midiSetting);
    }
  }
};

template<>
struct TouchPadDevice<Utils::Nil>
{
  void setup()
  {}
  int play(int)
  {
    return -1;
  }
  void light(int)
  {}
  void configure(int, int, int, const MidiSetting<Interface::TheMidiSetting>&)
  {}
};

}

struct TouchPad
{
  Logic::TouchPadDevice<Logic::PadList> _touchDevice;
  Interface::TheSurfaceConfiguration _device;
  int _lastHitPad;

  void setup()
  {
    _lastHitPad = -1;

    _device.setup();

    _touchDevice.setup();
  }

  void configure(Logic::MidiSetting<Interface::TheMidiSetting>& midiSetting)
  {
    
    _touchDevice.light(_lastHitPad);
    _touchDevice.configure(_lastHitPad,
			   _device.readThreshold(),
			   _device.readRelax(),
			   midiSetting);
    this->play(midiSetting);
  }

  void play(Logic::MidiSetting<Interface::TheMidiSetting>& midiSetting)
  {
    _lastHitPad = _touchDevice.play(midiSetting._channel);
  }

};

struct Tranxen200
{
  static const int CONFIG = HIGH;
  static const int PLAY   = LOW;

  Logic::MidiSetting<Interface::TheMidiSetting> _midiSetting;
  TouchPad _touchPad;

  int _mode;

  void setup()
  {
    _mode = PLAY;
    _midiSetting.setup();
    _touchPad.setup();
  }

  void loop()
  {
    _mode = _touchPad._device.getMode();
    if (_mode == CONFIG)
    {
      _midiSetting.readValues();
      _touchPad.configure(_midiSetting);
    }
    else
    {
      _touchPad.play(_midiSetting);
    }
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

