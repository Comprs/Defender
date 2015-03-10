#include "mainmenu.h"

#include "globals.h"
#include "keyboardmanager.h"
#include "maingameroom.h"

Defender::MainMenu::MainMenu(Game &newGame) :
    Room(newGame, windowWidth, windowHeight) {}

void Defender::MainMenu::update(const double time)
{
    // Move the bakground
    backgroundOffset -= time * 50;
    while (backgroundOffset <= -unitWidth)
    {
        backgroundOffset += unitWidth;
    }

    if (KeyboardManager::wasPressed(SDL_SCANCODE_DOWN) ||
            KeyboardManager::wasPressed(SDL_SCANCODE_S))
    {
        ++selection;
        if (selection > numbSelections) { selection = 0; }
    }
    if (KeyboardManager::wasPressed(SDL_SCANCODE_UP) ||
            KeyboardManager::wasPressed(SDL_SCANCODE_W))
    {
        --selection;
        if (selection < 0) { selection = numbSelections; }
    }

    // Accept selection
    if (KeyboardManager::wasPressed(SDL_SCANCODE_RETURN))
    {
        switch (selection) {
        case 0:
            game.replaceNewRoom<MainGameRoom>();
            break;
        case 1:
            game.toggleFullscreen();
            break;
        case 2:
            game.stop();
            break;
        default:
            throw std::runtime_error("Invalid menu selection\nValue: " +
                                     std::to_string(selection));
            break;
        }
    }
}

void Defender::MainMenu::draw()
{
    // Draw the background
    Renderer("background.png").setPosition(backgroundOffset, radarHeight)
            .addOffset(unitWidth, 0).addOffset(unitWidth * 2, 0).commit();

    // Draw the text
    Renderer("Audiowide-Regular.ttf", game.getRenderer(),
             "Play").setPosition(40, 0).commit();
    Renderer("Audiowide-Regular.ttf", game.getRenderer(),
             "Toggle Fullscreen").setPosition(40, 40).commit();
    Renderer("Audiowide-Regular.ttf", game.getRenderer(),
             "Quit").setPosition(40, 80).commit();

    Renderer("Audiowide-Regular.ttf", game.getRenderer(),
             ">").setPosition(10, 40 * selection).commit();
}
