#include <stdlib.h>
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
        // Create the game
        Defender::Game game;

        // Load in the font
        Defender::FontRegistry::addFont("Audiowide-Regular.ttf", 32);

        // Add the first room which is the menu
        game.replaceNewRoom<Defender::MainMenu>();
        game.begin();
    }
    catch (std::runtime_error e)
    {
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
                                 "A runtime error occured",
                                 e.what(), nullptr);
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Quit();

    return EXIT_SUCCESS;
}
