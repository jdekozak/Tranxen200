#pragma once

namespace THCRecords
{
namespace Device
{

template<int PIEZO_PIN, int LED_PIN>
struct PadIO
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
}

