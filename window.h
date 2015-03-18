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

    Window(const Window& other) = delete;
    Window& operator = (const Window& other) = delete;

    Window(Window&& other);
    Window& operator = (Window&& other);

    void close();
    bool isOpen();

    void eventLoop();

    SDL_Window* sdlWindow = nullptr;
    SDL_Renderer* sdlRenderer = nullptr;

private:
    bool open = true;
};
}

#endif // WINDOW_H
