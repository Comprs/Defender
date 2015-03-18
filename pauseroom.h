#ifndef PAUSEROOM
#define PAUSEROOM

#include "room.h"
#include "defenderutils.h"

namespace Defender
{
class PauseRoom : public Room
{
public:
    PauseRoom(Game& newGame);

    void update(const double time) override;
    void draw() override;

protected:
    void updateEntity(const double time, std::shared_ptr<Entity> e) override
    {
        __unused(e, time);
    }

private:
    int selection = 0;
    const int numbSelections = 2;
};
}

#endif // PAUSEROOM

