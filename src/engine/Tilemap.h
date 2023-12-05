#pragma once

#include "utils/Shader.h"
#include "utils/Framebuffer.h"
#include "utils/Math.h"

#include <memory>

struct Tile {
    int spriteId; // -1 for empty
    bool wall;
};

#define CHUNK_SIZE 16
#define CHUNK_BUFFER_SIZE 512
#define TILE_SIZE (2.0f / CHUNK_SIZE)

struct Chunk {
    bool isDirty;
    Framebuffer fb;
};

class Scene; // forward declare

class Tilemap {
private:
    int width, height;
    int nChunksWidth, nChunksHeight;
    float scale;
    float worldWidth, worldHeight;
    std::unique_ptr<Tile[]> tiles;
    std::unique_ptr<Chunk[]> chunks;
    
    std::vector<Polygon> walls;
    
    std::weak_ptr<Scene> scene;
public:
    Tilemap(int width, int height, float scale);

    std::shared_ptr<Scene> getScene() const;
    void setScene(std::shared_ptr<Scene> scene);

    float getScale() const;

    void recomputeWallPolygons();
    std::vector<Polygon> const& getWallPolygons() const;

    void setTile(int row, int col, Tile const& tile);
    void setTileFromWorldPosition(float x, float y, Tile const& tile);

    void render(Shader const& shader) const;
};