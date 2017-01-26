#ifndef MAN_H
#define MAN_H

#include "entity.hpp"
#include "abductor.hpp"

namespace Defender
{
class Man : public Entity
{
    friend class Abductor;
public:
    Man(Room& room, std::shared_ptr<Texture> texture);

    void update(const double time) override;
    void interact(Entity& entity) override;
    void interact(PlayerProjectile& playerProjectile) override;
    bool isAbducted() const;

protected:
    static std::uniform_real_distribution<double> positionDistribution;
    void onKill() override;

private:
    Abductor* abductor = nullptr;
    pseudo_random_distribution turnDistribution;
};
}

#endif // MAN_H
