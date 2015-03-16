#include "abductor.h"

#include "mutant.h"

Defender::Abductor::Abductor(std::vector<std::shared_ptr<Entity>>& newEntities,
                             Defender::Room& newRoom,
                             std::shared_ptr<Defender::Texture> newTexture) :
    Alien(newEntities, newRoom, newTexture) {}

void Defender::Abductor::interact(std::shared_ptr<Entity>& e)
{
    // Set the inital testing value to a large value
    double displacementMagnitude = 100000;
    // Try and lock the current target
    if (std::shared_ptr<Man> targetLock = target.lock())
    {
        if (targetLock->isAbducted())
        {
            // If the target is abducted, make the testing value 0 so that
            // The target will not be changed
            // This assumes that the target is being abducted this instance
            displacementMagnitude = 0;
        }
        else
        {
            // Get the displacement of the current target
            displacementMagnitude = (targetLock->getMiddle() - getMiddle())
                    .magnitude();
        }
    }

    // Check that we are interacting with a Man
    if (std::shared_ptr<Man> m = std::dynamic_pointer_cast<Man>(e))
    {
        if (!m->isAbducted())
        {
            // Check that the displacement to the current interation is smaller
            // than the displacement to the current target
            // This is repeated for +worldWidth and -worldWidth
            Vector2D displacementVector = m->getMiddle() - getMiddle();
            if (displacementVector.magnitude() < displacementMagnitude)
            {
                velocity = displacementVector.normalised() * 50;
                displacementMagnitude = displacementVector.magnitude();
                target = m;
            }
            displacementVector = m->getMiddle() - getMiddle()
                    + Vector2D(worldWidth, 0);
            if (displacementVector.magnitude() < displacementMagnitude)
            {
                velocity = displacementVector.normalised() * 50;
                displacementMagnitude = displacementVector.magnitude();
                target = m;
            }
            displacementVector = m->getMiddle() - getMiddle() -
                    Vector2D(worldWidth, 0);
            if (displacementVector.magnitude() < displacementMagnitude)
            {
                velocity = displacementVector.normalised() * 50;
                displacementMagnitude = displacementVector.magnitude();
                target = m;
            }
        }
    }
    Alien::interact(e);
}

void Defender::Abductor::update(const double time, std::shared_ptr<Entity> self)
{
    self_ptr = self;
    if (std::shared_ptr<Man> targetLock = target.lock())
    {
        // Check to see if this has collieded with its target
        if (intersect(*targetLock))
        {
            // Abduct it
            targetLock->abduct(self_ptr);
        }

        if (targetLock->isAbducted())
        {
            // Check whether the abductor of its target is itself
            if (targetLock->abductor.lock() != self_ptr.lock())
            {
                // If not, set the target to null
                target = std::weak_ptr<Man>();
            }
            else
            {
                // The abductor of its target is itself
                // It should move up
                velocity = Vector2D(0, -20);

                // Set the position of the abducted
                targetLock->setMiddle(getMiddle() + Vector2D(0, 32));

                // If it has reached the top of the world, kill both and spawn
                // a mutant
                if (position.y() <= 0)
                {
                    targetLock->kill();
                    kill();
                    room.addEntity<Mutant>("alien2.png", position);
                }
            }
        }
    }
    Alien::update(time, self);
}

void Defender::Abductor::onKill()
{
    room.score += 1;
    Alien::onKill();
}
