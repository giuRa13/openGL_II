#include "config.hpp"
#include "controller/app.hpp"
#include "components/camera_component.hpp"
#include "components/physics_component.hpp"
#include "components/render_component.hpp"
#include "components/transform_component.hpp"
#include "factory.hpp"
//#include "triangle_mesh.hpp"
//#include "material.hpp"
//#include "linear_algebra.hpp"

void GetOpenGLVersionInfo()
{
    std::cout <<"Vendor: " <<glGetString(GL_VENDOR) <<std::endl;
    std::cout <<"Renderer: " <<glGetString(GL_RENDERER) <<std::endl;
    std::cout <<"Version: " <<glGetString(GL_VERSION) <<std::endl;
    std::cout <<"Shadong Language: " <<glGetString(GL_SHADING_LANGUAGE_VERSION) <<std::endl;
    std::cout <<"\n";
}

int main(int, char**) 
{
	App* app = new App();
    Factory* factory = new Factory(
		app->physicsComponents, 
		app->renderComponents, 
        app->transformComponents);

    GetOpenGLVersionInfo();


	factory->make_cube({3.0f, 0.0f, 0.25f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 10.0f});

    factory->make_girl({5.0f, 00.0f, 0.25f}, {0.0f, 0.0f, 180.0f});

	unsigned int cameraEntity = factory->make_camera({0.0f, 0.0f, 1.0f}, {0.0f, 0.0f,0.0f});

	CameraComponent* camera = new CameraComponent();
	app->cameraComponent = camera;
	app->cameraID = cameraEntity;


	/*unsigned int cubeEntity = app->make_entity();
	TransformComponent transform;
	transform.position = {3.0f, 0.0f, 0.25f};
	transform.eulers = {0.0f, 0.0f, 0.0f};
	app->transformComponents[cubeEntity] = transform;

	PhysicsComponent physics;
	physics.velocity = {0.0f, 0.0f, 0.0f};
	physics.eulerVelocity = {0.0f, 0.0f, 10.0f};
	app->physicsComponents[cubeEntity] = physics;
	
	RenderComponent render;
	render.mesh = app->make_cube_mesh({0.25f, 0.25f, 0.25f});
	render.material = app->make_texture("../img/paper.jpg");
	app->renderComponents[cubeEntity] = render;

	unsigned int cameraEntity = app->make_entity();
	transform.position = {0.0f, 0.0f, 1.0f};
	transform.eulers = {0.0f, 0.0f, 0.0f};
	app->transformComponents[cameraEntity] = transform;

	CameraComponent* camera = new CameraComponent();
	app->cameraComponent = camera;
	app->cameraID = cameraEntity;*/

	app->set_up_opengl();
	app->make_systems();

	app->run();

    delete factory;
	delete app;
	
    return 0;
}


