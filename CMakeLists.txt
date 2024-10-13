cmake_minimum_required(VERSION 3.0.0)
project(my_opengl_project VERSION 0.1.0)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(my_opengl_project 
    src/config.hpp 
    src/config.cpp
    src/main.cpp 
    src/glad.c 
    src/systems/camera_system.cpp
    src/systems/motion_system.cpp
    src/systems/render_system.cpp
    src/systems/animation_system.cpp
    src/view/shader.cpp
    src/controller/app.cpp
    src/factories/factory.cpp
    src/factories/mesh_factory.cpp
    src/factories/texture_factory.cpp
    src/controller/app.cpp
    #src/triangle_mesh.cpp
    #src/material.cpp
    #src/linear_algebra.cpp
    )

target_link_libraries(my_opengl_project 
    glfw 
    OpenGL::GL) 