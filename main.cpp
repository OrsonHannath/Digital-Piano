#include <iostream>
#include <windows.h>
#include "Piano.h"

using namespace std;

bool debug = true;
int up = 0;
int down = 0;

int main() {

    // Initialize a digital Piano
    Piano *piano = new Piano(0);

    // Add the keys to the piano
    piano->AddKey("C", 261.63, 'Z'); // C Key
    piano->AddKey("D", 293.66, 'X'); // D Key
    piano->AddKey("E", 329.63, 'C'); // E Key
    piano->AddKey("F", 349.23, 'V'); // F Key
    piano->AddKey("G", 392.00, 'B'); // G Key
    piano->AddKey("A", 440.00, 'N'); // A Key
    piano->AddKey("B", 493.88, 'M'); // B Key
    piano->AddKey("C#", 277.18, 'S'); // C# Key
    piano->AddKey("D#", 311.13, 'D'); // D# Key
    piano->AddKey("F#", 369.99, 'G'); // F# Key
    piano->AddKey("G#", 415.30, 'H'); // G# Key
    piano->AddKey("A#", 466.16, 'J'); // A# Key

    while (true){

        // Update all the Pianos Keys to see if they are pressed
        piano->UpdateKeys();

        // Allow user to exit with 'escape' key
        if (GetAsyncKeyState(VK_ESCAPE)){

            cout << "Exiting Digital Piano" << endl;
            break;
        }

        // Increment Octave if 'up' key pressed
        if (GetAsyncKeyState(VK_UP) && up == 0){

            cout << "Incrementing Octave" << endl;
            piano->IncrementOctave();
            up = 1;
        }else if(!GetAsyncKeyState(VK_UP) && up == 1){

            up = 0;
        }

        // Decrement Octave if 'down' key pressed
        if (GetAsyncKeyState(VK_DOWN) && down == 0){

            cout << "Decrementing Octave" << endl;
            piano->DecrementOctave();
            down = 1;
        }else if(!GetAsyncKeyState(VK_DOWN) && down == 1){

            down = 0;
        }
    }
}
