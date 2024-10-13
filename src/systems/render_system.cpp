#include "render_system.hpp"
#include "../factories/mesh_factory.hpp"
#include "../factories/texture_factory.hpp"

RenderSystem::RenderSystem(std::vector<unsigned int>& shaders, GLFWwindow* window, 
    ComponentSet<TransformComponent> &transforms,
    ComponentSet<RenderComponent> &renderables,
    ComponentSet<AnimationComponent> &animations)
    :
    shaders(shaders),
    transforms(transforms),
    renderables(renderables),
    animations(animations) 
{    
    this->window = window;

    textures.resize(2);
    VAOs.resize(2);
    VBOs.resize(2);
    EBOs.resize(2);
    build_sky();
    build_models();
    build_geometry();

    glUseProgram(shaders[0]);
    glUniform1i(glGetUniformLocation(shaders[0], "sky"), 1);
    glUseProgram(shaders[1]);
    glUniform1i(glGetUniformLocation(shaders[1], "materials"), 0);
    glUniform1i(glGetUniformLocation(shaders[1], "sky"), 1);
    glUseProgram(shaders[2]);
    glUniform1i(glGetUniformLocation(shaders[2], "materials"), 0);
    glUniform1i(glGetUniformLocation(shaders[2], "sky"), 1);
    modelLocation = glGetUniformLocation(shaders[2], "model");   
}

RenderSystem::~RenderSystem() 
{
    glDeleteVertexArrays(VAOs.size(), VAOs.data());

    glDeleteBuffers(VBOs.size(), VBOs.data());

    glDeleteBuffers(EBOs.size(), EBOs.data());

    glDeleteTextures(textures.size(), textures.data());
}


void RenderSystem::build_sky() {

    TextureFactory textureFactory;

    skyTexture = textureFactory.build_cubemap({
        "../img/sky_front.png",  //x+
		"../img/sky_back.png",   //x-
		"../img/sky_left.png",   //y+
		"../img/sky_right.png",  //y-
		"../img/sky_top.png",     //z+
		"../img/sky_bottom.png",  //z-
    });
}

void RenderSystem::build_models() 
{
    MeshFactory meshFactory;
    TextureFactory textureFactory;
    meshFactory.start_obj_mesh();

    //Cube
    ObjectType objectType = ObjectType::eBox;
    AnimationType animationType = AnimationType::eNone;
    offsets[objectType][animationType] = meshFactory.offset;
    
    glm::mat4 preTransform = glm::mat4(1.0f);
    preTransform = glm::scale(preTransform, {0.25f, 0.25f, 0.25f});
    meshFactory.append_obj_mesh("../models/cube.obj", preTransform, 0); //layer 0
    elementCounts[objectType] = meshFactory.elementCount;
    meshFactory.elementCount = 0;

    //Girl
    objectType = ObjectType::eGirl;
    animationType = AnimationType::eNone;
    offsets[objectType][animationType] = meshFactory.offset;

    preTransform = glm::mat4(1.0);
    preTransform = glm::mat4(1.0f);
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), { 1.0f, 0.0f, 0.00f });
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), { 0.0f, 1.0f, 0.0f });
    preTransform = glm::translate(preTransform,{0.0f, 1.0f, -1.5f}); 
    meshFactory.append_obj_mesh("../models/girl.obj", preTransform, 1); //layer 1
    elementCounts[objectType] = meshFactory.elementCount;
    meshFactory.elementCount = 0;

    //Revy
    objectType = ObjectType::eRevy;
    animationType = AnimationType::eRun;
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform,{0.0f, 0.0f, -0.25f}); 
	preTransform = glm::rotate(preTransform, glm::radians(-90.0f), { 0.0f, 0.0f, 1.0f });
    offsets[objectType][animationType] = meshFactory.offset;
 
    std::stringstream filepath;
    std::string built_filepath;	
    for(size_t i = 0; i <19; ++i)
    {
        filepath.str("");
        filepath <<"../models/Revy_run_0000";
        if(i <= 9)
        {
            filepath <<"0";
        }
        filepath <<i <<".obj";
        built_filepath = filepath.str();
        meshFactory.append_obj_mesh(built_filepath.c_str(), preTransform, 2); //layer 2

        if (i == 0) 
        {
            elementCounts[objectType] = meshFactory.elementCount;
            meshFactory.elementCount = 0;
        }
    }

    StaticMesh mesh = meshFactory.build_obj_mesh();
    VAOs[1] = mesh.VAO;
    VBOs[1] = mesh.VBO;
    EBOs[1] = mesh.EBO;

    textureFactory.start_texture_array(3);
    textureFactory.load_into_array("../img/paper.jpg", 0);
    textureFactory.load_into_array("../img/stargirl.png", 1);
    textureFactory.load_into_array("../img/Revy_Final.png", 2);
    textures[1] = textureFactory.finalize_texture_array();
}
    

void RenderSystem::build_geometry() 
{
    MeshFactory meshFactory;
    TextureFactory textureFactory;

    ObjectType objectType = ObjectType::eGeometry;
    AnimationType animationType = AnimationType::eNone;
    meshFactory.start_obj_mesh();

    //ground
    glm::mat4 preTransform = glm::mat4(1.0f); 
    preTransform = glm::scale(preTransform, {2.0f, 2.0f, 1.0f});
    meshFactory.append_obj_mesh("../models/ground.obj", preTransform, 0);
    //west wall
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {10.0f, 0.0f, 0.0f});
    meshFactory.append_obj_mesh("../models/wall.obj", preTransform, 1);
    //east wall
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {-10.0f, 0.0f, 0.0f});
    meshFactory.append_obj_mesh("../models/wall.obj", preTransform, 1);
    //North wall
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {0.0f, 10.0f, 0.0f});
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), {0.0f, 0.0f, 1.0f});
    meshFactory.append_obj_mesh("../models/wall.obj", preTransform, 1);
    //South wall
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {0.0f, -10.0f, 0.0f});
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), {0.0f, 0.0f, 1.0f});
    meshFactory.append_obj_mesh("../models/wall.obj", preTransform, 1);
    //Northwest corner
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {10.0f, 10.0f, 0.0f});
    meshFactory.append_obj_mesh("../models/corner.obj", preTransform, 2);
    //Southwest corner
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {10.0f, -10.0f, 0.0f});
    meshFactory.append_obj_mesh("../models/corner.obj", preTransform, 2);
    //Southeast corner
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {-10.0f, -10.0f, 0.0f});
    meshFactory.append_obj_mesh("../models/corner.obj", preTransform, 2);
    //Northeast corner
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {-10.0f, 10.0f, 0.0f});
    meshFactory.append_obj_mesh("../models/corner.obj", preTransform, 2);
    //a tree
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {3.0f, -2.5f, 0.0f});
    meshFactory.append_obj_mesh("../models/tree.obj", preTransform, 3);
    //another tree
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform, {-2.0f, 1.0f, 0.0f});
    meshFactory.append_obj_mesh("../models/tree.obj", preTransform, 3);

    elementCounts[objectType] = meshFactory.elementCount;
    StaticMesh mesh = meshFactory.build_obj_mesh();
    VAOs[0] = mesh.VAO;
    VBOs[0] = mesh.VBO;
    EBOs[0] = mesh.EBO;

    textureFactory.start_texture_array(4);
    textureFactory.load_into_array("../img/GrassAndDirt_S.jpg", 0);
    textureFactory.load_into_array("../img/red_brick.jpg", 1);
    textureFactory.load_into_array("../img/red_brick.jpg", 2);
    textureFactory.load_into_array("../img/Tree_Texture.png", 3);
    textures[0] = textureFactory.finalize_texture_array();
}


void RenderSystem::update() 
{ 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear frame

    //Sky
    glUseProgram(shaders[0]); 
    glDisable(GL_DEPTH_TEST); //for no interfere with anything else objects
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyTexture);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glEnable(GL_DEPTH_TEST);
    // not binding VAO cause hard coded in the Vert Shader

    //Static geometry
    glUseProgram(shaders[1]); 
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textures[0]);
    glBindVertexArray(VAOs[0]);
    glDrawElements(GL_TRIANGLES, elementCounts[ObjectType::eGeometry], GL_UNSIGNED_INT, 0);

    //Everything else
    glUseProgram(shaders[2]);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textures[1]);
    glBindVertexArray(VAOs[1]);
    for (size_t i = 0; i < renderables.entities.size(); ++i) 
    {
        uint32_t entity = renderables.entities[i];
        RenderComponent& renderable = renderables.components[i];
        TransformComponent& transform = transforms.get_component(entity);

        glm::mat4 model = glm::mat4(1.0f);
	    model = glm::translate(model, transform.position);
	    model = glm::rotate(model, glm::radians(transform.eulers.z), { 0.0f, 0.0f, 1.0f });
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
        unsigned int elementCount = elementCounts[renderable.objectType];
        size_t frame = 0;
        if (renderable.animationType != AnimationType::eNone) {
            AnimationComponent& animation = 
                animations.get_component(entity);
            frame = static_cast<size_t>(animation.frame);
        }
        unsigned int offset = 
            sizeof(unsigned int) * (
                offsets[renderable.objectType][renderable.animationType] + frame * elementCount);
        
        glDrawElements(GL_TRIANGLES, elementCount, GL_UNSIGNED_INT, (void*)(offset));
    }
    
	glfwSwapBuffers(window);
}
