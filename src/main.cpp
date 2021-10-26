#include <iostream>

#include <GLFW/glfw3.h>


int main()
{
    if(!glfwInit())
    {
        std::cout<<"Failed to initialize GLFW"<<std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "2048", NULL, NULL);
    
}