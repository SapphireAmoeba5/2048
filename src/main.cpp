#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


int main()
{
    if(!glfwInit())
    {
        std::cout<<"Failed to initialize GLFW"<<std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "2048", NULL, NULL);
    if(window == nullptr)
    {
        std::cout<<"Failed to create GLFW window"<<std::endl;
        return -1;
    }
    glfwMakeContextCurrent(window);

    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<<"Failed to initialize OpenGL context/glad"<<std::endl;
        return -1;
    }

    while(!glfwWindowShouldClose(window))
    {
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}