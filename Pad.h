#ifndef __PAD_H__
#define __PAD_H__

namespace THCRecords
{
namespace Interface
{

template<int PIEZO_PIN, int LED_PIN>
struct Pad
{
  void setup()
  {
    pinMode(LED_PIN, OUTPUT);
  }

  int readPiezo()
  {
    return analogRead(PIEZO_PIN);
  }

  void light(bool value)
  {
    value ? digitalWrite(LED_PIN, HIGH) : digitalWrite(LED_PIN, LOW);
  }
};

}

namespace Logic
{

template<typename PAD_DEVICE>
struct Pad
{
  static const int PadDefaultThreshold = 600; //Default threshold value between 0 and 1023
  static const int PadDefaultRelax     = 100; //Default relax value in ms value between 0 and 1023
  static const int PadNoteOffset       = 36;  //Hydrogen Instrument 1

  PAD_DEVICE _device;
  int _threshold;
  int _relax;

  int _note;

  int _volume;
  unsigned long _hit;

  void setup()
  {
    _device.setup();

    _threshold = PadDefaultThreshold;
    _relax = PadDefaultRelax;
    _note = PadNoteOffset;

    _hit = millis();
    _volume = 0;
  }

  bool play(int channel)
  {
    bool midiNote   = false;
    bool lightState = false;
    unsigned long now = millis();
    
    if (now - _hit < _relax)
    {
      Serial.println("Relax");
      lightState = true;
    }
    else
    {
      int measure = _device.readPiezo() - _threshold;
      if ( measure > _volume)
      {
        _volume = measure;
        lightState = true;
      }
      else if (_volume > 0)
      {
        MidiOut.sendNoteOn(_note, (_volume+_threshold)*128/1024, channel);
        Serial.println(_volume);
        Serial.println("Note On");
        midiNote = true;

        _hit = now;
        _volume = 0;

        lightState = true;
      }
      else
      {
        lightState = false;
      }
    }

    _device.light(lightState);

    return midiNote;
  }
  
  void configure(int threshold, int relax, bool up, bool down)
  {
    _threshold = threshold;
    _relax = relax;
    if(up) {
      ++_note;
    } else if(down) {
      --_note;
    }
  }

  void light(bool value)
  {
    _device.light(value);
  }
};

}

}

#endif
