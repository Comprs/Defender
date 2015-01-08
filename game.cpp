#include "game.h"

#include <stdexcept>
#include "textureregistry.h"
#include "keyboardmanager.h"

Defender::Game::Game()
{
    // Attach renderer to the texture registry retrived from the window
    TextureRegistry::attachRenderer(getRenderer());
    clear();
    present();
}

void Defender::Game::killTopRoom()
{
    rooms.pop_back();
}

std::shared_ptr<Defender::Room> Defender::Game::getActiveRoom()
{
    if (rooms.size() == 0)
    {
        // If there are no rooms, return nullptr
        return nullptr;
    }
    // Return the last room in the vector
    return rooms.back();
}

void Defender::Game::update()
{
    // Update the active room
    getActiveRoom()->update(clock.getTimeSpan());
}

void Defender::Game::draw()
{
    // Draw the active room
    getActiveRoom()->draw();
}

void Defender::Game::eventLoop()
{
    // Perform the window's event loop
    window.eventLoop();
}

void Defender::Game::present()
{
    // Present the renderer
    SDL_RenderPresent(getRenderer());
}

void Defender::Game::clear()
{
    // Clear renderer
    SDL_RenderClear(getRenderer());
}

void Defender::Game::updateKeyboard()
{
    // Update the state of the keyboard
    Defender::KeyboardManager::update();
}

void Defender::Game::begin()
{
    // Game loop
    while (window.isOpen())
    {
        // Manage system status
        eventLoop();
        updateKeyboard();

        // Clear the renderer for rendering
        clear();

        // Check that we have a active room
        if (getActiveRoom() == nullptr)
        {
            throw std::runtime_error("No active room");
        }

        // Update the game
        update();

        // Draw and present
        draw();
        present();

        // Keep track of the time. Mantain the game at 60 updates/draws per
        // second
        clock.tick(60);
    }
}

void Defender::Game::stop()
{
    window.close();
}

SDL_Renderer* Defender::Game::getRenderer() const
{
    // Get the renderer from the window
    return window.sdlRenderer;
}
