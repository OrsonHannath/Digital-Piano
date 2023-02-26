#include "PianoKey.h"

PianoKey::PianoKey(float freq, char vKey, std::string note, Piano *ptr) {

    SetFrequency(freq);
    SetVirtualKey(vKey);
    SetNote(note);
    SetAngleOffset();
    pianoPtr = ptr;
}

// Update the Piano Key
void PianoKey::update() {

    // CHECK FOR PIANO KEY INPUT
    if (GetAsyncKeyState(virtualKey) && !pressed){

        // Key has just been pressed
        SetAngleOffset();
        pressed = true;
        std::cout << keyNote << " pressed." << std::endl;
        CreateSound();

    }else if (!GetAsyncKeyState(virtualKey) && pressed){

        // Key has just been released
        ResetAngle();
        pressed = false;
        std::cout << keyNote << " released." << std::endl;
    }
}

// Create a loop-able audio clip of the frequency to be played
void PianoKey::CreateSound() {

    // Determine the path that the exe is being run from
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH);
    std::string currentDirectory = std::string(buffer).substr(0, std::string(buffer).find_last_of("\\/"));
    std::string directory = currentDirectory + "/NoteAudioFiles/";

    // Create a folder at the current running directory
    CreateDirectory(directory.c_str(), NULL);
    audioFile.open(directory + keyNote + ".wav", std::ios::binary);

    // WAV File Header
    audioFile << "RIFF"; // Chunk ID
    audioFile << "----"; // Chunk Data Size
    audioFile << "WAVE"; // RIFF Type

    // Format Chunk
    audioFile << "fmt "; // Chunk ID

    WriteToFile(audioFile, 16, 4); // Chunk Data Size
    WriteToFile(audioFile, 1, 2); // Compression Code
    WriteToFile(audioFile, 1, 2); // Number of Channels
    WriteToFile(audioFile, sampleRate, 4); // Sample Rate
    WriteToFile(audioFile, sampleRate * bitSize / 8, 4); // Bytes per Second (bitRate / 8)
    WriteToFile(audioFile, bitSize / 8, 2); // Block Align
    WriteToFile(audioFile, bitSize, 2); // Significant Bits per Sample (bitSize)

    // Data Chunk
    audioFile << "data"; // Chunk ID
    audioFile << "----"; // Chunk Data Size

    // Set a marker for where the audio chunk data starts
    int preAudioDataPos = audioFile.tellp();

    // Determine the maximum amplitude
    auto maxAmplitude = pow(2, bitSize - 1) - 1;

    // Based on the frequency get a series of sample values ranging from 0 to 1 to 0 to -1 to 0
    for (int i = 0; i < (int)((sampleRate/frequency)); i++){

        // Process the sample value at position
        auto sample = ProcessSound();
        int intSample = static_cast<int> (sample * maxAmplitude);

        // Write the sample value to the file
        WriteToFile(audioFile, intSample, 4);
    }

    // Set a marker for where the audio chunk data ends
    int postAudioDataPos = audioFile.tellp();

    // Update the WAV Header with the chunk data sizes
    audioFile.seekp(preAudioDataPos - 4); // Go to position in audio file that is before the audio data then 4 bytes prior
    WriteToFile(audioFile, postAudioDataPos - preAudioDataPos, 4); // Replace the next 4 bytes with the audio data size

    audioFile.seekp(4, std::ios::beg); // Go to the end of the 4th byte from start of file
    WriteToFile(audioFile, postAudioDataPos - 8, 4); // Replace the next 4 bytes with the wav header size

    // Done creating the WAV
    audioFile.close();

    // Play the sound on a loop
    PlaySound((directory + keyNote + ".wav").c_str(), GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC | SND_LOOP);
}

float PianoKey::ProcessSound() {

    // amp * sin((2pi * freq) / sampleRate)
    float amplitude = 1;
    auto sample = amplitude * sin(angle);
    angle += angleOffset;

    //std::cout << sample << std::endl;
    return sample;
}

void PianoKey::WriteToFile(std::ofstream &file, int value, int bytesSize) {

    file.write(reinterpret_cast<const char*> (&value), bytesSize);
}

void PianoKey::SetFrequency(float freq) {

    frequency = freq;
}

void PianoKey::SetVirtualKey(char vKey) {

    virtualKey = vKey;
}

void PianoKey::SetNote(std::string note) {

    keyNote = note;
}

void PianoKey::SetAngle(float ang) {

    angle = ang;
}

void PianoKey::SetAngleOffset() {

    angleOffset = (2 * M_PI * frequency) / sampleRate;//piano->GetWavCreator()->GetSampleRate();
}

void PianoKey::ResetAngle() {

    angle = 0;
}