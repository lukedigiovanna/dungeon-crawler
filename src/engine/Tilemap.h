#pragma once

#include "utils/Shader.h"

#include <memory>

struct Tile {
    int spriteId; // -1 for empty
    bool wall;
};

#define CHUNK_SIZE 64

struct Chunk {
    bool isDirty;
};

class Scene; // forward declare

class Tilemap {
private:
    int width, height;
    int nChunksWidth, nChunksHeight;
    float scale;
    std::unique_ptr<Tile[]> tiles;
    std::unique_ptr<Chunk[]> chunks;
    std::weak_ptr<Scene> scene;
public:
    Tilemap(int width, int height, float scale);

    std::shared_ptr<Scene> getScene() const;
    void setScene(std::shared_ptr<Scene> scene);

    void setTile(int row, int col, int spriteId, bool isWall);

    void render(Shader const& shader) const;
};