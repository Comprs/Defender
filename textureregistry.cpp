#include "textureregistry.h"

std::unordered_map<std::string, std::shared_ptr<Defender::Texture>>
Defender::TextureRegistry::textures;
SDL_Renderer* Defender::TextureRegistry::sdlRenderer = nullptr;

void Defender::TextureRegistry::attachRenderer(SDL_Renderer *newSdlRenderer)
{
    sdlRenderer = newSdlRenderer;
}

void Defender::TextureRegistry::addTexture(const std::string &textureName)
{
    textures[textureName] =
            std::make_shared<Defender::Texture>(sdlRenderer, textureName);
}

std::shared_ptr<Defender::Texture>
Defender::TextureRegistry::getTexture(const std::string &textureName)
{
    if (textures.count(textureName) == 0)
    {
        addTexture(textureName);
    }
    return textures.at(textureName);
}