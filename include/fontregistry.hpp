#ifndef FONTREGISTRY_H
#define FONTREGISTRY_H

#include <string>
#include <unordered_map>
#include <memory>
#include "ttffont.hpp"

namespace Defender
{
class FontRegistry
{
public:
    FontRegistry() = delete;
    static void addFont(const std::string& fontName, const int ptSize);
    static std::shared_ptr<TTFFont> getFont(const std::string& fontName);
    static void unload();

private:
    static std::unordered_map<std::string, std::shared_ptr<TTFFont>> fonts;
};
}

#endif // FONTREGISTRY_H
