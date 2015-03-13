#include "game.h"

#include <stdexcept>
#include <fstream>
#include "textureregistry.h"
#include "keyboardmanager.h"

Defender::Game::Game()
{
    // Attach renderer to the texture registry retrived from the window
    TextureRegistry::attachRenderer(getRenderer());
    clear();
    present();

    std::ifstream file("highscore.dat");
    file >> highScore;
    file.close();
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
    std::ofstream file("highscore.dat",
                       std::ios_base::out | std::ios_base::trunc);
    file << highScore;
    file.close();
    window.close();
}

SDL_Renderer* Defender::Game::getRenderer() const
{
    // Get the renderer from the window
    return window.sdlRenderer;
}

void Defender::Game::toggleFullscreen()
{
    // Bitwise and the current mode of the window and the flag we wish to check
    if (SDL_GetWindowFlags(window.sdlWindow) & SDL_WINDOW_FULLSCREEN)
    {
        // The window currently is fullscreen so switch to windowed mode
        SDL_SetWindowFullscreen(window.sdlWindow, 0);
        // Make sure the image is not stretched
        SDL_SetWindowSize(window.sdlWindow, Defender::windowWidth,
                          Defender::windowHeight);
    }
    else
    {
        // The window currently is windowed so switch to fullscreen mode
        SDL_SetWindowFullscreen(window.sdlWindow, SDL_WINDOW_FULLSCREEN);
    }
}
