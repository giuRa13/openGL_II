#pragma once

#include "../config.hpp"
#include "../components/transform_component.hpp"
#include "../components/physics_component.hpp"

class MotionSystem {
    
public:
    
    void update(
        std::unordered_map<unsigned int,TransformComponent> &transformComponents,
        std::unordered_map<unsigned int,PhysicsComponent> &physicsComponents,
        float dt);


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