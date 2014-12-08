#include "entity.h"

#include "renderer.h"

Defender::Entity::Entity(std::vector<std::shared_ptr<Entity>>* newEntities,
                         Defender::Texture* newTexture)
{
    entities = newEntities;
    texture = newTexture;
}

void Defender::Entity::update(const double time)
{
    for (std::shared_ptr<Entity> e : *entities)
    {
        interact(e);
    }

    position += velocity * time + 0.5 * time * time * acceleration;
    velocity += acceleration * time;

    if (lifeTime > 0)
    {
        lifeTime -= time;
        if (lifeTime <= 0)
        {
            kill();
        }
    }
}

void Defender::Entity::draw()
{
    Defender::Renderer(*texture).setPosition(position).commit();
}

void Defender::Entity::kill()
{
    onKill();
    dead = true;
}

void Defender::Entity::isSame(std::shared_ptr<Entity> &e) const
{
    return (&(*e) == this);
}

void Defender::Entity::interact(std::shared_ptr<Entity>& e)
{
    if (isSame(e)) { return; }
}

bool Defender::Entity::intersect(const Entity& e) const
{
    SDL_Rect r1 = texture->getRect();
    r1.x = position.x();
    r1.y = position.y();

    SDL_Rect r2 = e.texture->getRect();
    r2.x = e.position.x();
    r2.y = e.position.y();

    return SDL_HasIntersection(&r1, &r2);
}
