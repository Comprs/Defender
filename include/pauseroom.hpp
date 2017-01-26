#ifndef PAUSEROOM_H
#define PAUSEROOM_H

#include "menuroom.hpp"

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

#endif // PAUSEROOM_H

