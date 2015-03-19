#include "entity.h"

#include <chrono>
#include "renderer.h"

std::default_random_engine Defender::Entity::engine;

Defender::Entity::Entity(Room& room, std::shared_ptr<Texture> texture) : texture(texture),
    position(Vector2D()), velocity(Vector2D()), acceleration(Vector2D()), room(room)
{
    // Seed the random engine so that the positions generated won't be the same
    // each time the game is run
    engine.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
}

void Defender::Entity::update(const double time, std::shared_ptr<Entity>)
{
    // Perform all updates needed
    interactAll();
    updatePosition(time);
    bound();
    updateLifeTime(time);
}

void Defender::Entity::interact(std::shared_ptr<Entity>&) {}

void Defender::Entity::interactAll()
{
    for (std::shared_ptr<Entity> e : room.entities)
    {
        // Don't interact with itself
        if (isSame(e)) { continue; }
        // Interact with all other entities
        interact(e);
    }
}

void Defender::Entity::updatePosition(const double time)
{
    // Use the equations of motion to perform position updates
    position += velocity * time + 0.5 * time * time * acceleration;
    velocity += acceleration * time;
}

void Defender::Entity::bound()
{
    // Wrap around horizontaly
    while (position.x() >= room.width)
    {
        position.x() -= room.width;
    }
    while (position.x() < 0)
    {
        position.x() += room.width;
    }

    // Keep within the world vertically
    if (position.y() < 0)
    {
        position.y() = 0;
        velocity.y() = 0;
    }
    else if (position.y() > room.height - getBoundingBox().h)
    {
        position.y() = room.height - getBoundingBox().h;
        velocity.y() = 0;
    }
}

void Defender::Entity::updateLifeTime(const double time)
{
    if (lifeTime > 0)
    {
        // If the entity has lifetime left, decrease by the time that has passed
        // in the previous update
        lifeTime -= time;
        if (lifeTime <= 0)
        {
            // If the entity now has no lifetime left (Used to have but no
            // longer as of the previous operation), kill it
            kill();
        }
    }
}

void Defender::Entity::draw()
{
    SDL_RendererFlip flip;
    // Set the variable needed to filp if the entity has filpped
    if (facingRight)  { flip = SDL_FLIP_NONE; }
    else { flip = SDL_FLIP_HORIZONTAL; }

    // Use the renderer to draw. The position and flip are set to the
    // respective properties of itself. Two offsets are used to create the
    // illusion of infinite scrolling, both of worldWidth displacement
    Defender::Renderer(*texture).setPosition(position).setFlip(flip)
            .addOffset(room.width, 0).addOffset(-room.width, 0).commit();
}

void Defender::Entity::kill()
{
    if (!dead)
    {
        // Perform onkill if the entitiy isn't already dead
        onKill();
    }
    // Kill it
    dead = true;
}

bool Defender::Entity::isSame(const std::shared_ptr<Entity> &e) const
{
    // Check that a normal point to the object pointed by the shared pointer is
    // the same as the normal pointer to itself
    return (&(*e) == this);
}

bool Defender::Entity::isDead() const
{
    return dead;
}

bool Defender::Entity::intersect(const Entity& e) const
{
    // Use the bounding boxes to check for intersection
    SDL_Rect r1 = getBoundingBox();
    SDL_Rect r2 = e.getBoundingBox();

    return SDL_HasIntersection(&r1, &r2);
}

// Overload to check for intersection between itself and a SDL_Rect
bool Defender::Entity::intersect(const SDL_Rect &r) const
{
    SDL_Rect r2 = getBoundingBox();

    return SDL_HasIntersection(&r, &r2);
}

const Defender::Vector2D& Defender::Entity::getPosition() const
{
    return position;
}

const Defender::Vector2D& Defender::Entity::getVelocity() const
{
    return velocity;
}

const Defender::Vector2D Defender::Entity::getMiddle() const
{
    // Calculate the middle of the entity by adding on half of the bounding box
    // width and height
    double x = position.x() + getBoundingBox().w / 2;
    double y = position.y() + getBoundingBox().h / 2;
    return Vector2D(x, y);
}

SDL_Rect Defender::Entity::getBoundingBox() const
{
    // Create the bounding box based on the current position and the dimentions
    // of the texture
    SDL_Rect r = texture->getRect();
    r.x = position.x();
    r.y = position.y();
    return r;
}

void Defender::Entity::setMiddle(const Vector2D &a)
{
    // Set the position of the middle by reducing the given value by half of the
    // bounding box
    double x = a.x() - getBoundingBox().w / 2;
    double y = a.y() - getBoundingBox().h / 2;
    position = Vector2D(x, y);
}
