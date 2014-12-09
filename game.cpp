#include "game.h"

#include <stdexcept>
#include "textureregistry.h"
#include "keyboardmanager.h"

Defender::Game::Game()
{
    TextureRegistry::attachRenderer(window.sdlRenderer);
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
        return nullptr;
    }
    return rooms.back();
}

void Defender::Game::update()
{
    getActiveRoom()->update(clock.getTimeSpan());
}

void Defender::Game::draw()
{
    getActiveRoom()->draw();
}

void Defender::Game::eventLoop()
{
    window.eventLoop();
}

void Defender::Game::present()
{
    SDL_RenderPresent(window.sdlRenderer);
}

void Defender::Game::clear()
{
    SDL_RenderClear(window.sdlRenderer);
}

void Defender::Game::updateKeyboard()
{
    Defender::KeyboardManager::update();
}

void Defender::Game::begin()
{
    while (window.isOpen())
    {
        eventLoop();
        updateKeyboard();

        clear();

        if (getActiveRoom() == nullptr)
        {
            throw std::runtime_error("No active room");
        }
        update();
        draw();

        present();
        clock.tick(60);
    }
}
