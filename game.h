#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include "room.h"
#include "window.h"
#include "clock.h"

namespace Defender
{
class Game
{
public:
    Game();

    void begin();

    void pushNewRoom(std::shared_ptr<Room> newRoom);
    void replaceNewRoom(std::shared_ptr<Room> newRoom);
    void killTopRoom();

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
};
}

#endif // GAME_H
