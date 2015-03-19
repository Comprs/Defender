#ifndef MAN_H
#define MAN_H

#include "entity.h"
#include "abductor.h"

namespace Defender
{
class Man : public Entity
{
    friend class Abductor;
public:
    Man(Room& newRoom, std::shared_ptr<Texture> newTexture);

    void update(const double time, std::shared_ptr<Entity> self) override;
    bool isAbducted() const;

protected:
    void interact(std::shared_ptr<Entity>& e) override;
    void onKill() override;
    static std::uniform_real_distribution<double> positionDistribution;

private:
    std::weak_ptr<Entity> abductor;
    void abduct(std::weak_ptr<Entity> a);
    void drop();
};
}

#endif // MAN_H
