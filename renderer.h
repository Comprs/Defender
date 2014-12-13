#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <SDL2/SDL.h>
#include "texture.h"
#include "ttffont.h"
#include "vector.h"

namespace Defender
{
class Texture;
class TTFFont;
class Renderer
{
public:
    Renderer(Defender::Texture& texture);
    Renderer(const std::string& textureName);

    Renderer(TTFFont& font, SDL_Renderer* newSdlRenderer,
             const std::string& text);
    Renderer(const std::string &fontName, SDL_Renderer* sdlRenderer,
             const std::string& text);

    void commit();
    void operator () ();

    Renderer& setSrcRect(const SDL_Rect& newSrcRect);
    Renderer& setDestRect(const SDL_Rect& newDestRect);
    Renderer& setAngle(const double newAngle);
    Renderer& setCentre(const SDL_Point& newCentre);
    Renderer& setFlip(const SDL_RendererFlip newFlip);
    Renderer& addOffset(const Vector2D& offset);

    Renderer& setPosition(const Defender::Vector2D& position);
    Renderer& setPosition(const int x, const int y);
    Renderer& addOffset(const int x, const int y);

private:
    SDL_Renderer* sdlRenderer;
    SDL_Texture* sdlTexture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    double angle;
    SDL_Point centre;
    SDL_RendererFlip flip;

    std::vector<Vector2D> offsets;
};
}

#endif // RENDERER_H
