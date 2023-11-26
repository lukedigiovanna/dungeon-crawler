#include "meshes.h"

using namespace meshes;

static float v_square[] = {
    -0.5f, -0.5f,  0.0f, 0.0f,
     0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.0f, 1.0f
};

static unsigned int i_square[] = {
    0, 1, 2,
    0, 2, 3
};

Mesh* meshes::SQUARE;

void meshes::init() {
    SQUARE = new Mesh(v_square, i_square, 4, 2);
}

void meshes::destroy() {
    delete SQUARE;
}