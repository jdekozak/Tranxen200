#include <MIDI.h>

MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MidiOut);

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

template<int THRESHOLD_PIN, int RELAX_PIN, int MODE_PIN>
struct SurfaceConfiguration
{
  void setup()
  {
    pinMode(MODE_PIN, INPUT);
  }

  int readThreshold()
  {
    return analogRead(THRESHOLD_PIN);
  }  
  int readRelax()
  {
    return analogRead(RELAX_PIN);
  }
  int getMode()
  {
    return digitalRead(MODE_PIN);
  }
};

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
  
  void configure(int threshold, int relax)
  {
    _threshold = threshold;
    _relax = relax;
  }

  void light(bool value)
  {
    _device.light(value);
  }
};

struct MidiSetting
{
  static const unsigned long ScanPeriod = 1000; //in ms

  Interface::TheMidiSetting _device;
  int _channel;

  unsigned long _lastScan;
  bool _next;
  bool _up;
  bool _down;

  void setup()
  {
    _lastScan = millis();
    _next  = false;
    _up    = false;
    _down  = false;
    
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
      _lastScan = now;
      _next  = false;
      _up    = false;
      _down  = false;
    }
  }

};


struct Nil
{
  typedef Nil head;
  typedef Nil tail;
};

template<typename Head, typename Tail=Nil>
struct Cons
{
  typedef Head head;
  typedef Tail tail;
};

typedef Cons<Pad<Interface::Pad9>,
             Cons<Pad<Interface::Pad8>,
                  Cons<Pad<Interface::Pad7>,
                       Cons<Pad<Interface::Pad6>,
                            Cons<Pad<Interface::Pad5>,
                                 Cons<Pad<Interface::Pad4>,
                                      Cons<Pad<Interface::Pad3>,
                                           Cons<Pad<Interface::Pad2>,
                                                Cons<Pad<Interface::Pad1>,
                                                     Cons<Pad<Interface::Pad0> >
                                                >
                                           >
                                      >
                                 >
                            >
                       >
                  >
             >
        > PadList;

template<typename List>
struct length
{
  static const int size = 1 + length<typename List::tail>::size;
};
template<>
struct length<Nil>
{
  static const int size = 0;
};

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
      index = length<typename Pads::tail>::size;
    }
    return index;
  }

  void light(int index)
  {
    if (index == length<typename Pads::tail>::size)
    {
      _pad.light(true);
    }
    else
    {
      TouchPadDevice<typename Pads::tail>::light(index);
    }
  }

  void configure(int index, int threshold, int relax, const MidiSetting& midiSetting)
  {
    if (index == length<typename Pads::tail>::size)
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
struct TouchPadDevice<Nil>
{
  void setup()
  {}
  int play(int)
  {
    return -1;
  }
  void light(int)
  {}
  void configure(int, int, int, const MidiSetting&)
  {}
};

struct TouchPad
{
  TouchPadDevice<PadList> _touchDevice;
  Interface::TheSurfaceConfiguration _device;
  int _lastHitPad;

  void setup()
  {
    _lastHitPad = -1;

    _device.setup();

    _touchDevice.setup();
  }

  void configure(MidiSetting& midiSetting)
  {
    
    _touchDevice.light(_lastHitPad);
    _touchDevice.configure(_lastHitPad,
			   _device.readThreshold(),
			   _device.readRelax(),
			   midiSetting);
    this->play(midiSetting);
  }

  void play(MidiSetting& midiSetting)
  {
    _lastHitPad = _touchDevice.play(midiSetting._channel);
  }

};

struct Tranxen200
{
  static const int CONFIG = HIGH;
  static const int PLAY   = LOW;

  MidiSetting _midiSetting;
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

