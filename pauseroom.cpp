#include "pauseroom.h"

#include "globals.h"
#include "keyboardmanager.h"
#include "gamecontrollermanager.h"
#include "mainmenu.h"

Defender::PauseRoom::PauseRoom(Game &newGame) :
    Room(newGame, worldWidth, worldHeight) {}

void Defender::PauseRoom::update(const double time)
{
    __unused(time);

    if (KeyboardManager::wasPressed(SDL_SCANCODE_DOWN) ||
            KeyboardManager::wasPressed(SDL_SCANCODE_S) ||
            GameControllerManager::wasAxisTapped(SDL_CONTROLLER_AXIS_LEFTY, true))
    {
        ++selection;
        if (selection > numbSelections - 1) { selection = 0; }
    }
    if (KeyboardManager::wasPressed(SDL_SCANCODE_UP) ||
            KeyboardManager::wasPressed(SDL_SCANCODE_W) ||
            GameControllerManager::wasAxisTapped(SDL_CONTROLLER_AXIS_LEFTY, false))
    {
        --selection;
        if (selection < 0) { selection = numbSelections - 1; }
    }

    if (KeyboardManager::wasPressed(SDL_SCANCODE_RETURN) ||
            GameControllerManager::wasPressed(SDL_CONTROLLER_BUTTON_A))
    {
        switch (selection)
        {
        case 0:
            game.killTopRoom();
            return;
        case 1:
            game.replaceNewRoom<MainMenu>();
            return;
        default:
            throw std::runtime_error("Invalid menu selection\nValue: " +
                                     std::to_string(selection));
            break;
        }
    }

    if (GameControllerManager::wasPressed(SDL_CONTROLLER_BUTTON_START))
    {
        game.killTopRoom();
        return;
    }
}

void Defender::PauseRoom::draw()
{
    Renderer("Audiowide-Regular.ttf", game.getRenderer(),
             "Paused").setPosition(40, 0).commit();
    Renderer("Audiowide-Regular.ttf", game.getRenderer(),
             "Resume").setPosition(40, 40).commit();
    Renderer("Audiowide-Regular.ttf", game.getRenderer(),
             "Quit").setPosition(40, 80).commit();

    Renderer("Audiowide-Regular.ttf", game.getRenderer(),
             ">").setPosition(10, 40 * selection + 40).commit();
}
