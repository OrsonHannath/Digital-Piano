#ifndef DIGITALPIANO_PIANO_H
#define DIGITALPIANO_PIANO_H

#include <map>
#include <string>
#include "PianoKey.h"

class Piano {

private:
    int octave;
    std::map<std::string, PianoKey*> keysMap;
public:
    Piano(int octaveValue);

    void SetOctave(int octaveValue);
    void IncrementOctave();
    void DecrementOctave();
    void AddKey(std::string keyStr, float freq, char vKey);
    PianoKey *GetKey(std::string keyStr);

    void UpdateKeys();

    int getOctave() {
        return octave;
    }
};


#endif
