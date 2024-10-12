#pragma once

#include "../config.hpp"
#include "../components/camera_component.hpp"
#include "../components/physics_component.hpp"
#include "../components/render_component.hpp"
#include "../components/transform_component.hpp"
#include "../components/animation_component.hpp"


class Factory 
{

public:
    Factory(
        std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents,
        std::unordered_map<unsigned int, RenderComponent>& renderComponents,
        std::unordered_map<unsigned int, TransformComponent>& transformComponents,
        std::unordered_map<unsigned int, AnimationComponent>& animationComponents);
    
    ~Factory();

    unsigned int make_camera(glm::vec3 position, glm::vec3 eulers);

    void make_cube(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity);

    void make_girl(glm::vec3 position, glm::vec3 eulers);

    void make_revy(glm::vec3 position, glm::vec3 eulers);


private:

    unsigned int entities_made = 0;

    std::unordered_map<unsigned int, PhysicsComponent>& physicsComponents;
    std::unordered_map<unsigned int, RenderComponent>& renderComponents;
    std::unordered_map<unsigned int, TransformComponent>& transformComponents;
    std::unordered_map<unsigned int, AnimationComponent>& animationComponents;

};