#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <string>

namespace Defender
{
class Texture
{
public:
    Texture(SDL_Renderer* newSdlRenderer, const int width, const int height);
    Texture(SDL_Renderer* newSdlRenderer, const std::string& fileName);

    ~Texture();

    Texture(const Texture& other) = delete;
    Texture& operator = (const Texture& other) = delete;

    Texture(Texture&& other);
    Texture& operator = (Texture&& other);

    SDL_Texture* sdlTexture = nullptr;
    SDL_Renderer* sdlRenderer = nullptr;
    SDL_Rect sdlRect;
};
}

#endif // TEXTURE_H
