#ifndef MAINMENU_H
#define MAINMENU_H

#include "menuroom.h"
#include "defenderutils.h"

namespace Defender
{
class MainMenu : public MenuRoom
{
public:
    MainMenu(Game& game);

    void update(const double time) override;
    void draw() override;

protected:
    void select(int selectionNumber) override;

private:
    double backgroundOffset = 0;
};
}

#endif // MAINMENU_H
