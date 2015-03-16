#include "maingameroom.h"

#include <typeinfo>
#include <chrono>
#include "globals.h"
#include "player.h"
#include "mainmenu.h"
#include "keyboardmanager.h"

#include "abductor.h"
#include "fighter.h"
#include "man.h"
#include "alienprojectile.h"

Defender::MainGameRoom::MainGameRoom(Game &newGame) :
    Room(newGame, Defender::worldWidth, Defender::worldHeight)
{
    distribution = Defender::pseudo_random_distribution(0.005);
    engine.seed(std::chrono::high_resolution_clock::now().time_since_epoch()
                .count());
    // Add the entities
    addEntity<Player>("player.png");
    for (int i = 0; i < 20; ++i) { addEntity<Man>("man.png"); }
}

void Defender::MainGameRoom::draw()
{
    // Create a texture to renderer the world ont
    Texture target  = Texture(game.getRenderer(), width, height);
    // Set the target to the new texture
    target.setRenderTarget();
    // Clear it
    SDL_RenderClear(game.getRenderer());

    // Create a renderer to render the background
    Renderer r = Renderer("background.png");
    // Set enougth offsets to cover the whole world
    for (int i = 0; i < width;
         i += TextureRegistry::getTexture("background.png")->getRect().w)
    {
        r.addOffset(i, 0);
    }
    // Render
    r();

    // Perform the render functions of the parent class
    Room::draw();

    // Reset the renderer target
    SDL_SetRenderTarget(game.getRenderer(), nullptr);

    // Render the rendered world onto the screen three times to create the
    // illusion of an infinte world
    Renderer(target).addOffset(width, 0).addOffset(-width, 0)
            .setPosition(-cameraPos + Vector2D(0, radarHeight)).commit();

    // Render the renderer world onto the screen again but with a destrect such
    // that the entire world will be visable
    SDL_Rect destRect = {int(-radarPos.x()), 0, radarWidth, radarHeight};
    Renderer(target).addOffset(-radarWidth, 0).addOffset(radarWidth, 0)
            .setDestRect(destRect).commit();

    // Render the score counter
    Renderer("Audiowide-Regular.ttf", game.getRenderer(),
             "Score: " + std::to_string(score)).commit();

    // Render the high score counter
    Renderer("Audiowide-Regular.ttf", game.getRenderer(), "High Score: " +
             std::to_string(game.highScore)).setPosition(0, 40).commit();

    Renderer("Audiowide-Regular.ttf", game.getRenderer(), "Bombs: " +
             std::to_string(bombs)).setPosition(0, 80).commit();

    if (!playerAlive)
    {
        Renderer("Audiowide-Regular.ttf", game.getRenderer(),
                 "Press R to reset").setPosition(0, 120).commit();
    }
}

void Defender::MainGameRoom::updateEntity(const double time,
                                          std::shared_ptr<Entity> e)
{
    // Update the entities
    Room::updateEntity(time, e);
    if (typeid(*e) == typeid(Player))
    {
        // A player exist therefore the player is alive
        playerAlive = true;
        // If the entity is the player, set the camera position such that they
        // Will appear in the centre of the screen
        cameraPos.x() = e->getPosition().x() - windowWidth / 2
                + TextureRegistry::getTexture("player.png")->getRect().w / 2;

        // Set the radar camera position such that the player is again centred
        radarPos.x() = e->getPosition().x() / worldWidth * windowWidth
                - radarWidth / 2;
    }
}

void Defender::MainGameRoom::update(const double time)
{
    if (KeyboardManager::wasPressed(SDL_SCANCODE_ESCAPE))
    {
        // If the escaped is pressed, return to the main menu discarding the
        // room
        game.replaceNewRoom<MainMenu>();
    }

    if (distribution(engine))
    {
        addEntity<Abductor>("alien1.png");
    }

    if (distribution(engine))
    {
        addEntity<Fighter>("alien3.png");
    }

    while (score >= nextBombScore)
    {
        ++bombs;
        nextBombScore += 10;
    }

    if (KeyboardManager::wasPressed(SDL_SCANCODE_SPACE) && bombs > 0 &&
            playerAlive)
    {
        --bombs;
        for (std::shared_ptr<Entity> e: entities)
        {
            if (std::shared_ptr<Alien> a = std::dynamic_pointer_cast<Alien>(e))
            {
                a->kill();
            }
            if (std::shared_ptr<AlienProjectile> a =
                    std::dynamic_pointer_cast<AlienProjectile>(e))
            {
                a->kill();
            }
        }
    }

    // Assume the player is dead
    playerAlive = false;
    Room::update(time);

    // Quickly reset if the player is dead
    if (!playerAlive && KeyboardManager::wasPressed(SDL_SCANCODE_R))
    {
        game.replaceNewRoom<MainGameRoom>();
    }
}

void Defender::MainGameRoom::incrementScore(int delta)
{
    if (playerAlive) { score += delta; }
}
