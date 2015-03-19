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
    MainGameRoom(Game& game);

    void update(const double time) override;
    void draw() override;
    void incrementScore(int delta) override;
    Vector2D getPlayerPos();

protected:
    void updateEntity(const double time, std::shared_ptr<Entity> e) override;

private:
    Vector2D cameraPos = Vector2D();
    Vector2D radarPos = Vector2D();
    Vector2D playerPos = Vector2D();

    std::default_random_engine engine;
    pseudo_random_distribution spawnDistribution;
    std::normal_distribution<> spawnFighterDistribution;
    std::normal_distribution<> spawnAbductorDistribution;

    bool playerAlive;
    int bombs = 0;
    int nextBombScore = 20;
};
}

#endif // MAINGAMEROOM_H
