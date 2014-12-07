#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

namespace Defender
{
struct Window
{
public:
    Window();
    ~Window();

    Window(const Defender::Window& other) = delete;
    Defender::Window& operator = (const Defender::Window& other) = delete;

    Window(Defender::Window&& other);
    Defender::Window& operator = (Defender::Window&& other);

    SDL_Window* sdlWindow = nullptr;
    SDL_Renderer* sdlRenderer = nullptr;
};
}

#endif // WINDOW_H
