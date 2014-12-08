#include "renderer.h"

Defender::Renderer::Renderer(Defender::Texture &texture)
{
    sdlRenderer = texture.sdlRenderer;
    sdlTexture = texture.sdlTexture;

    srcRect = texture.sdlRect;
    destRect = texture.sdlRect;

    angle = 0;

    centre = {destRect.x / 2, destRect.y / 2};

    flip = SDL_FLIP_NONE;
}

void Defender::Renderer::commit()
{
    SDL_RenderCopyEx(sdlRenderer, sdlTexture, &srcRect, &destRect, angle,
                     &centre, flip);
}

void Defender::Renderer::operator () ()
{
    commit();
}

Defender::Renderer& Defender::Renderer::setSrcRect(const SDL_Rect &newSrcRect)
{
    srcRect = newSrcRect;
    return *this;
}

Defender::Renderer& Defender::Renderer::setDestRect(const SDL_Rect &newDestRect)
{
    destRect = newDestRect;
    return *this;
}

Defender::Renderer& Defender::Renderer::setAngle(const double newAngle)
{
    angle = newAngle;
    return *this;
}

Defender::Renderer& Defender::Renderer::setCentre(const SDL_Point &newCentre)
{
    centre = newCentre;
    return *this;
}

Defender::Renderer& Defender::Renderer::setFlip(const SDL_RendererFlip newFlip)
{
    flip = newFlip;
    return *this;
}

Defender::Renderer& Defender::Renderer::setPosition(const Defender::Vector2D
                                                    &position)
{
    destRect.x = position.x();
    destRect.y = position.y();
    return *this;
}

Defender::Renderer& Defender::Renderer::setPosition(const int x, const int y)
{
    destRect.x = x;
    destRect.y = y;
    return *this;
}
