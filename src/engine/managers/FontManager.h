#pragma once

#include "../utils/Font.h"

#include <unordered_map>
#include <memory>

class FontManager {
private:
    std::unordered_map<std::string, Font> fonts;
public:
    FontManager();

    void registerFont(std::string const& name, std::string const& path);
    const Font* getFont(std::string const& name) const;
};