#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace Renderer
{
    bool Init();
    bool Shutdown();

    void Draw(const glm::vec2& pos, const glm::vec2& size, int level);
    
    void BeginBatch();
    void EndBatch();

    const glm::vec2& GetWindowSize();
    int GetTextureCount();

    GLFWwindow* GetWindow();

    void InitImGui();
	void NewImGuiFrame();
	void RenderImGui();
	void ShutdownImGui();
}