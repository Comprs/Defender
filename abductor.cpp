#include "abductor.h"

Defender::Abductor::Abductor(std::vector<std::shared_ptr<Entity>>& newEntities,
                             Defender::Room& newRoom,
                             std::shared_ptr<Defender::Texture> newTexture) :
    Alien(newEntities, newRoom, newTexture) {}

void Defender::Abductor::interact(std::shared_ptr<Entity>& e)
{
    double displacementMagnitude = 100000;
    if (std::shared_ptr<Man> targetLock = target.lock())
    {
        if (targetLock->isAbducted())
        {
            displacementMagnitude = 0;
        }
        else
        {
            displacementMagnitude = (targetLock->getMiddle() - getMiddle())
                    .magnitude();
        }
    }

    if (std::shared_ptr<Man> m = std::dynamic_pointer_cast<Man>(e))
    {
        if (!m->isAbducted())
        {
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
        if (intersect(*targetLock))
        {
            targetLock->abduct(self_ptr);
        }

        if (targetLock->isAbducted())
        {
            if (targetLock->abductor.lock() != self_ptr.lock())
            {
                target = std::weak_ptr<Man>();
            }
            velocity = Vector2D(0, -20);
            targetLock->setMiddle(getMiddle() + Vector2D(0, 32));

            if (position.y() <= 0)
            {
                targetLock->kill();
                kill();
            }
        }
    }
    Alien::update(time, self);
}
