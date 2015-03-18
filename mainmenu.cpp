#include "mainmenu.h"

#include "globals.h"
#include "keyboardmanager.h"
#include "gamecontrollermanager.h"
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

    // Accept selection
    if (KeyboardManager::wasPressed(SDL_SCANCODE_RETURN) ||
            GameControllerManager::wasPressed(SDL_CONTROLLER_BUTTON_A) ||
            GameControllerManager::wasPressed(SDL_CONTROLLER_BUTTON_START))
    {
        switch (selection)
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
