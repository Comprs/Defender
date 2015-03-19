#include "mutant.h"

#include "player.h"
#include "defenderutils.h"

Defender::Mutant::Mutant(std::vector<std::shared_ptr<Entity>>& newEntities,
                         Defender::Room& newRoom,
                         std::shared_ptr<Defender::Texture> newTexture,
                         Vector2D startPosition) :
    Alien(newEntities, newRoom, newTexture)
{
    position = startPosition;
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
