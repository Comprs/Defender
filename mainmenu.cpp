#include "mainmenu.h"

#include "globals.h"
#include "keyboardmanager.h"
#include "maingameroom.h"

Defender::MainMenu::MainMenu(Game &newGame) :
    Room(newGame, windowWidth, windowHeight)
{
    // Prerender the options
    optionTextures.push_back(Renderer("Audiowide-Regular.ttf",
                                      game.getRenderer(),
                                      "Play").getTexture());

    optionTextures.push_back(Renderer("Audiowide-Regular.ttf",
                                      game.getRenderer(),
                                      "Options").getTexture());

    optionTextures.push_back(Renderer("Audiowide-Regular.ttf",
                                      game.getRenderer(),
                                      "Exit").getTexture());
}

void Defender::MainMenu::update(const double time)
{
    // Move the bakground
    backgroundOffset -= time * 50;
    while (backgroundOffset <= -unitWidth)
    {
        backgroundOffset += unitWidth;
    }

    // Increase the selection
    if (KeyboardManager::wasPressed(SDL_SCANCODE_DOWN))
    {
        ++selection;
        if (selection >= numbSelections)
        {
            selection = 0;
        }
    }
    // Decrease the selection
    if (KeyboardManager::wasPressed(SDL_SCANCODE_UP))
    {
        --selection;
        if (selection < 0)
        {
            selection = numbSelections - 1;
        }
    }
    // Accept selection
    if (KeyboardManager::wasPressed(SDL_SCANCODE_RETURN))
    {
        game.replaceNewRoom<MainGameRoom>();
    }
}

void Defender::MainMenu::draw()
{
    // Draw the background
    Renderer("background.png").setPosition(backgroundOffset, radarHeight)
            .addOffset(unitWidth, 0).addOffset(unitWidth * 2, 0).commit();

    // Draw the text
    int drawOffset = 0;
    for (Texture& t : optionTextures)
    {
        Renderer(t).setPosition(0, drawOffset).commit();
        drawOffset += t.getRect().h;
    }
}
