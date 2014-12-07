#include "keyboardmanager.h"

#include <cstdlib>
#include <cstring>

// Allocate memory for the C arrays holding the current and previous state
// of the keyboard
Uint8* Defender::KeyboardManager::prevState =
        (Uint8*)std::malloc(SDL_NUM_SCANCODES);
Uint8* Defender::KeyboardManager::currState =
        (Uint8*)std::malloc(SDL_NUM_SCANCODES);

void Defender::KeyboardManager::update()
{
    // Move the values in the current state array into the previous state array
    std::memmove(prevState, currState, SDL_NUM_SCANCODES);
    // Copy the values in the array given by SDL into the current state array
    std::memcpy(currState, SDL_GetKeyboardState(nullptr), SDL_NUM_SCANCODES);
}

bool Defender::KeyboardManager::isDown(SDL_Scancode key)
{
    return currState[key];
}

bool Defender::KeyboardManager::wasPressed(SDL_Scancode key)
{
    // If the key is currently down and was not down in the previous update
    return isDown(key) && !prevState[key];
}
