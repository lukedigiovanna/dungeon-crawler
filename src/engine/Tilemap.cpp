#include "Tilemap.h"

#include "utils/meshes.h"
#include "Scene.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Tilemap::Tilemap(int width, int height, float scale) : scale(scale) {
    this->width = width;
    this->height = height;
    nChunksWidth = width / CHUNK_SIZE;
    nChunksHeight = height / CHUNK_SIZE;
    if (width % CHUNK_SIZE != 0) nChunksWidth++;
    if (height % CHUNK_SIZE != 0) nChunksHeight++;
    tiles = std::make_unique<Tile[]>(width * height);
    chunks = std::make_unique<Chunk[]>(nChunksWidth * nChunksHeight);
}

std::shared_ptr<Scene> Tilemap::getScene() const {
    std::shared_ptr<Scene> s = scene.lock();
    if (s == nullptr) {
        throw std::runtime_error("Tilemap::getScene: Cannot get the scene of a tilemap which is not attached to a scene");
    }
    return s;
}

void Tilemap::setScene(std::shared_ptr<Scene> scene) {
    this->scene = scene;
}   

void Tilemap::setTile(int row, int col, int spriteId, bool isWall) {
    if (row < 0 || row >= height || col < 0 || col >= width) {
        throw std::runtime_error("Tilemap::setTile: Coordinates out of bounds: row, col = " + std::to_string(row) + ", " + std::to_string(col));
    }
    int i = row * width + col;
    int cr = row / CHUNK_SIZE, cc = col / CHUNK_SIZE;
    int ci = cr * nChunksWidth + cc;
    if (spriteId != tiles[i].spriteId || isWall != tiles[i].wall) {
        tiles[i] = {
            spriteId, isWall
        };
        chunks[ci].isDirty = true;
    }
}

void Tilemap::render(Shader const& shader) const {
    float ww = static_cast<float>(width) * scale;
    float wh = static_cast<float>(height) * scale;
    std::shared_ptr<SpriteManager> sm = getScene()->getManagers()->spriteManager;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int ind = i * width + j;
            if (tiles[ind].spriteId < 0) {
                continue;
            }  
            float y = static_cast<float>(i) / height * wh - wh / 2.0f;
            float x = static_cast<float>(j) / width * ww - ww / 2.0f;
            glm::mat4 trans(1.0f);
            trans = glm::translate(trans, glm::vec3(x, y, 0.0f));
            trans = glm::scale(trans, glm::vec3(scale, scale, 1.0f));
            shader.setMatrix4("model", trans);
            const Sprite* sprite = sm->getSpriteByIndex(tiles[ind].spriteId);
            sprite->texture->bind();
            shader.setVec4("clipRect", sprite->clip);
            meshes::SQUARE->render();
        }
    }
}