#include "renderer.h"

#include "textureregistry.h"
#include "fontregistry.h"

Defender::Renderer::Renderer(Defender::Texture &texture)
{
    // Extract values from the texture
    sdlRenderer = texture.sdlRenderer;
    sdlTexture = texture.sdlTexture;

    srcRect = texture.sdlRect;
    destRect = texture.sdlRect;

    // Set the defaults
    angle = 0;
    centre = {destRect.x / 2, destRect.y / 2};
    flip = SDL_FLIP_NONE;

    offsets = {Vector2D()};
}

// If given a string, it should use this with the texture registry
Defender::Renderer::Renderer(const std::string &textureName) :
    Renderer(*TextureRegistry::getTexture(textureName)) {}

Defender::Renderer::Renderer(TTFFont &font, SDL_Renderer *newSdlRenderer,
                             const std::string &text)
{
    sdlRenderer = newSdlRenderer;

    // Render the text
    SDL_Surface* tempsurface = TTF_RenderUTF8_Blended(font.sdlFont,
                                                      text.c_str(),
                                                      {255, 255, 255, 255});

    // Convert the rendered surface into a texure
    sdlTexture = SDL_CreateTextureFromSurface(sdlRenderer, tempsurface);
    // Set the responsibility to destroy the texture
    destroyTexture = true;

    // Destroy the surface
    SDL_FreeSurface(tempsurface);
    tempsurface = nullptr;

    // Set the size of the source rectangle
    srcRect = {0, 0, 0, 0};
    SDL_QueryTexture(sdlTexture, nullptr, nullptr, &srcRect.w, &srcRect.h);

    // Set the defaults
    destRect = srcRect;
    angle = 0;
    centre = {destRect.x / 2, destRect.y / 2};
    flip = SDL_FLIP_NONE;

    offsets = {Vector2D()};
}

// If a string is passed rather that a font, it should retrive the font from the
// font registry
Defender::Renderer::Renderer(const std::string &fontName,
                             SDL_Renderer *sdlRenderer,
                             const std::string &text) :
    Renderer(*FontRegistry::getFont(fontName), sdlRenderer, text) {}

// Move constructor
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

// Move assignment
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

// This renders the image
Defender::Renderer& Defender::Renderer::commit()
{
    for (Vector2D v : offsets)
    {
        // For all of the offsets it should create a new SDL_Rect with the value
        // of the displacement added on
        SDL_Rect finalDestRect = destRect;
        finalDestRect.x += v.x();
        finalDestRect.y += v.y();
        // Use sdl to render
        SDL_RenderCopyEx(sdlRenderer, sdlTexture, &srcRect, &finalDestRect,
                         angle, &centre, flip);
    }
    return *this;
}

Defender::Renderer::~Renderer()
{
    // If it is the renderer's responsibility to destroy the rendered text
    // texture, it destroys it
    if (destroyTexture)
    {
        SDL_DestroyTexture(sdlTexture);
    }
}

Defender::Renderer& Defender::Renderer::operator () ()
{
    // commit() proxy
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
    // Add the offset to the vector of offsets
    offsets.push_back(offset);
    return *this;
}

Defender::Renderer& Defender::Renderer::addOffset(const int x, const int y)
{
    // Add the offset based on two integers
    return addOffset(Vector2D(x, y));
}

Defender::Texture Defender::Renderer::getTexture()
{
    // Since the texture is being passed out, it is no longer the renderers
    // responsibility to destroy it
    destroyTexture = false;
    return Texture(sdlRenderer, sdlTexture);
}
