#include "ttffont.h"

#include <stdexcept>

Defender::TTFFont::TTFFont(const std::string& fontName, int ptSize)
{
    // Load in the font
    sdlFont = TTF_OpenFont(fontName.c_str(), ptSize);
    if (sdlFont == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

// Move constructor
Defender::TTFFont::TTFFont(TTFFont&& other)
{
    sdlFont = other.sdlFont;
    other.sdlFont = nullptr;
}

// Move assignment
Defender::TTFFont& Defender::TTFFont::operator = (TTFFont&& other)
{
    sdlFont = other.sdlFont;
    other.sdlFont = nullptr;

    return *this;
}

Defender::TTFFont::~TTFFont()
{
    // Destroy the font
    TTF_CloseFont(sdlFont);
    sdlFont = nullptr;
}
