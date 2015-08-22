#pragma once

namespace THCRecords
{
namespace Device
{

template<int NEXT_PIN, int UP_PIN, int DOWN_PIN>
struct MidiSetting
{
  void setup()
  {
    pinMode(NEXT_PIN, INPUT);
    pinMode(UP_PIN, INPUT);
    pinMode(DOWN_PIN, INPUT);
  }
  int getUp()
  {
    return digitalRead(UP_PIN);
  }
  int getDown()
  {
    return digitalRead(DOWN_PIN);
  }
  int getNext()
  {
    return digitalRead(NEXT_PIN);
  }
};

}

namespace Logic
{

template<typename MIDI_DEVICE>
struct MidiSetting
{
  static const unsigned long ScanPeriod = 1000; //in ms

  MIDI_DEVICE _device;
  int _channel;

  unsigned long _lastScan;
  bool _next;
  bool _up;
  bool _down;

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
