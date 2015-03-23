#include "abductor.h"

#include "mutant.h"
#include "defenderutils.h"

Defender::Abductor::Abductor(Room& room, std::shared_ptr<Texture> texture) :
    Alien(room, texture) {}

void Defender::Abductor::interact(Entity& entity)
{
    entity.interact(*this);
}

void Defender::Abductor::interact(Man& man)
{
    if (abducting == nullptr && !man.isAbducted() && !man.isDead())
    {
        Vector2D displacementVector = getSmallestVectorTo(getMiddle(), man.getMiddle());
        if (displacementVector.magnitude() < distanceToTarget)
        {
            target = &man;
            distanceToTarget = displacementVector.magnitude();
        }
    }
}

void Defender::Abductor::update(const double time)
{
    Alien::update(time);

    if (abducting != nullptr)
    {
        abducting->setMiddle(getMiddle() + Vector2D(0, 32));
        if (position.y() == 0)
        {
            abducting->kill();
            kill();
            room.addEntity<Mutant>("alien2.png", position);
        }
    }
}

void Defender::Abductor::onKill()
{
    room.incrementScore(1);
    if (abducting != nullptr)
    {
        abducting->abductor = nullptr;
        abducting = nullptr;
    }
    Alien::onKill();
}

void Defender::Abductor::afterInteraction()
{
    if (target != nullptr)
    {
        if (!target->isAbducted() && intersect(*target))
        {
            abducting = target;
            abducting->abductor = this;
            velocity = Vector2D(0, -abductingSpeed);
        }
        else
        {
            velocity = getSmallestVectorTo(getMiddle(),target->getMiddle()).normalised() *
                    abductorSpeed;
        }
    }
    else if (abducting == nullptr)
    {
        velocity = Vector2D();
    }

    target = nullptr;
    distanceToTarget = 100000;
}
