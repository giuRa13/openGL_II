#pragma once

#include "../config.hpp"
#include "../components/animation_component.hpp"


class AnimationSystem
{

public:

    void update(
        std::unordered_map<unsigned int, AnimationComponent>& AnimationComponents, 
        float frameTime
    );

};