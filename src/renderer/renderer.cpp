#include "renderer.h"
#include "OpenGLInit.h"

#include <array>

struct Vertex
{
    glm::vec4 position;
    float textureIndex;
};

namespace Renderer
{
    static GLFWwindow* window;

    bool Init()
    {
        if(!OpenGLInit(&window))
            return false;

        

        return true;
    }

    bool Shutdown()
    {
        glfwTerminate();
        return true;
    }

    void Draw(const glm::vec2& pos, const glm::vec2& size, int level)
    {

    }


    GLFWwindow* GetWindow()
    {
        return window;
    }
}