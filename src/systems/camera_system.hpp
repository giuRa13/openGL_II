#pragma once


#include "../config.hpp"
#include "../components/camera_component.hpp"
#include "../components/transform_component.hpp"
#include "../components/component_set.hpp"


class CameraSystem 
{

public:
    CameraSystem(
        std::vector<unsigned int>& shaders, 
        GLFWwindow* window, 
        ComponentSet<TransformComponent>& transforms, 
        ComponentSet<CameraComponent>& cameras);
    
    bool update(float dt);


private:
    std::vector<unsigned int>& shaders;

    unsigned int forwardsLocation;
    unsigned int rightLocation;
    unsigned int upLocation;

    std::vector<unsigned int> viewLocation;
    std::vector<unsigned int> posLocation;
    
    const glm::vec3 global_up = {0.0f, 0.0f, 1.0f};
    
    GLFWwindow* window;
    
    float dx, dy; //correction factor for screen AspectRatio

    ComponentSet<TransformComponent>& transforms;
    ComponentSet<CameraComponent>& cameras;

};