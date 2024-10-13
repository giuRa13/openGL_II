#pragma once

#include "../config.hpp"
#include "../components/transform_component.hpp"
#include "../components/render_component.hpp"
#include "../components/animation_component.hpp"
#include "../components/component_set.hpp"


class RenderSystem {
public:

    RenderSystem(std::vector<unsigned int>& shaders, GLFWwindow* window, 
        ComponentSet<TransformComponent> &transforms,
        ComponentSet<RenderComponent> &renderables,
        ComponentSet<AnimationComponent> &animations);

    ~RenderSystem();
    
    void update();

    
private:
    void build_sky();
    void build_models();
    void build_geometry();

    std::vector<unsigned int>& shaders;

    std::vector<unsigned int> VAOs;
    std::vector<unsigned int> VBOs;
    std::vector<unsigned int> EBOs;
    
    std::unordered_map<ObjectType, unsigned int> elementCounts;
    std::unordered_map<ObjectType, std::unordered_map<AnimationType, unsigned int>> offsets;

    std::vector<unsigned int> textures;
    unsigned int skyTexture;

    unsigned int modelLocation;
    
    GLFWwindow* window;

    ComponentSet<TransformComponent> &transforms;
    ComponentSet<RenderComponent> &renderables;
    ComponentSet<AnimationComponent> &animations;
};