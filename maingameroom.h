#ifndef MAINGAMEROOM_H
#define MAINGAMEROOM_H

#include "room.h"

namespace Defender
{
class MainGameRoom : public Room
{
public:
    MainGameRoom(Game& newGame);

    void update(const double time) override;
    void draw() override;

protected:
    void updateEntity(const double time, std::shared_ptr<Entity> e) override;

private:
    Vector2D cameraPos;
    Vector2D radarPos;
};
}

#endif // MAINGAMEROOM_H
