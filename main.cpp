#include <stdlib.h>
#include <SDL2/SDL_mixer.h>
#include "game.h"
#include "mainmenu.h"
#include "fontregistry.h"
#include "textureregistry.h"
#include "audioregistry.h"
#include "globals.h"

void quit()
{
    Defender::TextureRegistry::unload();
    Defender::AudioRegistry::unload();
    Defender::FontRegistry::unload();
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}

int main()
{
    // Seed the random engine so that the positions generated won't be the same
    // each time the game is run
    Defender::engine.seed(std::chrono::high_resolution_clock::now().time_since_epoch()
    .count());

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    Mix_Init(0);

    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);

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
        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "A runtime error occured",
                                 e.what(), nullptr);
        quit();
        return EXIT_FAILURE;
    }

    quit();

    return EXIT_SUCCESS;
}
