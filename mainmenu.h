#ifndef MAINMENU_H
#define MAINMENU_H

#include "room.h"

namespace Defender
{
class MainMenu : public Room
{
public:
    MainMenu(Game& newGame);

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
    double backgroundOffset = 0;

    std::vector<Texture> optionTextures;
};
}

#endif // MAINMENU_H
