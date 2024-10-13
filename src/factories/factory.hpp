#pragma once

#include "../config.hpp"
#include "../components/camera_component.hpp"
#include "../components/physics_component.hpp"
#include "../components/render_component.hpp"
#include "../components/transform_component.hpp"
#include "../components/animation_component.hpp"
#include "../components/component_set.hpp"


class Factory 
{

public:
    Factory(
        ComponentSet<PhysicsComponent>& physicsComponents,
        ComponentSet<RenderComponent>& renderComponents,
        ComponentSet<TransformComponent>& transformComponents,
        ComponentSet<AnimationComponent>& animationComponents,
        ComponentSet<CameraComponent>& cameraComponents);
    
    ~Factory();

    void make_camera(glm::vec3 position, glm::vec3 eulers);

    void make_cube(glm::vec3 position, glm::vec3 eulers, glm::vec3 eulerVelocity);

    void make_girl(glm::vec3 position, glm::vec3 eulers);

    void make_revy(glm::vec3 position, glm::vec3 eulers);


private:

    unsigned int entities_made = 0;

    ComponentSet<PhysicsComponent>& physicsComponents;
    ComponentSet<RenderComponent>& renderComponents;
    ComponentSet<TransformComponent>& transformComponents;
    ComponentSet<AnimationComponent>& animationComponents;
    ComponentSet<CameraComponent>& cameraComponents;

};