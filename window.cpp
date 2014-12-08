#include "window.h"

#include <stdexcept>
#include <iostream>

Defender::Window::Window()
{
    sdlWindow = SDL_CreateWindow("Defender",
                                 SDL_WINDOWPOS_UNDEFINED,
                                 SDL_WINDOWPOS_UNDEFINED,
                                 512, 512, SDL_WINDOW_SHOWN);
    if (sdlWindow == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }

    sdlRenderer = SDL_CreateRenderer(sdlWindow, -1,
                                     SDL_RENDERER_ACCELERATED |
                                     SDL_RENDERER_PRESENTVSYNC |
                                     SDL_RENDERER_TARGETTEXTURE);
    if (sdlRenderer == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

Defender::Window::~Window()
{
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(sdlWindow);
}

Defender::Window::Window(Defender::Window&& other)
{
    sdlWindow = other.sdlWindow;
    other.sdlWindow = nullptr;

    sdlRenderer = other.sdlRenderer;
    other.sdlRenderer = nullptr;
}

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
