#ifndef ENTITY_H
#define ENTITY_H

#include <memory>
#include <vector>
#include "vector.h"
#include "texture.h"
#include "room.h"

template<typename T>
inline void __unused(T t)
{
    (void)t;
}

template<typename T, typename... Args>
inline void __unused(T t, Args... args)
{
    __unused(t);
    __unused(args...);
}

namespace Defender
{
class Room;
class Entity
{
public:
    Entity(std::vector<std::shared_ptr<Entity>>* newEntities,
           Defender::Room* newRoom,
           std::shared_ptr<Defender::Texture> newTexture);
    virtual void update(const double time, std::shared_ptr<Entity> self);
    virtual void draw();
    bool intersect(const Entity& e) const;
    void kill();
    bool isDead() const;
    const Vector2D& getPosition() const;

protected:
    std::shared_ptr<Defender::Texture> texture;

    Defender::Vector2D position;
    Defender::Vector2D velocity;
    Defender::Vector2D acceleration;

    double lifeTime = -1.0;
    bool facingRight = true;

    std::vector<std::shared_ptr<Entity>>* entities;
    Defender::Room* room;

    bool isSame(const std::shared_ptr<Entity>& e) const;
    virtual void interact(std::shared_ptr<Entity>& e);
    virtual void onKill() {}

private:
    bool dead = false;
};
}

#endif // ENTITY_H
