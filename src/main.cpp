#include "config.hpp"
#include "controller/app.hpp"
#include "components/camera_component.hpp"
#include "components/physics_component.hpp"
#include "components/render_component.hpp"
#include "components/transform_component.hpp"
#include "factories/factory.hpp"
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
        app->transformComponents,
        app->animationComponents,
		app->cameraComponents);

    GetOpenGLVersionInfo();


	factory->make_cube({3.0f, -1.5f, 0.25f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 10.0f});

    factory->make_girl({5.0f, 0.0f, 0.25f}, {0.0f, 0.0f, 180.0f});

    factory->make_revy({4.0f, 2.0f, 0.25f}, {0.0f, 0.0f, 270.0f});

	factory->make_camera({0.0f, 0.0f, 1.0f}, {0.0f, 0.0f,0.0f});
	

	app->set_up_opengl();
	app->make_systems();

	app->run();

	delete app;
	
    return 0;
}


