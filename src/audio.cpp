#include "audio.hpp"

#include <stdexcept>

Defender::Audio::Audio(const std::string &filename)
{
    this->mixChunk = Mix_LoadWAV(filename.c_str());

    if (mixChunk == nullptr)
    {
        throw std::runtime_error(SDL_GetError());
    }
}

Defender::Audio::Audio(Audio&& other)
{
    mixChunk = other.mixChunk;
    other.mixChunk = nullptr;
}

Defender::Audio& Defender::Audio::operator = (Audio&& other)
{
    mixChunk = other.mixChunk;
    other.mixChunk = nullptr;
    return *this;
}

Defender::Audio::~Audio()
{
    Mix_FreeChunk(mixChunk);
}
