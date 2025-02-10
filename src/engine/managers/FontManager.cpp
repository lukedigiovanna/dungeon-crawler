#include "FontManager.h"

#include <stdexcept>

FontManager::FontManager() {

}

void FontManager::registerFont(std::string const& name, std::string const& path) {
    if (fonts.find(name) != fonts.end()) {
        throw std::runtime_error("FontManager::registerFont: font name " + name + " is already in use");
    }
    fonts.emplace(name, path);
}

const Font* FontManager::getFont(std::string const& name) const {
    auto f = fonts.find(name);
    if (f == fonts.end()) {
        throw std::runtime_error("FontManager::getFont: no font with name " + name);
    }
    return &f->second;
}