#include "Font.h"

#include <glad/glad.h>

#include <stdexcept>

FT_Library Font::ft;

void Font::initFreeType() {
    if (FT_Init_FreeType(&ft))
    {
        throw std::runtime_error("initFreeType: Could not init FreeType Library");
    }
}

Font::Font(const std::string& filepath) {
    FT_Face face;
    if (FT_New_Face(ft, filepath.c_str(), 0, &face)) {
        throw std::runtime_error("Font::Font: Could not init given font: " + filepath);
    }

    FT_Set_Pixel_Sizes(face, 0, 48);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1); 
    // supported chars are from the space key to space + 128
    for (char c = ' '; c < 127; c++) {
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            throw std::runtime_error("Font::Font: Could not load a character");
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture, 
            face->glyph->advance.x,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        };
        characters.insert(std::pair<char, Character>(c, character));
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 
}