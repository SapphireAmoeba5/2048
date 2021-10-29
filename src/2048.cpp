#include "2048.h"
#include "renderer/renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace g2048
{
    bool Init()
    {
        if(!Renderer::Init())
            return false;
        
        return true;
    }

    bool Run()
    {
        while(!glfwWindowShouldClose(Renderer::GetWindow()))
        {   
            glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            glfwPollEvents();
            glfwSwapBuffers(Renderer::GetWindow());
        }

        return true;
    }

    bool Shutdown()
    {
        if(!Renderer::Shutdown())
            return false;
            
        return true;
    }
}