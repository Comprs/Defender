#include "fontregistry.h"

std::unordered_map<std::string, std::shared_ptr<Defender::TTFFont>>
Defender::FontRegistry::fonts;

void Defender::FontRegistry::addFont(const std::string& fontName,
                                     const int ptSize)
{
    // Add the font by creating a TTFFont and add it to the registry
    fonts[fontName] = std::make_shared<TTFFont>(fontName, ptSize);
}

std::shared_ptr<Defender::TTFFont>
Defender::FontRegistry::getFont(const std::string& fontName)
{
    // If the font doesn't exist, add it
    if (fonts.count(fontName) == 0)
    {
        addFont(fontName, 10);
    }
    // Return the named font
    return fonts.at(fontName);
}

void Defender::FontRegistry::unload()
{
    fonts.erase(fonts.begin(), fonts.end());
}
