#include "maingameroom.h"

#include "player.h"

Defender::MainGameRoom::MainGameRoom(Game *newGame) : Room(newGame)
{
    addEntity<Player>("player.png");
}
