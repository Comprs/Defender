#include "audioregistry.h"

std::unordered_map<std::string, std::shared_ptr<Defender::Audio>>
Defender::AudioRegistry::audio;

void Defender::AudioRegistry::addAudio(const std::string& audioName)
{
    audio[audioName] = std::make_shared<Audio>(audioName);
}

void Defender::AudioRegistry::play(const std::string& audioName)
{
    if (audio.count(audioName) == 0)
    {
        addAudio(audioName);
    }
    Mix_PlayChannel(-1, audio.at(audioName)->mixChunk, 0);
}
