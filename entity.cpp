#include "entity.h"

#include <chrono>
#include "renderer.h"

std::default_random_engine Defender::Entity::engine;

std::uniform_real_distribution<double> Defender::Entity::distribution =
        std::uniform_real_distribution<double>(0.0, Defender::worldWidth);

Defender::Entity::Entity(std::vector<std::shared_ptr<Entity>>& newEntities,
                         Room& newRoom, std::shared_ptr<Texture> newTexture) :
    entities(newEntities), room(newRoom)
{
    texture = newTexture;

    engine.seed(std::chrono::high_resolution_clock::now().time_since_epoch()
                .count());

    position = Vector2D();
    velocity = Vector2D();
    acceleration = Vector2D();
}

void Defender::Entity::update(const double time, std::shared_ptr<Entity> self)
{
    __unused(self);
    interactAll();
    updatePosition(time);
    bound();
    updateLifeTime(time);
}

void Defender::Entity::interactAll()
{
    for (std::shared_ptr<Entity> e : entities)
    {
        interact(e);
    }
}

void Defender::Entity::updatePosition(const double time)
{
    position += velocity * time + 0.5 * time * time * acceleration;
    velocity += acceleration * time;
}

void Defender::Entity::bound()
{
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
    else if (position.y() > room.height - getBoundingBox().h)
    {
        position.y() = room.height - getBoundingBox().h;
    }
}

void Defender::Entity::updateLifeTime(const double time)
{
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
    SDL_Rect r1 = getBoundingBox();
    SDL_Rect r2 = e.getBoundingBox();

    return SDL_HasIntersection(&r1, &r2);
}

bool Defender::Entity::intersect(const SDL_Rect &r) const
{
    SDL_Rect r2 = getBoundingBox();

    return SDL_HasIntersection(&r, &r2);
}

const Defender::Vector2D& Defender::Entity::getPosition() const
{
    return position;
}

const Defender::Vector2D Defender::Entity::getMiddle() const
{
    double x = position.x() + getBoundingBox().w / 2;
    double y = position.y() + getBoundingBox().h / 2;
    return Vector2D(x, y);
}

SDL_Rect Defender::Entity::getBoundingBox() const
{
    SDL_Rect r = texture->getRect();
    r.x = position.x();
    r.y = position.y();
    return r;
}

void Defender::Entity::setMiddle(const Vector2D &a)
{
    double x = a.x() - getBoundingBox().w / 2;
    double y = a.y() - getBoundingBox().h / 2;
    position = Vector2D(x, y);
}
