#pragma once
#include "../config.hpp"
#include "../components/render_component.hpp"


struct StaticMesh 
{
    unsigned int VAO, VBO, vertexCount;
};


class MeshFactory {

public:
    void start_obj_mesh(); 

    void append_cube_mesh(glm::vec3 size);

    void append_obj_mesh(const char* filename, glm::mat4 preTransform);

    StaticMesh build_obj_mesh();
    

private:
    void reserve_space(const char* filename);
    void read_file(const char* filename);

    glm::vec3 read_vec3(std::vector<std::string> words, float w);
    glm::vec2 read_vec2(std::vector<std::string> words);
    void read_face(std::vector<std::string> words);
    void read_corner(std::string description);

    std::vector<glm::vec3> v;
    std::vector<glm::vec2> vt;
    std::vector<glm::vec3> vn;
    std::vector<float> vertices;

    size_t v_loaded, vt_loaded, vn_loaded;

    glm::mat4 preTransform;

};