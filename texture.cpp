#include "texture.h"

#include <stdexcept>
#include <algorithm>
#include <SDL2/SDL_image.h>

Defender::Texture::Texture(SDL_Renderer* newSdlRenderer, const int width,
                           const int height)
{
    sdlRenderer = newSdlRenderer;

    sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_RGBA8888,
                                   SDL_TEXTUREACCESS_TARGET, width, height);

    if (sdlTexture == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }

    sdlRect.x = 0;
    sdlRect.y = 0;
    sdlRect.w = width;
    sdlRect.h = height;
}

Defender::Texture::Texture(SDL_Renderer *newSdlRenderer,
                           const std::string &fileName)
{
    sdlRenderer = newSdlRenderer;

    sdlTexture = IMG_LoadTexture(sdlRenderer, fileName.c_str());

    if (sdlTexture == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }

    sdlRect.x = 0;
    sdlRect.y = 0;
    SDL_QueryTexture(sdlTexture, nullptr, nullptr, &sdlRect.w, &sdlRect.h);
}

Defender::Texture::~Texture()
{
    SDL_DestroyTexture(sdlTexture);
    sdlTexture = nullptr;
}

Defender::Texture::Texture(Texture&& other)
{
    sdlRenderer = other.sdlRenderer;
    other.sdlRenderer = nullptr;

    sdlTexture = other.sdlTexture;
    other.sdlTexture = nullptr;

    sdlRect = std::move(other.sdlRect);
}

Defender::Texture& Defender::Texture::operator = (Texture&& other)
{
    sdlRenderer = other.sdlRenderer;
    other.sdlRenderer = nullptr;

    sdlTexture = other.sdlTexture;
    other.sdlTexture = nullptr;

    sdlRect = std::move(other.sdlRect);
    return *this;
}
