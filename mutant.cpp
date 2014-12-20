#include "mutant.h"

#include "player.h"

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
        Vector2D newDisplacement = p->getMiddle() - getMiddle();
        double distance = newDisplacement.magnitude();

        if ((p->getMiddle() - getMiddle() + Vector2D(worldWidth, 0))
                .magnitude() < distance)
        {
            newDisplacement = p->getMiddle() - getMiddle()
                    + Vector2D(worldWidth, 0);
            distance = newDisplacement.magnitude();
        }
        if ((p->getMiddle() - getMiddle() - Vector2D(worldWidth, 0))
                .magnitude() < distance)
        {
            newDisplacement = p->getMiddle() - getMiddle()
                    - Vector2D(worldWidth, 0);
            distance = newDisplacement.magnitude();
        }

        velocity = newDisplacement.normalised() * 500;
    }

    Alien::interact(e);
}
