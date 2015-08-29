#pragma once

namespace THCRecords
{
namespace Logic
{

template<int PAD_NUMBER>
struct TouchPadDevice
{
  Logic::PadInterface* _pad[PAD_NUMBER];
  const PadFactory& _padFactory;

  TouchPadDevice(const PadFactory& padFactory) : _padFactory(padFactory) {}

  void setup()
  {
    for(int pad = 0; pad < PAD_NUMBER; ++pad) {
      _pad[pad] = _padFactory.create(pad);
      _pad[pad]->setup(pad);
    }
  }

  int play(int channel)
  {
    int pad = -1;
    for(int index = 0; index < PAD_NUMBER; ++index) {
      pad = _pad[index]->play(channel) ? index : pad;
    }
    return pad;
  }

  void light(int pad)
  {
    _pad[pad]->light(true);
  }

  void configure(int pad, int threshold, int relax, bool up, bool down)
  {
    _pad[pad]->configure(threshold, relax, up, down);
  }
};

}

template<int PAD_NUMBER>
struct Tranxen200Application
{
  static const int CONFIG = HIGH;
  static const int PLAY   = LOW;

  Logic::TouchPadDevice<PAD_NUMBER> _touchDevice;
  Logic::MidiSetting<Device::TheMidiSetting> _midiSetting;

  Device::TheSurfaceConfiguration& _surfaceDevice;

  int _lastHitPad;
  int _mode;

  Tranxen200Application(const Logic::PadFactory& padFactory,
			Device::TheMidiSetting& midiDevice,
			Device::TheSurfaceConfiguration& surfaceDevice) :
    _touchDevice(padFactory),
    _midiSetting(midiDevice),
    _surfaceDevice(surfaceDevice)
  {}

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
      if(_lastHitPad >= 0)
      {
	_touchDevice.light(_lastHitPad);
	_touchDevice.configure(_lastHitPad,
			       _surfaceDevice.readThreshold(), _surfaceDevice.readRelax(),
			       _midiSetting._up, _midiSetting._down);
      }
    }
    _lastHitPad = _touchDevice.play(_midiSetting._channel);
  }
};

}

