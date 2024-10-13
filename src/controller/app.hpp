#pragma once

#include "../config.hpp"
#include "../components/camera_component.hpp"
#include "../components/physics_component.hpp"
#include "../components/render_component.hpp"
#include "../components/transform_component.hpp"
#include "../components/animation_component.hpp"
#include "../components/component_set.hpp"
#include "../systems/camera_system.hpp"
#include "../systems/motion_system.hpp"
#include "../systems/render_system.hpp"
#include "../systems/animation_system.hpp"
#include "../view/shader.hpp"


class App 
{

public:
    App();
    ~App();
    void run();
    void set_up_opengl();
    void make_systems();

    //Components
    ComponentSet<AnimationComponent> animationComponents;
    ComponentSet<TransformComponent> transformComponents;
    ComponentSet<PhysicsComponent> physicsComponents;
    ComponentSet<CameraComponent> cameraComponents;
    ComponentSet<RenderComponent> renderComponents;
    

private:
    void set_up_glfw();
    void handle_frame_timing();

    GLFWwindow* window;

    //unsigned int shader;
    std::vector<unsigned int> shaders;

    //Systems
    MotionSystem* motionSystem;
    CameraSystem* cameraSystem;
    RenderSystem* renderSystem;
    AnimationSystem* animationSystem;

    //Timing
    double lastTime, currentTime;
	int numFrames;
	float frameTime;
};