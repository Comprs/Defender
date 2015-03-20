#ifndef MENUROOM
#define MENUROOM

#include "room.h"

namespace Defender
{
class MenuRoom : public Room
{
public:
    MenuRoom(Game& game, int numbSelections, std::string menuTitle);

    void update(const double time) override;
    void draw() override;

protected:
    const int numbSelections;

    void updateEntity(const double time, std::shared_ptr<Entity> e);
    virtual void select(int selectionNumber) = 0;

private:
    int selection = 0;
    const std::string menuTitle;
};
}

#endif // MENUROOM

