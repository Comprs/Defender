#include "texture.h"

#include <stdexcept>
#include <algorithm>
#include <SDL2/SDL_image.h>

// Create a blank texture
Defender::Texture::Texture(SDL_Renderer* sdlRenderer, const int width, const int height) :
    sdlRenderer(sdlRenderer)
{
    // Create the texture
    this->sdlTexture = SDL_CreateTexture(this->sdlRenderer, SDL_PIXELFORMAT_RGBA8888,
                                         SDL_TEXTUREACCESS_TARGET, width, height);

    if (this->sdlTexture == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }

    // Set the properties of the rect
    this->sdlRect = {0, 0, width, height};
}

// Load a texture
Defender::Texture::Texture(SDL_Renderer* sdlRenderer, const std::string &fileName) :
    sdlRenderer(sdlRenderer)
{
    // Load the texture
    this->sdlTexture = IMG_LoadTexture(sdlRenderer, fileName.c_str());

    if (this->sdlTexture == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }

    // Set the properties of the rect
    this->sdlRect.x = 0;
    this->sdlRect.y = 0;
    SDL_QueryTexture(this->sdlTexture, nullptr, nullptr, &this->sdlRect.w, &this->sdlRect.h);
}

// Create a texture out of a given SDL_Renderer and SDL_Texture
Defender::Texture::Texture(SDL_Renderer* sdlRenderer, SDL_Texture* sdlTexture) :
    sdlRenderer(sdlRenderer), sdlTexture(sdlTexture)
{
    this->sdlRect = {0, 0, 0, 0};
    SDL_QueryTexture(this->sdlTexture, nullptr, nullptr, &this->sdlRect.w, &this->sdlRect.h);
}

Defender::Texture::~Texture()
{
    // Destory the texture
    SDL_DestroyTexture(sdlTexture);
    sdlTexture = nullptr;
}

// Move constructor
Defender::Texture::Texture(Texture&& other)
{
    sdlRenderer = other.sdlRenderer;
    other.sdlRenderer = nullptr;

    sdlTexture = other.sdlTexture;
    other.sdlTexture = nullptr;

    sdlRect = std::move(other.sdlRect);
}

// Move assignment
Defender::Texture& Defender::Texture::operator = (Texture&& other)
{
    sdlRenderer = other.sdlRenderer;
    other.sdlRenderer = nullptr;

    sdlTexture = other.sdlTexture;
    other.sdlTexture = nullptr;

    sdlRect = std::move(other.sdlRect);
    return *this;
}

const SDL_Rect& Defender::Texture::getRect() const
{
    return sdlRect;
}

void Defender::Texture::setRenderTarget()
{
    // Set the render target to this texture
    SDL_SetRenderTarget(sdlRenderer, sdlTexture);
}
