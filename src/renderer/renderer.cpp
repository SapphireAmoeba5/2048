#include "rendererutil.h"
#include "OpenGLInit.h"
#include "Shader.h"

namespace Renderer
{
    // Static variables
    static GLFWwindow* window;
    static Shader* shader;

    static RendererData* s_Data;

    static glm::mat4 proj; 
    static glm::mat4 view;

    static glm::vec2 size = {500, 500};

    // Resize callback
    static void resize_callback(GLFWwindow* window, int width, int height)
    {
        size = {static_cast<float>(width),
                static_cast<float>(height)};
        glViewport(0, 0, width, height);
        proj = glm::ortho(0.0f, size.x, 0.0f, size.y);
        shader->SetUniformMat4f("u_MVP", proj);

    }  

    const glm::vec2& GetWindowSize()
    {
        return size;
    }


    //Function definitions
    bool Init()
    {
        if(!OpenGLInit(&window, size.x, size.y, "2048"))
            return false;

        s_Data = new RendererData;
        
        // Creating vertex array
        glGenVertexArrays(1, &s_Data->VAO);
        glBindVertexArray(s_Data->VAO);

        // Creating vertex buffer
        glCreateBuffers(1, &s_Data->VBO);
        glBindBuffer(GL_ARRAY_BUFFER, s_Data->VBO);
        glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 20, 0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 20, (const void*)8);

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 20, (const void*)16);
        
        // Creating index buffer
        glCreateBuffers(1, &s_Data->IBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data->IBO);

        //Creating index buffer data
        uint32_t* indicies = new uint32_t[MaxIndexCount];
        int offset = 0;
        for(size_t i = 0; i < MaxIndexCount; i += 6)
        {
            indicies[0 + i] = 0 + offset;
            indicies[1 + i] = 1 + offset;
            indicies[2 + i] = 2 + offset;

            indicies[3 + i] = 3 + offset;
            indicies[4 + i] = 2 + offset;
            indicies[5 + i] = 0 + offset;
            offset += 4;
        }
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * MaxIndexCount, indicies, GL_STATIC_DRAW);
        delete[] indicies;

        // Initializing textures on the shader
        shader = new Shader("assets/shaders/vertex.vert", "assets/shaders/fragment.frag");
        int textures[MaxTextureCount];
        for(size_t i = 0; i < MaxTextureCount; i++)
        {
            textures[i] = i;
        }
        shader->SetUniform1iv("u_Textures", MaxTextureCount, textures);

        

        // Loading textures
        s_Data->textures.push_back(LoadTexture("assets/textures/2.png"));
        s_Data->textures.push_back(LoadTexture("assets/textures/4.png"));
        s_Data->textures.push_back(LoadTexture("assets/textures/8.png"));
        s_Data->textures.push_back(LoadTexture("assets/textures/16.png"));
        s_Data->textures.push_back(LoadTexture("assets/textures/32.png"));
        s_Data->textures.push_back(LoadTexture("assets/textures/64.png"));
        s_Data->textures.push_back(LoadTexture("assets/textures/128.png"));
        s_Data->textures.push_back(LoadTexture("assets/textures/256.png"));
        s_Data->textures.push_back(LoadTexture("assets/textures/512.png"));
        s_Data->textures.push_back(LoadTexture("assets/textures/1024.png"));
        s_Data->textures.push_back(LoadTexture("assets/textures/2048.png"));
        s_Data->textures.push_back(LoadTexture("assets/textures/4096.png"));
        s_Data->textures.push_back(LoadTexture("assets/textures/8192.png"));


        // If textures loads properly then load the texture otherwise log the error
        for(int i = 0; i < s_Data->textures.size();i++)
        {
            if(s_Data->textures[i] != 0)
            {
                glBindTextureUnit(i, s_Data->textures[i]);
            }
            else
            {
                std::cout<<"texture: "<<(2 << i)<<" not loaded!"<<std::endl;
            }
                
        }

        // Initialize projection and view
        proj = glm::ortho(0.0f, size.x, 0.0f, size.y);
        view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        shader->SetUniformMat4f("u_MVP", proj * view);

        // Set resize callback
        glfwSetFramebufferSizeCallback(window, resize_callback);

        return true;
    }

    bool Shutdown()
    {
        // Delete textures
        for(size_t i = 0; i < s_Data->textures.size();i++)
        {
            glDeleteTextures(1, &s_Data->textures[i]);
        }
        
        // Delete vertex array
        glDeleteVertexArrays(1, &s_Data->VAO);

        // Delete vertex buffer
        glDeleteBuffers(1, &s_Data->VBO);
        
        // Delete index buffer
        glDeleteBuffers(1, &s_Data->IBO);


        glfwTerminate();
        return true;
    }

    void Draw(const glm::vec2& pos, const glm::vec2& size, int level)
    {
        std::array<Vertex, 4> verticies = CreateQuad(pos, size, static_cast<float>(level));

        s_Data->verticies[s_Data->VertexCount++] = verticies[0];
        s_Data->verticies[s_Data->VertexCount++] = verticies[1];
        s_Data->verticies[s_Data->VertexCount++] = verticies[2];
        s_Data->verticies[s_Data->VertexCount++] = verticies[3];

        s_Data->QuadCount++;
    }

    void BeginBatch()
    {
        s_Data->VertexCount = 0;
        s_Data->QuadCount = 0;
    }

    void EndBatch()
    {
        glBindVertexArray(s_Data->VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data->IBO);
        glBindBuffer(GL_ARRAY_BUFFER, s_Data->VBO);
        shader->Bind();

        glBufferSubData(GL_ARRAY_BUFFER, 0, MaxVertexCount * sizeof(Vertex), s_Data->verticies);

        glDrawElements(GL_TRIANGLES, s_Data->QuadCount * 6, GL_UNSIGNED_INT, 0);
    }

    GLFWwindow* GetWindow()
    {
        return window;
    }
}