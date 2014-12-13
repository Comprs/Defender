#include "renderer.h"

#include "textureregistry.h"
#include "fontregistry.h"

Defender::Renderer::Renderer(Defender::Texture &texture)
{
    sdlRenderer = texture.sdlRenderer;
    sdlTexture = texture.sdlTexture;

    srcRect = texture.sdlRect;
    destRect = texture.sdlRect;

    angle = 0;

    centre = {destRect.x / 2, destRect.y / 2};

    flip = SDL_FLIP_NONE;

    offsets = {Vector2D()};
}

Defender::Renderer::Renderer(const std::string &textureName) :
    Renderer(*TextureRegistry::getTexture(textureName)) {}

Defender::Renderer::Renderer(TTFFont &font, SDL_Renderer *newSdlRenderer,
                             const std::string &text)
{
    sdlRenderer = newSdlRenderer;

    SDL_Surface* tempsurface = TTF_RenderUTF8_Blended(font.sdlFont,
                                                      text.c_str(),
                                                      {255, 255, 255, 255});

    sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, tempsurface);
    destroyTexture = true;

    SDL_FreeSurface(tempsurface);
    tempsurface = nullptr;

    srcRect = {0, 0, 0, 0};
    SDL_QueryTexture(sdlTexture, nullptr, nullptr, &srcRect.w, &srcRect.h);

    destRect = srcRect;

    angle = 0;

    centre = {destRect.x / 2, destRect.y / 2};

    flip = SDL_FLIP_NONE;

    offsets = {Vector2D()};
}

Defender::Renderer::Renderer(const std::string &fontName,
                             SDL_Renderer *sdlRenderer,
                             const std::string &text) :
    Renderer(*FontRegistry::getFont(fontName), sdlRenderer, text) {}

Defender::Renderer::Renderer(Renderer&& other)
{
    sdlRenderer = other.sdlRenderer;
    other.sdlRenderer = nullptr;

    sdlTexture = other.sdlTexture;
    other.sdlTexture = nullptr;

    srcRect = std::move(other.srcRect);
    destRect = std::move(other.destRect);
    angle = std::move(other.angle);
    centre = std::move(other.centre);
    flip = std::move(other.flip);

    offsets = std::move(other.offsets);

    destroyTexture = std::move(other.destroyTexture);
}

Defender::Renderer& Defender::Renderer::operator = (Renderer&& other)
{
    sdlRenderer = other.sdlRenderer;
    other.sdlRenderer = nullptr;

    sdlTexture = other.sdlTexture;
    other.sdlTexture = nullptr;

    srcRect = std::move(other.srcRect);
    destRect = std::move(other.destRect);
    angle = std::move(other.angle);
    centre = std::move(other.centre);
    flip = std::move(other.flip);

    offsets = std::move(other.offsets);

    destroyTexture = std::move(other.destroyTexture);

    return *this;
}

Defender::Renderer& Defender::Renderer::commit()
{
    for (Vector2D v : offsets)
    {
        SDL_Rect finalDestRect = destRect;
        finalDestRect.x += v.x();
        finalDestRect.y += v.y();
        SDL_RenderCopyEx(sdlRenderer, sdlTexture, &srcRect, &finalDestRect,
                         angle, &centre, flip);
    }
    return *this;
}

Defender::Renderer::~Renderer()
{
    if (destroyTexture)
    {
        SDL_DestroyTexture(sdlTexture);
    }
}

Defender::Renderer& Defender::Renderer::operator () ()
{
    return commit();
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

Defender::Renderer& Defender::Renderer::addOffset(const Vector2D &offset)
{
    offsets.push_back(offset);
    return *this;
}

Defender::Renderer& Defender::Renderer::addOffset(const int x, const int y)
{
    return addOffset(Vector2D(x, y));
}

Defender::Texture Defender::Renderer::getTexture()
{
    destroyTexture = false;
    return Texture(sdlRenderer, sdlTexture);
}
