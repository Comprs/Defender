#ifndef GAMECONTROLLERMANAGER_H
#define GAMECONTROLLERMANAGER_H

#include <SDL2/SDL.h>

const int buttonCount = SDL_CONTROLLER_BUTTON_MAX - SDL_CONTROLLER_BUTTON_A;
const int axisCount = SDL_CONTROLLER_AXIS_MAX - SDL_CONTROLLER_AXIS_LEFTX;
const double deadZone = 0.2;

namespace Defender
{
class GameControllerManager
{
public:
    GameControllerManager() = delete;

    static void update();

    static bool wasPressed(SDL_GameControllerButton button);
    static bool isDown(SDL_GameControllerButton button);

    static double getAxis(SDL_GameControllerAxis axis);
    static bool wasAxisTapped(SDL_GameControllerAxis axis);
    static bool wasAxisTapped(SDL_GameControllerAxis axis, bool positive);

private:
    static Uint8 prevButtonState[buttonCount];
    static Uint8 currButtonState[buttonCount];
    static bool prevAxisState[axisCount];
    static bool currAxisState[axisCount];
    static SDL_GameController* gameController;
};
}

#endif // GAMECONTROLLERMANAGER_H
