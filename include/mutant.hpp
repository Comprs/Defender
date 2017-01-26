#ifndef MUTANT_H
#define MUTANT_H

#include "alien.hpp"

namespace Defender
{
class Mutant : public Alien
{
public:
    Mutant(Room& room, std::shared_ptr<Texture> texture, Vector2D position);
    void interact(Entity& entity) override;
    void interact(Player& player) override;
    void interactWithBomb() override;

protected:
    void onKill() override;
};
}

#endif // MUTANT_H
