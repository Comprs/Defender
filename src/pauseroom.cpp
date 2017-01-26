#include "pauseroom.hpp"

#include "globals.hpp"
#include "gamecontrollermanager.hpp"
#include "mainmenu.hpp"
#include "defenderutils.hpp"

Defender::PauseRoom::PauseRoom(Game& game) : MenuRoom(game, 2, "Paused") {}

void Defender::PauseRoom::select(int selectionNumber)
{
    switch (selectionNumber)
    {
    case 0:
        // Close the room
        game.killTopRoom();
        return;
    case 1:
        // Goto the main menu
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
    // Close the menu
    if (GameControllerManager::wasPressed(SDL_CONTROLLER_BUTTON_START))
    {
        game.killTopRoom();
        return;
    }

    MenuRoom::update(time);
}

void Defender::PauseRoom::draw()
{
    Renderer("Audiowide-Regular.ttf", game.getRenderer(), "Resume")
            .setPosition(40, 40).commit();
    Renderer("Audiowide-Regular.ttf", game.getRenderer(), "Quit")
            .setPosition(40, 80).commit();

    MenuRoom::draw();
}
