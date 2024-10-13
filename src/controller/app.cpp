#include "app.hpp"


App::App() 
{
    set_up_glfw();
}

App::~App() 
{
    for (unsigned int& shader : shaders) 
    {
        glDeleteProgram(shader);
    }

    delete motionSystem;
    delete cameraSystem;
    delete renderSystem;
    delete animationSystem;
    
    glfwTerminate();
}


void App::run() 
{

    lastTime = glfwGetTime();
    numFrames = 0;
    frameTime = 16.0f;

    while (!glfwWindowShouldClose(window)) {

        motionSystem->update(frameTime / 1000.0f);
        
        // send all data about the camera to the appropriate shader
        bool should_close = cameraSystem->update(frameTime / 1000.0f);
		
        if (should_close) {
			break;
		}

        animationSystem->update(frameTime);
		renderSystem->update();

        handle_frame_timing();  
	}
}


void App::set_up_glfw() 
{
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	
	window = glfwCreateWindow(640, 480, "glfw window!", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Couldn't load opengl" << std::endl;
		glfwTerminate();
	}

}


void App::set_up_opengl() 
{
    glClearColor(0.25f, 0.5f, 0.75f, 1.0f);
        //Set the rendering region to the actual screen size
        int w,h;
        glfwGetFramebufferSize(window, &w, &h);
        //(left, top, width, height)
        glViewport(0,0,w,h);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

	shaders.push_back(make_shader(
		"../src/shaders/vertex_sky.txt", 
		"../src/shaders/fragment_sky.txt"));
	shaders.push_back(make_shader(
		"../src/shaders/geometry_vertex.txt", 
		"../src/shaders/frag.txt"));
	shaders.push_back(make_shader(
		"../src/shaders/vert.txt", 
		"../src/shaders/frag.txt"));
    
	glm::mat4 projection = glm::perspective(45.0f, 640.0f / 480.0f, 0.1f, 50.0f);

    for (size_t i = 1; i < 3; ++i) 
    {
        unsigned int shader = shaders[i];

        glUseProgram(shader);
	    unsigned int projLocation = glGetUniformLocation(shader, "projection");
	    glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projection));
    }
}


void App::make_systems() 
{
	animationSystem = new AnimationSystem(animationComponents);
    motionSystem = new MotionSystem(transformComponents, physicsComponents);
    cameraSystem = new CameraSystem(shaders, window, transformComponents, cameraComponents);
    renderSystem = new RenderSystem(shaders, window, transformComponents, renderComponents, animationComponents);
}


void App::handle_frame_timing() {
	currentTime = glfwGetTime();
	double delta = currentTime - lastTime;

	if (delta >= 1) {
		int framerate{ std::max(1, int(numFrames / delta)) };
		std::stringstream title;
		title << "Running at " << framerate << " fps.";
		glfwSetWindowTitle(window, title.str().c_str());
		lastTime = currentTime;
		numFrames = -1;
		frameTime = float(1000.0 / framerate);
	}

	++numFrames;
}