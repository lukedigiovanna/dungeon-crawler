#ifndef H_MESH
#define H_MESH

class Mesh {
private:
    unsigned int vbo, vao, numIndices, numTriangles;
    unsigned int ebo;
    bool useEbo = false;
public:
    Mesh(float* vertexData, unsigned int* indices, unsigned int numVertices, unsigned int numTriangles);
    Mesh(float* vertexData, unsigned int numTriangles);
    ~Mesh();

    void render() const;
};

#endif