#include "ttffont.h"

#include <stdexcept>

Defender::TTFFont::TTFFont(const std::string& fontName, int ptSize)
{
    sdlFont = TTF_OpenFont(fontName.c_str(), ptSize);
    if (sdlFont == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

Defender::TTFFont::TTFFont(TTFFont&& other)
{
    sdlFont = other.sdlFont;
    other.sdlFont = nullptr;
}

Defender::TTFFont& Defender::TTFFont::operator = (TTFFont&& other)
{
    sdlFont = other.sdlFont;
    other.sdlFont = nullptr;

    return *this;
}

Defender::TTFFont::~TTFFont()
{
    TTF_CloseFont(sdlFont);
    sdlFont = nullptr;
}
