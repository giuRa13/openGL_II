#pragma  once

#include "glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <vector>
#include <unordered_map>


std::vector<std::string> split(std::string line, std::string delimiter);

enum class ObjectType 
{
    eBox,
    eGirl,
    eRevy
};

enum class AnimationType
{
    eNone,
    eRun
};