#pragma once

namespace THCRecords
{
namespace Device
{

template<int NEXT_PIN, int UP_PIN, int DOWN_PIN>
struct MidiSettingIO
{
  void setup()
  {
    pinMode(NEXT_PIN, INPUT);
    pinMode(UP_PIN, INPUT);
    pinMode(DOWN_PIN, INPUT);
  }
  int getUp() const
  {
    return digitalRead(UP_PIN);
  }
  int getDown() const
  {
    return digitalRead(DOWN_PIN);
  }
  int getNext() const
  {
    return digitalRead(NEXT_PIN);
  }
};

}
}

