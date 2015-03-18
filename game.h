#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "room.h"
#include "window.h"
#include "clock.h"

namespace Defender
{
class Room;
class Game
{
public:
    Game();

    int highScore = 0;

    void begin();
    void stop();

    template<typename T, typename... Args>
    void pushNewRoom(Args... args)
    {
        rooms.push_back(std::make_shared<T>(*this, args...));
    }

    template<typename T, typename... Args>
    void replaceNewRoom(Args... args)
    {
        rooms.erase(rooms.begin(), rooms.end());
        pushNewRoom<T>(args...);
    }

    void killTopRoom();
    void toggleFullscreen();

    SDL_Renderer* getRenderer() const;

private:
    Window window;
    Clock clock;
    std::vector<std::shared_ptr<Room>> rooms;

    std::shared_ptr<Room> getActiveRoom();
    void update();
    void draw();
    void eventLoop();
    void present();
    void clear();
    void updateKeyboard();
    void updateGameController();
};
}

#endif // GAME_H
