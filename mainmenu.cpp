#include "mainmenu.h"

#include "globals.h"
#include "keyboardmanager.h"
#include "maingameroom.h"

Defender::MainMenu::MainMenu(Game &newGame) :
    Room(newGame, windowWidth, windowHeight) {}

void Defender::MainMenu::update(const double time)
{
    backgroundOffset -= time * 50;
    while (backgroundOffset <= -unitWidth)
    {
        backgroundOffset += unitWidth;
    }

    if (KeyboardManager::wasPressed(SDL_SCANCODE_DOWN))
    {
        ++selection;
        if (selection >= numbSelections)
        {
            selection = 0;
        }
    }
    if (KeyboardManager::wasPressed(SDL_SCANCODE_UP))
    {
        --selection;
        if (selection < 0)
        {
            selection = numbSelections - 1;
        }
    }
    if (KeyboardManager::wasPressed(SDL_SCANCODE_RETURN))
    {
        game.replaceNewRoom<MainGameRoom>();
    }
}

void Defender::MainMenu::draw()
{
    Renderer("background.png").setPosition(backgroundOffset, radarHeight)
            .addOffset(unitWidth, 0).addOffset(unitWidth * 2, 0).commit();
}
