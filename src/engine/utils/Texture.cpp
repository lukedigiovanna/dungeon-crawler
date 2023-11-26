#include "Texture.h"
#include "../stb_image.h"
#include <glad/glad.h>
#include <iostream>

Texture::Texture(std::string const& imagePath) {
    unsigned char* data = stbi_load(imagePath.c_str(), &this->width, &this->height, &this->nrChannels, 0);
    if (!data) {
        std::cout << "Failed to load texture" << std::endl;
        return;
    }
    glGenTextures(1, &this->texture);
    std::cout << imagePath << ": " << &this->texture << " " << this->texture << std::endl;
    glBindTexture(GL_TEXTURE_2D, this->texture);
    
    // set parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load the texture data
    GLenum format = this->nrChannels == 3 ? GL_RGB : GL_RGBA;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, this->width, this->height, 0, format, GL_UNSIGNED_BYTE, data);
    
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    this->unbind();
}

Texture::Texture() {
    // leaves all data unitialized.
    // this constructor is useful for statically allocating
    // textures objects and then later reassigning their
    // memory to an allocated texture.
}

Texture::~Texture() {
    // glDeleteTextures(1, &this->texture);
}

void Texture::bind() const {
    glBindTexture(GL_TEXTURE_2D, this->texture);
}

void Texture::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}