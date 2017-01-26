#include "mutant.hpp"

#include "player.hpp"
#include "defenderutils.hpp"

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
    // Move towards the player
    velocity = getSmallestVectorTo(getMiddle(), player.getMiddle()).normalised() *
            mutantSpeed;
    Alien::interact(player);
}

void Defender::Mutant::onKill()
{
    // Increase the score
    room.incrementScore(mutantScore);

    Alien::onKill();
}

void Defender::Mutant::interactWithBomb() {}
