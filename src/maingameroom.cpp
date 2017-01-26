#include "maingameroom.hpp"

#include "globals.hpp"
#include "player.hpp"
#include "pauseroom.hpp"
#include "inputmanager.hpp"
#include "abductor.hpp"
#include "fighter.hpp"
#include "interceptor.hpp"
#include "mutant.hpp"
#include "man.hpp"
#include "alienprojectile.hpp"
#include "particle.hpp"
#include "audioregistry.hpp"

Defender::MainGameRoom::MainGameRoom(Game& game) : Room(game, worldWidth, worldHeight)
{
    this->spawnDistribution = Defender::pseudo_random_distribution(0.0025);
    this->spawnFighterDistribution = std::normal_distribution<>(1, 0.5);
    this->spawnAbductorDistribution = std::normal_distribution<>(3, 1.5);
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

    // Render the bomb counter
    Renderer("Audiowide-Regular.ttf", game.getRenderer(), "Bombs: " +
             std::to_string(bombs)).setPosition(0, 80).commit();

    // If the player isn't alive, render the reset hint
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

    // If the escape key or the start button are pressed, create a pause room
    if (ifOneWasPressed(SDL_SCANCODE_ESCAPE, SDL_CONTROLLER_BUTTON_START))
    {
        game.pushNewRoom<PauseRoom>();
        return;
    }

    // on random chance
    if (spawnDistribution(engine))
    {
        int spawnCount = 0;

        // Spawn in the abductors
        spawnCount = std::lround(spawnAbductorDistribution(engine));
        for (int i = 0; i < spawnCount; ++i) { addEntity<Abductor>("alien1.png"); }

        // Spawn in the Fighters
        spawnCount = std::lround(spawnFighterDistribution(engine));
        for (int i = 0; i < spawnCount; ++i) { addEntity<Fighter>("alien3.png"); }

        // Spawn in the Interceptors
        spawnCount = std::lround(spawnFighterDistribution(engine));
        for (int i = 0; i < spawnCount; ++i) { addEntity<Interceptor>("alien4.png"); }
    }

    // Add more bombs
    while (score >= nextBombScore)
    {
        ++bombs;
        nextBombScore += 20;
    }

    // Detonate a bomb if the player has pressed one of the correct keys, the bomb counter
    // is above 0 and the player is alive
    if (ifOneWasPressed(SDL_SCANCODE_SPACE, SDL_CONTROLLER_BUTTON_X,
                        SDL_CONTROLLER_BUTTON_LEFTSHOULDER) && bombs > 0 && playerAlive)
    {
        // Decrement the counter
        --bombs;

        // Get all of the entities to react to the bomb
        for (std::shared_ptr<Entity> entity: entities)
        {
            entity->interactWithBomb();
        }

        // Create the particles
        std::uniform_real_distribution<> horDis(0, worldWidth);
        std::uniform_real_distribution<> verDis(0, worldHeight);
        std::uniform_real_distribution<> accelerationVariance(-360, 480);
        std::uniform_real_distribution<> velocityVariance(-200, 200);
        for (int i = 0; i < 1000; ++i)
        {
            addEntity<Particle>("explosion.png", Vector2D(horDis(engine), verDis(engine)),
                                -1, Vector2D(velocityVariance(engine), -480),
                                Vector2D(0, 480 + accelerationVariance(engine)));
        }

        // Play the sound effect
        AudioRegistry::play("explosion.wav");
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
