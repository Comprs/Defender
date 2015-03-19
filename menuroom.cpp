#include "menuroom.h"

#include "inputmanager.h"

Defender::MenuRoom::MenuRoom(Game &game, int numbSelections, std::string menuTitle) :
    Room(game), numbSelections(numbSelections), menuTitle(menuTitle) {}

void Defender::MenuRoom::update(const double)
{
    // Change the selection
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
        select(selection);
    }
}

void Defender::MenuRoom::updateEntity(const double, std::shared_ptr<Entity>) {}

void Defender::MenuRoom::draw()
{
    Renderer("Audiowide-Regular.ttf", game.getRenderer(), menuTitle).setPosition(40, 0).commit();
    Renderer("Audiowide-Regular.ttf", game.getRenderer(), ">").setPosition(10, 40 * (selection + 1))
            .commit();
}
