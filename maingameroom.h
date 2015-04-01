#ifndef MAINGAMEROOM_H
#define MAINGAMEROOM_H

#include <random>
#include "pseudorandomdistribution.h"
#include "room.h"

namespace Defender
{
class MainGameRoom : public Room
{
    friend class Player;
public:
    MainGameRoom(Game& game);

    void update(const double time) override;
    void draw() override;
    void incrementScore(int delta) override;
    Vector2D getPlayerPos();

private:
    Vector2D cameraPos = Vector2D();
    Vector2D radarPos = Vector2D();
    Vector2D playerPos = Vector2D();

    pseudo_random_distribution spawnDistribution;
    std::normal_distribution<> spawnFighterDistribution;
    std::normal_distribution<> spawnAbductorDistribution;

    bool playerAlive;
    int bombs = 0;
    int nextBombScore = 20;
};
}

#endif // MAINGAMEROOM_H
