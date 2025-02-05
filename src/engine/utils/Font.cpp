#include "Font.h"

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

#include <stdexcept>

FT_Library Font::ft;
unsigned int Font::vao;
unsigned int Font::vbo;

void Font::initFreeType() {
    if (FT_Init_FreeType(&ft))
    {
        throw std::runtime_error("initFreeType: Could not init FreeType Library");
    }

    // initialize vao
    glGenBuffers(1, &vbo);
    glGenVertexArrays(1, &vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(vao);
    // 6 vertices with 4 elements each
    glBufferData(GL_ARRAY_BUFFER, 6 * 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*) 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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
            static_cast<unsigned int>(face->glyph->advance.x),
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
        };
        characters.insert(std::pair<char, Character>(c, character));
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 4); 
}

#include <iostream>

void Font::renderText(const Shader& shader, const std::string& text, float x, float y, float scale) const {
    shader.use();
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f);
    shader.setMatrix4("projection", projection);
    shader.setVec3("textColor", 0.9f, 0.9f, 0.9f);

    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(vao);
    
    for (auto c : text) {
        auto f = characters.find(c);
        if (f == characters.end()) {
            throw std::runtime_error("Font::renderText: Unsupported character in string");
        }
        Character glyph = f->second;

        float xPos = x + glyph.bearing.x * scale;
        float yPos = y + (characters.find('H')->second.bearing.y - glyph.bearing.y) * scale;

        float w = glyph.size.x * scale;
        float h = glyph.size.y * scale;

        float vertices[24] = {
            xPos, yPos + h, 0.0f, 1.0f,
            xPos, yPos, 0.0f, 0.0f,
            xPos + w, yPos, 1.0f, 0.0f,

            xPos, yPos + h, 0.0f, 1.0f,
            xPos + w, yPos, 1.0f, 0.0f,
            xPos + w, yPos + h, 1.0f, 1.0f
        };

        glBindTexture(GL_TEXTURE_2D, glyph.textureID);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);

        x += (glyph.advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}