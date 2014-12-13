#include "fontregistry.h"

std::unordered_map<std::string, std::shared_ptr<Defender::TTFFont>>
Defender::FontRegistry::fonts;

void Defender::FontRegistry::addFont(const std::string &fontName,
                                     const int ptSize)
{
    fonts[fontName] = std::make_shared<TTFFont>(fontName, ptSize);
}

std::shared_ptr<Defender::TTFFont>
Defender::FontRegistry::getFont(const std::string &fontName)
{
    if (fonts.count(fontName) == 0)
    {
        addFont(fontName, 10);
    }
    return fonts.at(fontName);
}
