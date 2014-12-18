#include "maingameroom.h"

#include <typeinfo>
#include <chrono>
#include "globals.h"
#include "player.h"
#include "mainmenu.h"
#include "keyboardmanager.h"

#include "abductor.h"
#include "man.h"

Defender::MainGameRoom::MainGameRoom(Game &newGame) :
    Room(newGame, Defender::worldWidth, Defender::worldHeight)
{
    distribution = std::bernoulli_distribution(0.015);
    engine.seed(std::chrono::high_resolution_clock::now().time_since_epoch()
                .count());
    // Add the entities
    addEntity<Player>("player.png");
    addEntity<Man>("man.png");
    addEntity<Man>("man.png");
    addEntity<Man>("man.png");
    addEntity<Man>("man.png");
    addEntity<Man>("man.png");
    addEntity<Man>("man.png");
    addEntity<Man>("man.png");
    addEntity<Man>("man.png");
    addEntity<Man>("man.png");
    addEntity<Man>("man.png");
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

    Renderer t = Renderer("Audiowide-Regular.ttf", game.getRenderer(),
                          "Score: " + std::to_string(score));
    t.commit();
}

void Defender::MainGameRoom::updateEntity(const double time,
                                          std::shared_ptr<Entity> e)
{
    // Update the entities
    Room::updateEntity(time, e);
    if (typeid(*e) == typeid(Player))
    {
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

    Room::update(time);
}
