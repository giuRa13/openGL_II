#include "config.hpp"

class TriangleMesh 
{
public:
    TriangleMesh();
    void draw();
    ~TriangleMesh();

private:
    //EBO --> VBO without duplicate
    unsigned int EBO, VAO, vertex_count;
    std::vector<unsigned int> VBOs;
};