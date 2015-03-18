#include "window.h"

#include <stdexcept>
#include "globals.h"

Defender::Window::Window()
{
    // Create the window based on constant values
    sdlWindow = SDL_CreateWindow("Defender",
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED,
                                 windowWidth, windowHeight,
                                 SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    if (sdlWindow == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }

    // Create the renderer from the window
    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1,
                                     SDL_RENDERER_ACCELERATED |
                                     SDL_RENDERER_TARGETTEXTURE);
    if (sdlRenderer == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(sdlRenderer, windowWidth, windowHeight);
}

Defender::Window::~Window()
{
    // Destroy the renderer and window
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
}

// Move constructor
Defender::Window::Window(Defender::Window&& other)
{
    sdlWindow = other.sdlWindow;
    other.sdlWindow = nullptr;

    sdlRenderer = other.sdlRenderer;
    other.sdlRenderer = nullptr;
}

// Move assignment
Defender::Window& Defender::Window::operator = (Defender::Window&& other)
{
    sdlWindow = other.sdlWindow;
    other.sdlWindow = nullptr;

    sdlRenderer = other.sdlRenderer;
    other.sdlRenderer = nullptr;

    return *this;
}

void Defender::Window::close()
{
    open = false;
}

bool Defender::Window::isOpen()
{
    return open;
}

// Event loop to handle events from the operating system
void Defender::Window::eventLoop()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        switch(e.type)
        {
        case (SDL_QUIT):
            close();
        }
    }
}
