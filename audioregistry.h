#ifndef AUDIOREGISTRY
#define AUDIOREGISTRY

#include <string>
#include <memory>
#include <unordered_map>
#include "audio.h"

namespace Defender
{
class AudioRegistry
{
public:
    AudioRegistry() = delete;
    static void addAudio(const std::string& audioName);
    static void play(const std::string& audioName);

private:
    static std::unordered_map<std::string, std::shared_ptr<Audio>> audio;
};
}

#endif // AUDIOREGISTRY

