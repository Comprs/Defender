#include "maingameroom.h"

#include <typeinfo>
#include <chrono>
#include "globals.h"
#include "player.h"
#include "pauseroom.h"
#include "inputmanager.h"
#include "abductor.h"
#include "fighter.h"
#include "mutant.h"
#include "man.h"
#include "alienprojectile.h"
#include "particle.h"

Defender::MainGameRoom::MainGameRoom(Game& game) : Room(game, worldWidth, worldHeight)
{
    this->spawnDistribution = Defender::pseudo_random_distribution(0.0025);
    this->spawnFighterDistribution = std::normal_distribution<>(1, 0.5);
    this->spawnAbductorDistribution = std::normal_distribution<>(3, 1.5);
    this->engine.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
    // Add the entities
    addEntity<Player>("player.png");
    for (int i = 0; i < initialManCount; ++i) { addEntity<Man>("man.png"); }
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
    for (int i = 0; i < width; i +=
         TextureRegistry::getTexture("background.png")->getRect().w)
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
                 "Press R or Start to reset").setPosition(0, 120).commit();
    }
}

void Defender::MainGameRoom::update(const double time)
{
    // Quickly reset if the player is dead
    if (!playerAlive && ifOneWasPressed(SDL_SCANCODE_R, SDL_CONTROLLER_BUTTON_START))
    {
        game.replaceNewRoom<MainGameRoom>();
        return;
    }

    if (ifOneWasPressed(SDL_SCANCODE_ESCAPE, SDL_CONTROLLER_BUTTON_START))
    {
        // If the escaped is pressed, return to the main menu discarding the
        // room
        game.pushNewRoom<PauseRoom>();
        return;
    }

    if (spawnDistribution(engine))
    {
        int spawnCount = 0;
        spawnCount = std::lround(spawnAbductorDistribution(engine));
        for (int i = 0; i < spawnCount; ++i) { addEntity<Abductor>("alien1.png"); }
        spawnCount = std::lround(spawnFighterDistribution(engine));
        for (int i = 0; i < spawnCount; ++i) { addEntity<Fighter>("alien3.png"); }
    }

    while (score >= nextBombScore)
    {
        ++bombs;
        nextBombScore += 20;
    }

    if (ifOneWasPressed(SDL_SCANCODE_SPACE, SDL_CONTROLLER_BUTTON_X,
                        SDL_CONTROLLER_BUTTON_LEFTSHOULDER) && bombs > 0 && playerAlive)
    {
        --bombs;
        for (std::shared_ptr<Entity> entity: entities)
        {
            entity->interactWithBomb();
        }
        std::uniform_real_distribution<> horDis(0, worldWidth);
        std::uniform_real_distribution<> verDis(0, worldHeight);
        std::uniform_real_distribution<> accelerationVariance(-360, 480);
        for (int i = 0; i < 1000; ++i)
        {
            addEntity<Particle>("explosion.png", Vector2D(horDis(engine), verDis(engine)),
                                -1, Vector2D(0, -480),
                                Vector2D(0, 480 + accelerationVariance(engine)));
        }
    }

    Room::update(time);
}

void Defender::MainGameRoom::incrementScore(int delta)
{
    if (playerAlive) { score += delta; }
}

Defender::Vector2D Defender::MainGameRoom::getPlayerPos()
{
    return playerPos;
}
