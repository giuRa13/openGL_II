#include "render_system.hpp"
#include "../factories/mesh_factory.hpp"
#include "../factories/texture_factory.hpp"

RenderSystem::RenderSystem(unsigned int shader, GLFWwindow* window) 
{    
    modelLocation = glGetUniformLocation(shader, "model");
    
    this->window = window;

    build_models();

    //build_geometry();
}

RenderSystem::~RenderSystem() {
    for (auto& [objectType, animations] : VAOs) {
        for (auto& [animation, VAO] : animations) {
            glDeleteVertexArrays(1, &VAO);
        }
    }

    for (auto& [objectType, animations] : VBOs) {
        for (auto& [animation, VBO] : animations) {
            glDeleteBuffers(1, &VBO);
        }
    }

    for (auto& [objectType, texture] : textures) {
        glDeleteTextures(1, &texture);
    }
}


void RenderSystem::build_models() 
{
    MeshFactory meshFactory;
    TextureFactory textureFactory;

    //Cube
    ObjectType objectType = ObjectType::eBox;
    AnimationType animationType = AnimationType::eNone;

    meshFactory.start_obj_mesh();
    meshFactory.append_cube_mesh({0.25f, 0.25f, 0.25f});
    StaticMesh mesh = meshFactory.build_obj_mesh();
    VAOs[objectType][animationType] = mesh.VAO;
    VBOs[objectType][animationType] = mesh.VBO;
    vertexCounts[objectType] = mesh.vertexCount;
    textures[objectType] = textureFactory.make_texture("../img/crate.png");

    //Girl
    objectType = ObjectType::eGirl;
    animationType = AnimationType::eNone;
    glm::mat4 preTransform = glm::mat4(1.0f);
	preTransform = glm::rotate(preTransform, glm::radians(90.0f), { 1.0f, 0.0f, 0.0f });
    preTransform = glm::rotate(preTransform, glm::radians(90.0f), { 0.0f, 1.0f, 0.0f });
    
    meshFactory.start_obj_mesh();
    meshFactory.append_obj_mesh("../models/girl.obj", preTransform);
    mesh = meshFactory.build_obj_mesh();
    VAOs[objectType][animationType] = mesh.VAO;
    VBOs[objectType][animationType] = mesh.VBO;
    vertexCounts[objectType] = mesh.vertexCount;
    textures[objectType] = textureFactory.make_texture("../img/stargirl.png");

    //Revy
    objectType = ObjectType::eRevy;
    animationType = AnimationType::eRun;
    preTransform = glm::mat4(1.0f);
    preTransform = glm::translate(preTransform,{0.0f, 0.0f, -1.0f}); 
	preTransform = glm::rotate(preTransform, glm::radians(-90.0f), { 0.0f, 0.0f, 1.0f });

    meshFactory.start_obj_mesh();
    textures[objectType] = textureFactory.make_texture("../img/Revy_Final.png");
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
        meshFactory.append_obj_mesh(built_filepath.c_str(), preTransform);

    }
    mesh = meshFactory.build_obj_mesh();
    VAOs[objectType][animationType] = mesh.VAO;
    VBOs[objectType][animationType] = mesh.VBO;
    vertexCounts[objectType] = mesh.vertexCount / 19;
}
    

void RenderSystem::update(
    std::unordered_map<unsigned int,TransformComponent> &transformComponents,
    std::unordered_map<unsigned int,RenderComponent> &renderComponents,
    std::unordered_map<unsigned int,AnimationComponent> &animationComponents) 
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear frame
    
    for (auto& [entity,renderable] : renderComponents)
    {
        TransformComponent& transform = transformComponents[entity];
        glm::mat4 model = glm::mat4(1.0f);
	    model = glm::translate(model, transform.position);
	    model = glm::rotate(model, glm::radians(transform.eulers.z), { 0.0f, 0.0f, 1.0f });
        glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
        
        glBindTexture(GL_TEXTURE_2D, textures[renderable.objectType]);
        unsigned int vertexCount = vertexCounts[renderable.objectType];
        size_t frame = 0;
        if (renderable.animationType != AnimationType::eNone)
        {
            frame = static_cast<size_t>(animationComponents[entity].frame);
        }

        glBindVertexArray(VAOs[renderable.objectType][renderable.animationType]);
        glDrawArrays(GL_TRIANGLES, frame * vertexCount, vertexCount);
    }
    
	glfwSwapBuffers(window);
}
