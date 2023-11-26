#ifndef H_TEXTURE
#define H_TEXTURE

#include <string>

class Texture {
private:
    int width, height, nrChannels;
    unsigned int texture;
public:
    /* DANGEROUS */
    Texture(); // default constructor leaves everything uninitialized

    Texture(std::string const& imagePath);
    ~Texture();

    void bind() const;
    void unbind() const;
};

#endif