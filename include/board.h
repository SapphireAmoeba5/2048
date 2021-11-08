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

    void Init(const glm::vec2& size);
    void Shutdown();

    void DrawBoard();

    void ShiftBoard(Direction direction);
}