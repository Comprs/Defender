#include "pauseroom.h"

#include "globals.h"
#include "gamecontrollermanager.h"
#include "mainmenu.h"

Defender::PauseRoom::PauseRoom(Game &newGame) : MenuRoom(newGame, 2, "Paused") {}

void Defender::PauseRoom::select(int selectionNumber)
{
    switch (selectionNumber)
    {
    case 0:
        game.killTopRoom();
        return;
    case 1:
        game.replaceNewRoom<MainMenu>();
        return;
    default:
        throw std::runtime_error("Invalid menu selection\nValue: " +
                                 std::to_string(selectionNumber));
        break;
    }
}

void Defender::PauseRoom::update(const double time)
{
    if (GameControllerManager::wasPressed(SDL_CONTROLLER_BUTTON_START))
    {
        game.killTopRoom();
        return;
    }
    MenuRoom::update(time);
}

void Defender::PauseRoom::draw()
{
    Renderer("Audiowide-Regular.ttf", game.getRenderer(), "Resume").setPosition(40, 40).commit();
    Renderer("Audiowide-Regular.ttf", game.getRenderer(), "Quit").setPosition(40, 80).commit();

    MenuRoom::draw();
}
