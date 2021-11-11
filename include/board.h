#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Board
{
    enum class Direction
    {
        Left  = 0,
        Right = 1,

        Up    = 2,
        Down  = 3
    };

    void Init(const glm::ivec2& size);
    void Shutdown();
    void ResetBoard(const glm::ivec2& size);
    void DrawBoard();

    void ShiftBoard(Direction direction);
}