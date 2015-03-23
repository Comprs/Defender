#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <vector>
#include <random>
#include "vector.h"
#include "texture.h"
#include "room.h"
#include "globals.h"
#include "defenderutils.h"

namespace Defender
{
class Room;

class Abductor;
class Alien;
class AlienProjectile;
class Fighter;
class Man;
class Mutant;
class Particle;
class Player;
class PlayerProjectile;

class Entity
{
public:
    Entity(Room& room, std::shared_ptr<Texture> texture);
    virtual void update(const double time);
    virtual void draw();
    bool intersect(const Entity& e) const;
    bool intersect(const SDL_Rect& r) const;
    void kill();
    bool isDead() const;
    const Vector2D& getPosition() const;
    const Vector2D& getVelocity() const;
    const Vector2D getMiddle() const;
    virtual SDL_Rect getBoundingBox() const;
    virtual void interact(Entity& entity) = 0;
    virtual void interact(Abductor& abductor);
    virtual void interact(Alien& alien);
    virtual void interact(AlienProjectile& alienProjectile);
    virtual void interact(Fighter& fighter);
    virtual void interact(Man& man);
    virtual void interact(Mutant& mutant);
    virtual void interact(Particle& particle);
    virtual void interact(Player& player);
    virtual void interact(PlayerProjectile& playerProjectile);
    virtual void interactWithBomb();
    virtual void afterInteraction();

protected:
    std::shared_ptr<Texture> texture;
    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;
    double lifeTime = -1.0;
    bool facingRight = true;
    Room& room;

    static std::default_random_engine engine;

    bool isSame(const std::shared_ptr<Entity> e) const;
    virtual void interactAll();
    virtual void updatePosition(const double time);
    virtual void bound();
    virtual void updateLifeTime(const double time);
    virtual void onKill();
    void setMiddle(const Vector2D& a);

private:
    bool dead = false;
};
}

#endif // ENTITY_H
