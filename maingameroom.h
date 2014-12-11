#ifndef MAINGAMEROOM_H
#define MAINGAMEROOM_H

#include "room.h"

namespace Defender
{
class MainGameRoom : public Room
{
public:
    MainGameRoom(Game* newGame);

    void draw() override;
};
}

#endif // MAINGAMEROOM_H
