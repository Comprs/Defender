#ifndef MUTANT_H
#define MUTANT_H

#include "alien.h"

namespace Defender
{
class Mutant : public Alien
{
public:
    Mutant(Room& newRoom, std::shared_ptr<Texture> newTexture, Vector2D startPosition);

protected:
    void interact(std::shared_ptr<Entity>& e) override;
    void onKill() override;
};
}

#endif // MUTANT_H
