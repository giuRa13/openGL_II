#pragma once

#include "../config.hpp"
#include "../components/transform_component.hpp"
#include "../components/render_component.hpp"
#include "../components/animation_component.hpp"
#include "../factories/mesh_factory.hpp"


class RenderSystem {
public:

    RenderSystem(unsigned int shader, GLFWwindow* window);
    
    void update(
        std::unordered_map<unsigned int,TransformComponent> &transformComponents,
        std::unordered_map<unsigned int,RenderComponent> &renderComponents,
        std::unordered_map<unsigned int,AnimationComponent> &animationCmponents);

    
private:
    std::unordered_map<ObjectType, 
        std::unordered_map<AnimationType, std::vector<unsigned int>>> VAOs;
    
    std::unordered_map<ObjectType, 
        std::unordered_map<AnimationType, std::vector<unsigned int>>> VBOs;
    
    std::unordered_map<ObjectType, unsigned int> vertexCounts;
    std::unordered_map<ObjectType, unsigned int> textures;

    unsigned int modelLocation;
    GLFWwindow* window;
};