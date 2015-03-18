#include "game.h"
#include "mainmenu.h"
#include "fontregistry.h"

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();

    // Catch any error that may occur and display a messagebox stating the
    // error.
    try
    {
        // Load in the font
        Defender::FontRegistry::addFont("Audiowide-Regular.ttf", 32);

        // Create the game and add the first room which is the menu
        Defender::Game game;
        game.replaceNewRoom<Defender::MainMenu>();
        game.begin();
    }
    catch (std::runtime_error e)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "A runtime error occured",
                                 e.what(), nullptr);
    }

    SDL_Quit();

    return 0;
}
