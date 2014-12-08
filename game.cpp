#include "game.h"

#include "textureregistry.h"
#include "keyboardmanager.h"

Defender::Game::Game()
{
    TextureRegistry::attachRenderer(window.sdlRenderer);
    clear();
    present();
}

void Defender::Game::pushNewRoom(std::shared_ptr<Room> newRoom)
{
    rooms.push_back(newRoom);
}

void Defender::Game::replaceNewRoom(std::shared_ptr<Room> newRoom)
{
    rooms.erase(rooms.begin(), rooms.end());
    pushNewRoom(newRoom);
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

        if (getActiveRoom() != nullptr)
        {
            update();
            draw();
        }

        present();
        clock.tick(60);
    }
}
