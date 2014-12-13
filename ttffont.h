#ifndef TTFFONT_H
#define TTFFONT_H

#include <string>
#include <SDL2/SDL_ttf.h>
#include "renderer.h"

namespace Defender
{
class Renderer;
class TTFFont
{
    friend class Renderer;
public:
    TTFFont(const std::string& fontName, int ptSize);

    TTFFont(const TTFFont& other) = delete;
    TTFFont& operator = (const TTFFont& other) = delete;

    TTFFont(TTFFont&& other);
    TTFFont& operator = (TTFFont&& other);

    ~TTFFont();

private:
    TTF_Font* sdlFont = nullptr;
};
}

#endif // TTFFONT_H
