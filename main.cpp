#include "game.h"
#include "mainmenu.h"
#include "fontregistry.h"

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    Defender::FontRegistry::addFont("Audiowide-Regular.ttf", 32);

    Defender::Game game;
    game.replaceNewRoom<Defender::MainMenu>();
    game.begin();

    SDL_Quit();

    return 0;
}
