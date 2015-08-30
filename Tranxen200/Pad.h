#pragma once

namespace THCRecords
{
namespace Logic
{

struct PadInterface {
  virtual void setup(int note) = 0;
  virtual bool play(int channel) = 0;
  virtual void configure(int threshold, int relax, bool up, bool down) = 0;
  virtual void light(bool value) = 0;
};

template<typename PAD_DEVICE>
struct Pad : public PadInterface
{
  static const int PadDefaultThreshold = 600; //Default threshold value between 0 and 1023
  static const int PadDefaultRelax     = 100; //Default relax value in ms value between 0 and 1023
  static const int PadNoteOffset       = 36;  //Hydrogen Instrument 1

  PAD_DEVICE& _device;
  int _threshold;
  int _relax;

  int _note;

  int _previousValue;
  unsigned long _hit;

  Pad(PAD_DEVICE& device) : _device(device) {}

  virtual void setup(int note)
  {
    _device.setup();

    _threshold = PadDefaultThreshold;
    _relax = PadDefaultRelax;
    _note = PadNoteOffset + note;

    _hit = 0;
    _previousValue = 0;
  }

  virtual bool play(int channel)
  {
    bool midiNote   = false;
    bool lightState = false;
    unsigned long now = millis();
    
    if (isInhibited(now))
    {
      Serial.println("Inhibit");
      lightState = true;
      _previousValue = 0;
    }
    else
    {
      int measure = _device.readPiezo();
      int difference = measure - _previousValue;
      if(measure > _threshold)
      {
	lightState = true;
      }
      if(difference < 0 && _previousValue > _threshold)
      {
	MidiOut.sendNoteOn(_note, _previousValue*128/1024, channel);
	_hit = now;
	midiNote = true;
	lightState = true;
      }

      _previousValue = measure;
    }

    _device.light(lightState);

    return midiNote;
  }
  
  virtual void configure(int threshold, int relax, bool up, bool down)
  {
    _threshold = threshold;
    _relax = relax;
    if(up) {
      ++_note;
    } else if(down) {
      --_note;
    }
  }

  virtual void light(bool value)
  {
    _device.light(value);
  }

  bool isInhibited(int now)
  {
    return (now - _hit < _relax) && _hit;
  }
};

}
}

