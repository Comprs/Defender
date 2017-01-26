#ifndef AUDIO_H
#define AUDIO_H

#include <string>
#include <SDL2/SDL_mixer.h>

namespace Defender
{
class AudioRegistry;
class Audio
{
    friend class AudioRegistry;
public:
    Audio(const std::string& filename);
    ~Audio();

    Audio(const Audio& other) = delete;
    Audio& operator = (const Audio& other) = delete;

    Audio(Audio&& other);
    Audio& operator = (Audio&& other);

private:
    Mix_Chunk* mixChunk = nullptr;
};
}

#endif // AUDIO_H

