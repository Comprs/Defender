#ifndef ROOM_H
#define ROOM_H

#include <string>
#include "entity.h"
#include "textureregistry.h"

namespace Defender
{
class Entity;
class Room
{
public:
    virtual void update(const double time);
    virtual void draw();

    template<typename T, typename... Args>
    void addEntity(const std::string& textureName, Args... args)
    {
        entities.push_back(std::make_shared<T>
                           (&entities, this,
                            TextureRegistry::getTexture(textureName),
                            args...));
    }

protected:
    std::vector<std::shared_ptr<Entity>> entities;
};
}

#endif // ROOM_H
