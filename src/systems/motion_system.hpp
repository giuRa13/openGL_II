#pragma once

#include "../config.hpp"
#include "../components/transform_component.hpp"
#include "../components/physics_component.hpp"
#include "../components/component_set.hpp"


class MotionSystem 
{
    
public:
    MotionSystem(ComponentSet<TransformComponent> &transforms, 
        ComponentSet<PhysicsComponent> &velocities);

    void update(float dt);


private:
    ComponentSet<TransformComponent> &transforms;
    ComponentSet<PhysicsComponent> &velocities;

};