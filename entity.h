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
class Entity
{
public:
    Entity(Room& newRoom, std::shared_ptr<Texture> newTexture);
    virtual void update(const double time, std::shared_ptr<Entity> self);
    virtual void draw();
    bool intersect(const Entity& e) const;
    bool intersect(const SDL_Rect& r) const;
    void kill();
    bool isDead() const;
    const Vector2D& getPosition() const;
    const Vector2D& getVelocity() const;
    const Vector2D getMiddle() const;
    virtual SDL_Rect getBoundingBox() const;

protected:
    std::shared_ptr<Texture> texture;

    Vector2D position;
    Vector2D velocity;
    Vector2D acceleration;

    double lifeTime = -1.0;
    bool facingRight = true;

    Room& room;

    bool isSame(const std::shared_ptr<Entity>& e) const;
    virtual void interact(std::shared_ptr<Entity>& e) {__unused(e);}
    virtual void interactAll();
    virtual void updatePosition(const double time);
    virtual void bound();
    virtual void updateLifeTime(const double time);
    virtual void onKill() {}
    void setMiddle(const Vector2D& a);

    static std::default_random_engine engine;

private:
    bool dead = false;
};
}

#endif // ENTITY_H
