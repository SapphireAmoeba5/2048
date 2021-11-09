#include "2048.h"
#include "renderer/renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include <macros.h>
#include "board.h"

void key_press_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

namespace g2048
{
    static glm::vec2 boardSize = {4.0f, 4.0f};

    bool Init()
    {
        
        if(!Renderer::Init())
        {
            CONSOLE_PRINT("FAILURE : Failed to initialize renderer!");
            return false;
        }
        
        glfwSetKeyCallback(Renderer::GetWindow(), key_press_callback);

        Board::Init(boardSize);

        return true;
    }

    bool Run()
    {
        while(!glfwWindowShouldClose(Renderer::GetWindow()))
        {   
            glClearColor(0.0f, 0.3f, 0.7f, 1.0f); // The nice blue background
            glClear(GL_COLOR_BUFFER_BIT);

            Renderer::BeginBatch();

            Board::DrawBoard();

            Renderer::EndBatch();

            glfwPollEvents();
            glfwSwapBuffers(Renderer::GetWindow());
        }

        return true;
    }

    bool Shutdown()
    {
        CONSOLE_PRINT("Shutting down renderer");
        if(!Renderer::Shutdown())
            return false;
        
        CONSOLE_PRINT("Shutting down board");
        Board::Shutdown();

        return true;
    }
}



void key_press_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if(key == GLFW_KEY_N && mods == GLFW_MOD_CONTROL && action == GLFW_PRESS)
    {
        Board::ResetBoard(g2048::boardSize);
    }

    if((key == GLFW_KEY_LEFT || key == GLFW_KEY_A) && mods == 0 && action == GLFW_PRESS)
        Board::ShiftBoard(Board::Direction::Left);

    else if((key == GLFW_KEY_RIGHT || key == GLFW_KEY_D) && mods == 0 && action == GLFW_PRESS)
        Board::ShiftBoard(Board::Direction::Right);

    else if((key == GLFW_KEY_UP || key == GLFW_KEY_W) && mods == 0 && action == GLFW_PRESS)
        Board::ShiftBoard(Board::Direction::Up);

    else if((key == GLFW_KEY_DOWN || key == GLFW_KEY_S) && mods == 0 && action == GLFW_PRESS)
        Board::ShiftBoard(Board::Direction::Down);
}