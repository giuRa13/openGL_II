#pragma once

#include "../config.hpp"
#include "../components/animation_component.hpp"
#include "../components/component_set.hpp"

class AnimationSystem
{

public:

    AnimationSystem(ComponentSet<AnimationComponent>& animations);

    void update(float frameTime);


private:
    ComponentSet<AnimationComponent>& animations;

};