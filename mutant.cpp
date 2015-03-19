#include "mutant.h"

#include "player.h"
#include "defenderutils.h"

Defender::Mutant::Mutant(Defender::Room& room, std::shared_ptr<Defender::Texture> texture,
                         Vector2D position) : Alien(room, texture)
{
    this->position = position;
}

void Defender::Mutant::interact(std::shared_ptr<Entity>& e)
{
    if (auto p = std::dynamic_pointer_cast<Player>(e))
    {
        velocity = getSmallestVectorTo(getMiddle(), p->getMiddle()).normalised() * mutantSpeed;
    }

    Alien::interact(e);
}

void Defender::Mutant::onKill()
{
    room.incrementScore(mutantScore);
    Alien::onKill();
}
