#ifndef KEYBOARDMANAGER_H
#define KEYBOARDMANAGER_H

#include <SDL2/SDL.h>

namespace Defender
{
class KeyboardManager
{
public:
    KeyboardManager() = delete;

    static void update();

    static bool wasPressed(SDL_Scancode key);
    static bool isDown(SDL_Scancode key);

private:
    static Uint8 prevState[SDL_NUM_SCANCODES];
    static Uint8 currState[SDL_NUM_SCANCODES];
};
}

#endif // KEYBOARDMANAGER_H
