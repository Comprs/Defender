#include "gamecontrollermanager.h"

#include <cstring>
#include <cmath>

Uint8 Defender::GameControllerManager::prevButtonState[buttonCount] = {};
Uint8 Defender::GameControllerManager::currButtonState[buttonCount] = {};
bool Defender::GameControllerManager::prevAxisState[axisCount] = {};
bool Defender::GameControllerManager::currAxisState[axisCount] = {};
SDL_GameController* Defender::GameControllerManager::gameController = nullptr;

void Defender::GameControllerManager::update()
{
    if (!SDL_GameControllerGetAttached(gameController))
    {
        gameController = SDL_GameControllerOpen(0);
        if (gameController == NULL)
        {
            gameController = nullptr;
            std::memset(prevButtonState, 0, buttonCount);
            std::memset(currButtonState, 0, buttonCount);
            std::memset(prevAxisState, 0, axisCount);
            std::memset(currAxisState, 0, axisCount);
            return;
        }
    }
    std::memmove(prevButtonState, currButtonState, buttonCount);
    for (int i = 0; i < buttonCount; ++i)
    {
        currButtonState[i] = SDL_GameControllerGetButton(gameController,
                                                   (SDL_GameControllerButton)i);
    }
    std::memmove(prevAxisState, currAxisState, axisCount);
    for (int i = 0; i < axisCount; ++i)
    {
        currAxisState[i] = getAxis((SDL_GameControllerAxis)i) != 0;
    }
}

bool Defender::GameControllerManager::isDown(SDL_GameControllerButton button)
{
    return currButtonState[button];
}

bool Defender::GameControllerManager::wasPressed(SDL_GameControllerButton button)
{
    return isDown(button) && !prevButtonState[button];
}

double Defender::GameControllerManager::getAxis(SDL_GameControllerAxis axis)
{
    Sint16 rawValue = SDL_GameControllerGetAxis(gameController, axis);
    double value = 0.0;
    if (rawValue == -32768) { value = -1.0; }
    else { value = rawValue / 32767.0; }

    if (std::abs(value) < deadZone) { return 0; }
    return value;
}

bool Defender::GameControllerManager::wasAxisTapped(SDL_GameControllerAxis axis)
{
    return currAxisState[axis] && !prevAxisState[axis];
}

bool Defender::GameControllerManager::wasAxisTapped(SDL_GameControllerAxis axis,
                                                    bool positive)
{
    if (!wasAxisTapped(axis)) { return false; }
    if (positive && getAxis(axis) > 0) { return true; }
    if (!positive && getAxis(axis) < 0) { return true; }
    return false;
}
