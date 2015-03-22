#include "mutant.h"

#include "player.h"
#include "defenderutils.h"

Defender::Mutant::Mutant(Defender::Room& room, std::shared_ptr<Defender::Texture> texture,
                         Vector2D position) : Alien(room, texture)
{
    this->position = position;
}

void Defender::Mutant::interact(Entity& entity)
{
    entity.interact(*this);
}

void Defender::Mutant::interact(Player& player)
{
    velocity = getSmallestVectorTo(getMiddle(), player.getMiddle()).normalised() * mutantSpeed;
    Alien::interact(player);
}

void Defender::Mutant::onKill()
{
    room.incrementScore(mutantScore);
    Alien::onKill();
}

void Defender::Mutant::interactWithBomb() {}
