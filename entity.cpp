#include "entity.h"

#include "renderer.h"

Defender::Entity::Entity(std::vector<std::shared_ptr<Entity>>& newEntities,
                         Room& newRoom, std::shared_ptr<Texture> newTexture) :
    entities(newEntities), room(newRoom)
{
    texture = newTexture;

    position = Vector2D();
    velocity = Vector2D();
    acceleration = Vector2D();
}

void Defender::Entity::update(const double time, std::shared_ptr<Entity> self)
{
    __unused(self);
    for (std::shared_ptr<Entity> e : entities)
    {
        interact(e);
    }

    position += velocity * time + 0.5 * time * time * acceleration;
    velocity += acceleration * time;

    while (position.x() >= room.width)
    {
        position.x() -= room.width;
    }
    while (position.x() < 0)
    {
        position.x() += room.width;
    }

    if (position.y() < 0)
    {
        position.y() = 0;
    }
    else if (position.y() > room.height - texture->getRect().h)
    {
        position.y() = room.height - texture->getRect().h;
    }

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
    SDL_RendererFlip flip;
    if (facingRight)  { flip = SDL_FLIP_NONE; }
    else { flip = SDL_FLIP_HORIZONTAL; }
    Defender::Renderer(*texture).setPosition(position).setFlip(flip)
            .addOffset(room.width, 0).addOffset(-room.width, 0).commit();
}

void Defender::Entity::kill()
{
    onKill();
    dead = true;
}

bool Defender::Entity::isSame(const std::shared_ptr<Entity> &e) const
{
    return (&(*e) == this);
}

bool Defender::Entity::isDead() const
{
    return dead;
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

const Defender::Vector2D& Defender::Entity::getPosition() const
{
    return position;
}
