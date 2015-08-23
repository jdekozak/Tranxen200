#pragma once

#include <iostream>

struct FakeMidi
{
  int note = 0;
  int volume = 0;
  int channel = 0;
  void sendNoteOn(int n, int v, int c)
  {
    note = n;
    volume = v;
    channel = c;
    std::cout << "FakeMidi::sendNoteOn::" << note << "," << volume << "," << channel << std::endl;
  }
};

FakeMidi MidiOut;
