#include "window.h"

#include <stdexcept>
#include "globals.h"

Defender::Window::Window()
{
    // Create the window based on constant values
    this->sdlWindow = SDL_CreateWindow("Defender",
                                       SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                       windowWidth, windowHeight,
                                       SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (this->sdlWindow == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }

    // Create the renderer from the window
    this->sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED |
                                           SDL_RENDERER_TARGETTEXTURE);
    if (this->sdlRenderer == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }

    // Set the scaling method
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    // Set the logical render size
    SDL_RenderSetLogicalSize(this->sdlRenderer, windowWidth, windowHeight);

    // Hide the cursor
    SDL_ShowCursor(SDL_FALSE);
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
    this->sdlWindow = other.sdlWindow;
    other.sdlWindow = nullptr;

    this->sdlRenderer = other.sdlRenderer;
    other.sdlRenderer = nullptr;
}

// Move assignment
Defender::Window& Defender::Window::operator = (Defender::Window&& other)
{
    this->sdlWindow = other.sdlWindow;
    other.sdlWindow = nullptr;

    this->sdlRenderer = other.sdlRenderer;
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
