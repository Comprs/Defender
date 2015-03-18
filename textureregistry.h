#ifndef TEXTUREREGISTRY_H
#define TEXTUREREGISTRY_H

#include <string>
#include <unordered_map>
#include <memory>
#include "texture.h"

namespace Defender
{
class TextureRegistry
{
public:
    TextureRegistry() = delete;
    static void attachRenderer(SDL_Renderer* newSdlRenderer);
    static void addTexture(const std::string& textureName);
    static std::shared_ptr<Texture>
    getTexture(const std::string& textureName);

private:
    static std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
    static SDL_Renderer* sdlRenderer;
};
}

#endif // TEXTUREREGISTRY_H
