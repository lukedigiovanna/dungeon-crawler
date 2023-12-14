#pragma once

#include "utils/Shader.h"
#include "utils/Framebuffer.h"
#include "utils/Math.h"

#include <memory>

class Tile {
private:
    math::Polygon wallPolygon;
public:
    int spriteId; // -1 for empty
    bool wall;
    Tile(int spriteId, bool wall, float x, float y, float size);
    Tile(float x, float y, float size);
    Tile();

    math::Polygon const& getWallPolygon() const;
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
    
    std::vector<math::Polygon> walls;
    
    std::weak_ptr<Scene> scene;
public:
    Tilemap(int width, int height, float scale);

    std::shared_ptr<Scene> getScene() const;
    void setScene(std::shared_ptr<Scene> scene);

    float getScale() const;

    void recomputeWallPolygons();
    std::vector<math::Polygon> const& getWallPolygons() const;

    void setTile(int row, int col, int spriteId, bool wall);
    void setTileFromWorldPosition(float x, float y, int spriteId, bool wall);

    Tile const& getTile(int row, int col) const;
    Tile const& getTileFromWorldPosition(float x, float y) const; 

    void render(Shader const& shader) const;
};