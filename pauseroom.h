#ifndef PAUSEROOM
#define PAUSEROOM

#include "menuroom.h"
#include "defenderutils.h"

namespace Defender
{
class PauseRoom : public MenuRoom
{
public:
    PauseRoom(Game& game);

    void update(const double time) override;
    void draw() override;

protected:
    void select(int selectionNumber) override;
};
}

#endif // PAUSEROOM

