#include "gamecontrollermanager.hpp"

#include <cstring>
#include <cmath>

Uint8 Defender::GameControllerManager::prevButtonState[buttonCount] = {};
Uint8 Defender::GameControllerManager::currButtonState[buttonCount] = {};
bool Defender::GameControllerManager::prevAxisState[axisCount] = {};
bool Defender::GameControllerManager::currAxisState[axisCount] = {};
SDL_GameController* Defender::GameControllerManager::gameController = nullptr;

void Defender::GameControllerManager::update()
{
    // If the game controller is not attached
    if (!SDL_GameControllerGetAttached(gameController))
    {
        // Try to attach the game controller
        gameController = SDL_GameControllerOpen(0);
        // If the game controller still isn't attached
        if (gameController == NULL)
        {
            gameController = nullptr;
            // Clear the states
            std::memset(prevButtonState, 0, buttonCount);
            std::memset(currButtonState, 0, buttonCount);
            std::memset(prevAxisState, 0, axisCount);
            std::memset(currAxisState, 0, axisCount);
            // End the call now
            return;
        }
    }

    // Set the previous state to be the current state
    std::memmove(prevButtonState, currButtonState, buttonCount);
    // Set the current state
    for (int i = 0; i < buttonCount; ++i)
    {
        currButtonState[i] = SDL_GameControllerGetButton(gameController,
                                                   (SDL_GameControllerButton)i);
    }

    // Do the same as above for the axies
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
    // If the button is currently down and wasn't before
    return isDown(button) && !prevButtonState[button];
}

double Defender::GameControllerManager::getAxis(SDL_GameControllerAxis axis)
{
    // Get the value from an integer form between the values -32768 and 32767 and turn it
    // into a double between the values -1 and 1
    Sint16 rawValue = SDL_GameControllerGetAxis(gameController, axis);
    double value = 0.0;
    if (rawValue == -32768) { value = -1.0; }
    else { value = rawValue / 32767.0; }

    // If the magnitude is smaller than the deadzone, return 0
    if (std::abs(value) < deadZone) { return 0; }
    return value;
}

bool Defender::GameControllerManager::wasAxisTapped(SDL_GameControllerAxis axis)
{
    // If the axis has been move and wasn't before
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
