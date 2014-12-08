#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include "texture.h"
#include "vector.h"

namespace Defender
{
class Texture;
class Renderer
{
public:
    Renderer(Defender::Texture& texture);

    void commit();
    void operator () ();

    Renderer& setSrcRect(const SDL_Rect& newSrcRect);
    Renderer& setDestRect(const SDL_Rect& newDestRect);
    Renderer& setAngle(const double newAngle);
    Renderer& setCentre(const SDL_Point& newCentre);
    Renderer& setFlip(const SDL_RendererFlip newFlip);

    Renderer& setPosition(const Defender::Vector2D& position);
    Renderer& setPosition(const int x, const int y);

private:
    SDL_Renderer* sdlRenderer;
    SDL_Texture* sdlTexture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    double angle;
    SDL_Point centre;
    SDL_RendererFlip flip;
};
}

#endif // RENDERER_H
