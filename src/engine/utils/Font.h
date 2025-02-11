#pragma once

#include "Shader.h"
#include "Graphics.h"

#include <ft2build.h>
#include FT_FREETYPE_H   

#include <glm/glm.hpp>

#include <string>
#include <map>

enum TextAlignment {
    JUSTIFY_LEFT,
    JUSTIFY_CENTER,
    JUSTIFY_RIGHT,
};

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

    float textWidth(const std::string& text, float scale) const;
    void renderText(
        const Shader& shader, 
        const std::string& text, 
        const gfx::color& color, 
        TextAlignment alignment, 
        float x, float y, 
        float scale) const;
};