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
}
