#ifndef MAINGAMEROOM_H
#define MAINGAMEROOM_H

#include <random>
#include "pseudorandomdistribution.h"
#include "room.h"

namespace Defender
{
class MainGameRoom : public Room
{
public:
    MainGameRoom(Game& newGame);

    void update(const double time) override;
    void draw() override;
    void incrementScore(int delta) override;

protected:
    void updateEntity(const double time, std::shared_ptr<Entity> e) override;

private:
    Vector2D cameraPos = Vector2D();
    Vector2D radarPos = Vector2D();

    std::default_random_engine engine;
    Defender::pseudo_random_distribution distribution;

    bool playerAlive;
    int bombs = 1;
    int nextBombScore = 10;
};
}

#endif // MAINGAMEROOM_H
