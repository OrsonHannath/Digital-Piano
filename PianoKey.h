//
// Created by User on 24/02/2023.
//

#ifndef DIGITALPIANO_PIANOKEY_H
#define DIGITALPIANO_PIANOKEY_H

#include <string>
#include <windows.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <windows.h>

class Piano;

class PianoKey {

private:
    float angle = 0.0;
    float angleOffset = 0.0;
    float bitSize = 16;
    float sampleRate = 44100;
    std::string keyNote;
    float frequency;
    char virtualKey;
    bool pressed;
    Piano *pianoPtr;
    std::ofstream audioFile;
public:
    PianoKey(float freq, char vKey, std::string note, Piano* ptr);
    void ResetAngle();

    void SetAngle(float angle);
    void SetAngleOffset();
    void SetFrequency(float freq);
    void SetVirtualKey(char vKey);
    void SetNote(std::string note);

    void update();
    float ProcessSound();
    void CreateSound();
    void WriteToFile(std::ofstream &file, int value, int size);
};


#endif //DIGITALPIANO_PIANOKEY_H
