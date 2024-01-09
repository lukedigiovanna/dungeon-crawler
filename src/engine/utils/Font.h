#pragma once

#include "Shader.h"

#include <ft2build.h>
#include FT_FREETYPE_H   

#include <glm/glm.hpp>

#include <string>
#include <map>

struct Character {
    unsigned int textureID;
    unsigned int advance;
    glm::ivec2 size;
    glm::ivec2 bearing;

};


class Font {
private:
    std::map<char, Character> characters;
public:
    static FT_Library ft;
    static unsigned int vao;
    static unsigned int vbo;
    static void initFreeType();

    Font(const std::string& filepath);

    void renderText(const Shader& shader, const std::string& text, float x, float y, float scale) const;
};