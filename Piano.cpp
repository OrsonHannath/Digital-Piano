#include "Piano.h"

// Piano Constructor
Piano::Piano(int octaveValue) {

    SetOctave(octaveValue);
}

// Update each key in the piano to check if they are activated
void Piano::UpdateKeys() {

    for (const auto& keyMap : keysMap){

        keyMap.second->update();
    }
}

// Add a Key to this Piano
void Piano::AddKey(std::string keyStr, float freq, char vKey) {

    PianoKey *pianoKey = new PianoKey(freq, vKey, keyStr, this);
    keysMap[keyStr] = pianoKey;
}

// Get a Key from this Piano
PianoKey* Piano::GetKey(std::string keyStr) {

    if (keysMap.find(keyStr) != keysMap.end()){
        return keysMap[keyStr];
    }else{

        // Key was not found
        return nullptr;
    }
}

// Piano SetOctave Function
void Piano::SetOctave(int octaveValue) {

    octave = octaveValue;
}

void Piano::IncrementOctave(){

    octave += octave;
};

void Piano::DecrementOctave(){

    octave -= octave;
};
