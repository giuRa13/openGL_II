#include "triangle_mesh.hpp"


TriangleMesh::TriangleMesh() {
    /*std::vector<float> positions = {
        -1.0f, -1.0f,  0.0f, 
         1.0f, -1.0f,  0.0f, 
        -1.0f,  1.0f,  0.0f,

        -1.0,   1.0f,  0.0f,
         1.0f, -1.0f,  0.0f,
         1.0f,  1.0f,  0.0f,      
    };*/
    std::vector<float> positions = {
        -1.0f, -1.0f,  0.0f, 
         1.0f, -1.0f,  0.0f, 
        -1.0f,  1.0f,  0.0f,
         1.0f,  1.0f,  0.0f,      
    };

    std::vector<int> colorIndices = {
        0, 1, 2, 3
    };
    
    std::vector<int> elementIndices = { //vertex index
        0, 1, 2, 2, 1, 3 
    };
    
    vertex_count = 6;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    VBOs.resize(2);

    glGenBuffers(2, VBOs.data());

    //position
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, (void*)0); //12 --> bytes, 3 float = 12 bytes
    glEnableVertexAttribArray(0);

    //color
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, colorIndices.size() * sizeof(float), colorIndices.data(), GL_STATIC_DRAW);
    glVertexAttribIPointer(1, 1, GL_INT, 4, (void*)0); //4 --> bytes ,1 int = 4 bytes
    glEnableVertexAttribArray(1);

    //element buffer
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementIndices.size() * sizeof(int), elementIndices.data(), GL_STATIC_DRAW);
}

void TriangleMesh::draw() {
    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, vertex_count); //or EBO
    glDrawElements(GL_TRIANGLES, vertex_count, GL_UNSIGNED_INT, 0); //mode, count, type, indices
}

TriangleMesh::~TriangleMesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBOs.data());
    glDeleteBuffers(1, &EBO);
}