#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <SDL2/SDL.h>
#include "renderer.hpp"

namespace Defender
{
class Renderer;
class Texture
{
    friend class Renderer;
public:
    Texture(SDL_Renderer* sdlRenderer, const int width, const int height);
    Texture(SDL_Renderer* sdlRenderer, const std::string& fileName);

    ~Texture();

    Texture(const Texture& other) = delete;
    Texture& operator = (const Texture& other) = delete;

    Texture(Texture&& other);
    Texture& operator = (Texture&& other);

    const SDL_Rect& getRect() const;
    void setRenderTarget();

private:
    Texture(SDL_Renderer *newSdlRenderer, SDL_Texture* newSdlTexture);
    SDL_Renderer* sdlRenderer = nullptr;
    SDL_Texture* sdlTexture = nullptr;
    SDL_Rect sdlRect;
};
}

#endif // TEXTURE_H
