#include "mainmenu.h"

#include "globals.h"
#include "maingameroom.h"

Defender::MainMenu::MainMenu(Game& game) : MenuRoom(game, 3, "Defender") {}

void Defender::MainMenu::update(const double time)
{
    // Move the bakground
    backgroundOffset -= time * 50;
    while (backgroundOffset <= -unitWidth)
    {
        backgroundOffset += unitWidth;
    }

    MenuRoom::update(time);
}

void Defender::MainMenu::select(int selectionNumber)
{
    switch (selectionNumber)
    {
    case 0:
        game.replaceNewRoom<MainGameRoom>();
        return;
    case 1:
        game.toggleFullscreen();
        return;
    case 2:
        game.stop();
        return;
    default:
        throw std::runtime_error("Invalid menu selection\nValue: " +
                                 std::to_string(selectionNumber));
        break;
    }
}

void Defender::MainMenu::draw()
{
    // Draw the background
    Renderer("background.png").setPosition(backgroundOffset, radarHeight)
            .addOffset(unitWidth, 0).addOffset(unitWidth * 2, 0).commit();

    // Draw the text
    Renderer("Audiowide-Regular.ttf", game.getRenderer(), "Play").setPosition(40, 40).commit();
    Renderer("Audiowide-Regular.ttf", game.getRenderer(), "Toggle Fullscreen").setPosition(40, 80)
            .commit();
    Renderer("Audiowide-Regular.ttf", game.getRenderer(), "Quit").setPosition(40, 120).commit();

    MenuRoom::draw();
}
