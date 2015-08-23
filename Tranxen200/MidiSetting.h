#pragma once

namespace THCRecords
{
namespace Logic
{

template<typename MIDI_DEVICE>
struct MidiSetting
{
  static const unsigned long ScanPeriod = 1000; //in ms

  MIDI_DEVICE& _device;
  int _channel;

  unsigned long _lastScan;
  bool _next;
  bool _up;
  bool _down;

  MidiSetting(MIDI_DEVICE& device) : _device(device) {}

  void initialize(unsigned long now)
  {
    _lastScan = now;
    _next  = false;
    _up    = false;
    _down  = false;
  }

  void setup()
  {
    initialize(millis());

    _channel = 1;

    _device.setup();
  }

  void cycleMidiChannel()
  {
    ++_channel;
    if (_channel > 16)
    {
      _channel = 1;
    }
  }
  
  void readValues()
  {
    if (!_next && _device.getNext() == HIGH)
    {
      _next = true;
      cycleMidiChannel();
    }
    if (!_up && _device.getUp() == HIGH)
    {
      _up = true;
    }
    if (!_down && _device.getDown() == HIGH)
    {
      _down = true;
    }

    unsigned long now = millis(); 
    if (now - _lastScan > ScanPeriod)
    {
      initialize(now);
    }
  }

};

}
}

