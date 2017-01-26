#include "abductor.hpp"

#include "mutant.hpp"
#include "defenderutils.hpp"

Defender::Abductor::Abductor(Room& room, std::shared_ptr<Texture> texture) :
    Alien(room, texture) {}

void Defender::Abductor::interact(Entity& entity)
{
    entity.interact(*this);
}

void Defender::Abductor::interact(Man& man)
{
    // Check than this abductor is not abducting, whether the man is being abducted and if
    // the man is still alive
    if (abducting == nullptr && !man.isAbducted() && !man.isDead())
    {
        // Get the vector to the man
        Vector2D displacementVector = getSmallestVectorTo(getMiddle(), man.getMiddle());
        // Check to see if the distance is smaller than the distance to the current
        // target
        if (displacementVector.magnitude() < distanceToTarget)
        {
            // If so, set the target to the man and retain the distance to it
            target = &man;
            distanceToTarget = displacementVector.magnitude();
        }
    }
}

void Defender::Abductor::update(const double time)
{
    Alien::update(time);

    // If the abductor is abducting
    if (abducting != nullptr)
    {
        // Set the middle of the abducted man to be 32 pixels below the middle of the
        // abductor
        abducting->setMiddle(getMiddle() + Vector2D(0, 32));

        // If at the top of the world
        if (position.y() == 0)
        {
            // Kill itself and the abducted man
            abducting->kill();
            kill();
            // Create a mutant
            room.addEntity<Mutant>("alien2.png", position);
        }
    }
}

void Defender::Abductor::onKill()
{
    // Modify the score
    room.incrementScore(1);

    // Attempt to detach the man
    detachMan();

    Alien::onKill();
}

void Defender::Abductor::afterInteraction()
{
    // If the abductor has a valid target
    if (target != nullptr)
    {
        // If the target is not currently being abducted and the abductor has collied with
        // the man
        if (!target->isAbducted() && intersect(*target))
        {
            // Attach the man
            abducting = target;
            abducting->abductor = this;

            // Move upwards
            velocity = Vector2D(0, -abductingSpeed);
        }
        else
        {
            // Move towards the target
            velocity = getSmallestVectorTo(getMiddle(),target->getMiddle()).normalised() *
                    abductorSpeed;
        }
    }
    // If the abductor also isn't abducting
    else if (abducting == nullptr)
    {
        // Don't move
        velocity = Vector2D();
    }

    // Reset variable used to determain the next target
    target = nullptr;
    distanceToTarget = 100000;
}

void Defender::Abductor::detachMan()
{
    // If abducting
    if (abducting != nullptr)
    {
        // Detach the abducted
        abducting->abductor = nullptr;
        abducting = nullptr;
    }
}
