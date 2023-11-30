#include "Mesh.h"
#include <glad/glad.h>

// Layout of each vertex is always
// [x][y] | [tx][ty]

#define NUM_ELEMENTS_PER_VERTEX 4

Mesh::Mesh(float* vertexData, unsigned int* indices, unsigned int numVertices, unsigned int numTriangles) {
    if (indices != nullptr) {
        this->useEbo = true;
    }
    this->numIndices = numTriangles * 3;
    this->numTriangles = numTriangles;

    glGenVertexArrays(1, &this->vao);
    glGenBuffers(1, &this->vbo);
    if (this->useEbo)
        glGenBuffers(1, &this->ebo);

    glBindVertexArray(this->vao);

    // set up vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * NUM_ELEMENTS_PER_VERTEX * numVertices, vertexData, GL_STATIC_DRAW);

    // set up index buffer, if we are using that
    if (this->useEbo) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * this->numIndices, indices, GL_STATIC_DRAW);
    }

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, NUM_ELEMENTS_PER_VERTEX * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, NUM_ELEMENTS_PER_VERTEX * sizeof(float), (void*) (2 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Mesh::Mesh(float* vertexData, unsigned int numTriangles) : Mesh(vertexData, nullptr, numTriangles * 3, numTriangles) {}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &this->vao);
    glDeleteBuffers(1, &this->vbo);
    if (this->useEbo)
        glDeleteBuffers(1, &this->ebo);
}

void Mesh::render() const {
    GLint textureBinding;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &textureBinding);
    if (textureBinding == 0) {
        // bind the blank texture then
        // textures::BLANK.bind();
    }
    // bind the vao
    glBindVertexArray(this->vao);
    // draw
    if (this->useEbo) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ebo);
        glDrawElements(GL_TRIANGLES, this->numIndices, GL_UNSIGNED_INT, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
    else {
        glDrawArrays(GL_TRIANGLES, 0, this->numIndices);
    }
    // unbind the vao
    glBindVertexArray(0);
}