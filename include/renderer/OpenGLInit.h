#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <macros.h>

#include <iostream>

static bool OpenGLInit(GLFWwindow** window, int width, int height, const char* name)
{

    if(!glfwInit())
    {
        std::cout<<"Failed to initialize GLFW"<<std::endl;
        return false;
    }
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    *window = glfwCreateWindow(width, height, name, NULL, NULL);
    if(window == nullptr)
    {
        std::cout<<"Failed to create GLFW window"<<std::endl;
        return false;
    }
    glfwMakeContextCurrent(*window);
    

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<<"Failed to initialize OpenGL context/glad"<<std::endl;
        return false;
    }
    
    CONSOLE_PRINT("OpenGL Version: "<<glGetString(GL_VERSION));

    return true;
}