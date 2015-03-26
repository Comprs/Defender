#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "keyboardmanager.h"
#include "gamecontrollermanager.h"

namespace Defender
{
bool ifOneWasPressed();

template <typename... Args>
inline bool ifOneWasPressed(SDL_GameControllerAxis axis, bool positive, Args... args)
{
    if (Defender::GameControllerManager::wasAxisTapped(axis, positive)) { return true; }
    else { return ifOneWasPressed(args...); }
}

template <typename... Args>
inline bool ifOneWasPressed(SDL_GameControllerAxis axis, Args... args)
{
    if (Defender::GameControllerManager::wasAxisTapped(axis)) { return true; }
    else { return ifOneWasPressed(args...); }
}

template <typename... Args>
inline bool ifOneWasPressed(SDL_GameControllerButton button, Args... args)
{
    if (Defender::GameControllerManager::wasPressed(button)) { return true; }
    else { return ifOneWasPressed(args...); }
}

template <typename... Args>
inline bool ifOneWasPressed(SDL_Scancode key, Args... args)
{
    if (Defender::KeyboardManager::wasPressed(key)) { return true; }
    else { return ifOneWasPressed(args...); }
}
}

#endif // INPUTMANAGER_H

