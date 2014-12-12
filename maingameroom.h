#ifndef MAINGAMEROOM_H
#define MAINGAMEROOM_H

#include "room.h"

namespace Defender
{
class MainGameRoom : public Room
{
public:
    MainGameRoom(Game& newGame);

    void updateEntity(const double time, std::shared_ptr<Entity> e) override;
    void draw() override;

private:
    Vector2D cameraPos;
    Vector2D radarPos;
};
}

#endif // MAINGAMEROOM_H
