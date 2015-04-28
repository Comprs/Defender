#include "audioregistry.h"

std::unordered_map<std::string, std::shared_ptr<Defender::Audio>>
Defender::AudioRegistry::audio;

void Defender::AudioRegistry::addAudio(const std::string& audioName)
{
    audio[audioName] = std::make_shared<Audio>(audioName);
}

void Defender::AudioRegistry::play(const std::string& audioName)
{
    // If the audio resource dosen't exist
    if (audio.count(audioName) == 0)
    {
        // try to load it in
        addAudio(audioName);
    }
    // Play the audio
    Mix_PlayChannel(-1, audio.at(audioName)->mixChunk, 0);
}

void Defender::AudioRegistry::unload()
{
    audio.erase(audio.begin(), audio.end());
}
