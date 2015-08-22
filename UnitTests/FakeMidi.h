#pragma once

class FakeMidi
{
public:
    void sendNoteOn(int note, int volume, int channel)
    {
        std::cout << note << "," << volume << "," << channel << std::endl;
    }
};

FakeMidi MidiOut;