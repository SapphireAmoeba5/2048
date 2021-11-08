#include "board.h"

#include <iostream>
#include <Random.h>
#include <renderer/renderer.h>
#include <macros.h>

namespace Board
{
    // Static function declarations
    static int Index(int x, int y);

    // Shift the board in one of these directions.
    // I have to redesign these functions because they kinda suck
    static void MoveLeft();
    static void MoveRight();
    static void MoveUp();
    static void MoveDown();

    // Place a sqaure somewhere on the board randomly
    static void PlaceRandom();
    // Static vars
    static glm::vec2 s_Size;
    static int s_1DSize;
    static int* s_Board;

    void Init(const glm::vec2& size)
    {
        Random random;
        s_Size = size;
        s_1DSize = size.x * size.y;
        s_Board = new int[s_1DSize];
        
        
        // Initializing board
        CONSOLE_PRINT("Initializing board");
        int count = 2; // Number of starting cells

        for(int i = 0; i < s_1DSize; i++)
        {
            if(count > 0 && random() % 5 == 3)
            {
                s_Board[i] = random() % 2;
                count--;
            }
            else
                s_Board[i] = -1;
        }

        // Checking if cells are placed. For loop won't run if 'count' is already 0
        for(; count > 0; count--)
        {
            int index = random() % s_1DSize;
            s_Board[index] = random() % 2;
            count--;
        }
    }

    void Shutdown()
    {
        delete[] s_Board;
    }

    void DrawBoard()
    {
        // The size that each sqaure should be
        const glm::vec2 size = {Renderer::GetWindowSize().x / s_Size.x,
                                Renderer::GetWindowSize().y / s_Size.y};

        for(int x = 0; x < s_Size.x; x++)
        {
            for(int y = 0; y < s_Size.y; y++)
            {
                int level = s_Board[Index(x,y)];
                if(level != -1)
                {
                    // Calculate the position of the square
                    const glm::vec2 pos = {(0.0f + x) * size.x + (size.x / 2),
                                            (0.0f, y) * size.y + (size.y / 2)};
                    
                    Renderer::Draw(pos, size, s_Board[Index(x,y)]);
                }
            }
        }
    }

    void ShiftBoard(Direction direction)
    {
        switch(direction)
        {
        case Direction::Left:
            MoveLeft();
            break;
        case Direction::Right:
            MoveRight();
            break;
        case Direction::Up:
            MoveUp();
            break;
        case Direction::Down:
            MoveDown();
            break;
        }
    }
}



// Static function definitions

// Converts 2D index to 1D index
static int Board::Index(int x, int y)
{
    return y * s_Size.x + x;
}

static void Board::PlaceRandom()
{
    Random random;

    // Checking if there are any slots to place
    bool slot = false;
    for(int i = 0; i < s_1DSize; i++)
    {
        if(s_Board[i] == -1)
        {
            slot = true;
            break;
        }
    }
    if(!slot)
        return;

    // Place a square in random slot
    int r;
    do
    {
        r = random() % s_1DSize;
    }while(s_Board[r] != -1);

    int val = random() % 2;
    s_Board[r] = val;
}

static void Board::MoveLeft()
{
    bool moved = false;

    for(int i = 0; i < s_Size.x; i++)
    {
        for(int x = s_Size.x-1; x > 0; x--)
        {
            for(int y = 0; y < s_Size.x; y++)
            {
                int curIndex = Index(x,y);
                int nexIndex = Index(x-1,y);

                if(s_Board[nexIndex] == -1 && s_Board[curIndex] != -1)
                {
                    s_Board[nexIndex] = s_Board[curIndex];
                    s_Board[curIndex] = -1;
                    moved = true;
                }
            }
        }
    }

    for(int y = 0; y < s_Size.y; y++)
    {
        for(int x = 0; x < s_Size.x-1; x++)
        {
            int curIndex = Index(x,y);
            int nexIndex = Index(x+1,y);

            if(s_Board[curIndex] == -1 && s_Board[nexIndex] == -1)
                continue;

            if(s_Board[curIndex] == s_Board[nexIndex])
            {
                s_Board[curIndex] = s_Board[nexIndex] + 1;
                s_Board[nexIndex] = -1;
                moved = true;
            }
        }   
    }

    for(int i = 0; i < s_Size.x; i++)
    {
        for(int x = s_Size.x-1; x > 0; x--)
        {
            for(int y = 0; y < s_Size.x; y++)
            {
                int curIndex = Index(x,y);
                int nexIndex = Index(x-1,y);

                if(s_Board[nexIndex] == -1 && s_Board[curIndex] != -1)
                {
                    s_Board[nexIndex] = s_Board[curIndex];
                    s_Board[curIndex] = -1;
                    moved = true;
                }
            }
        }
    }

    if(moved)
    {
        PlaceRandom();
    }
}

static void Board::MoveRight()
{
    bool moved = false;

    for(int i = 0; i < s_Size.x; i++)
    {
        for(int x = 0; x < s_Size.x-1; x++)
        {
            for(int y = 0; y < s_Size.x; y++)
            {
                int curIndex = Index(x,y);
                int nexIndex = Index(x+1,y);

                if(s_Board[nexIndex] == -1 && s_Board[curIndex] != -1)
                {
                    s_Board[nexIndex] = s_Board[curIndex];
                    s_Board[curIndex] = -1;
                    moved = true;
                }
            }
        }
    }

    for(int y = 0; y < s_Size.y; y++)
    {
        for(int x = s_Size.x-1; x > 0; x--)
        {
            int curIndex = Index(x,y);
            int nexIndex = Index(x-1,y);

            if(s_Board[curIndex] == -1 && s_Board[nexIndex] == -1)
                continue;

            if(s_Board[curIndex] == s_Board[nexIndex])
            {
                s_Board[curIndex] = s_Board[nexIndex] + 1;
                s_Board[nexIndex] = -1;
                moved = true;
            }
        }   
    }

    for(int i = 0; i < s_Size.x; i++)
    {
        for(int x = 0; x < s_Size.x-1; x++)
        {
            for(int y = 0; y < s_Size.x; y++)
            {
                int curIndex = Index(x,y);
                int nexIndex = Index(x+1,y);

                if(s_Board[nexIndex] == -1 && s_Board[curIndex] != -1)
                {
                    s_Board[nexIndex] = s_Board[curIndex];
                    s_Board[curIndex] = -1;
                    moved = true;
                }
            }
        }
    }

    if(moved)
    {
        PlaceRandom();
    }
}

static void Board::MoveUp()
{
    bool moved = false;

    for(int i = 0; i < s_Size.y; i++)
    {
        for(int y = s_Size.y-1; y > 0; y--)
        {
            for(int x = 0; x < s_Size.x; x++)
            {
                int curIndex = Index(x,y);
                int nexIndex = Index(x,y-1);

                if(s_Board[curIndex] == -1 && s_Board[nexIndex] != -1)
                {
                    s_Board[curIndex] = s_Board[nexIndex];
                    s_Board[nexIndex] = -1;
                    moved = true;
                }
            }
        }
    }

    for(int x = 0; x < s_Size.x; x++)
    {
        for(int y = s_Size.y-1; y > 0; y--)
        {
            int curIndex = Index(x,y);
            int nexIndex = Index(x,y-1);

            if(s_Board[curIndex] == -1 && s_Board[nexIndex] == -1)
                continue;

            if(s_Board[curIndex] == s_Board[nexIndex])
            {
                s_Board[curIndex] = s_Board[nexIndex] + 1;
                s_Board[nexIndex] = -1;
                moved = true;
            }
        }
    }

    for(int i = 0; i < s_Size.y; i++)
    {
        for(int y = s_Size.y-1; y > 0; y--)
        {
            for(int x = 0; x < s_Size.x; x++)
            {
                int curIndex = Index(x,y);
                int nexIndex = Index(x,y-1);

                if(s_Board[curIndex] == -1 && s_Board[nexIndex] != -1)
                {
                    s_Board[curIndex] = s_Board[nexIndex];
                    s_Board[nexIndex] = -1;
                    moved = true;
                }
            }
        }
    }

    if(moved)
    {
        PlaceRandom();
    }
}

static void Board::MoveDown()
{
    bool moved = false;

    for(int i = 0; i < s_Size.y; i++)
    {
        for(int y = 0; y < s_Size.y-1; y++)
        {
            for(int x = 0; x < s_Size.x; x++)
            {
                int curIndex = Index(x,y);
                int nexIndex = Index(x,y+1);

                if(s_Board[curIndex] == -1 && s_Board[nexIndex] != -1)
                {
                    s_Board[curIndex] = s_Board[nexIndex];
                    s_Board[nexIndex] = -1;
                    moved = true;
                }
            }
        }
    }

    for(int x = 0; x < s_Size.x; x++)
    {
        for(int y = 0; y < s_Size.y-1; y++)
        {
            int curIndex = Index(x,y);
            int nexIndex = Index(x,y+1);

            if(s_Board[curIndex] == -1 && s_Board[nexIndex] == -1)
                continue;

            if(s_Board[curIndex] == s_Board[nexIndex])
            {
                s_Board[curIndex] = s_Board[nexIndex] + 1;
                s_Board[nexIndex] = -1;
                moved = true;
            }
        }
    }

    for(int i = 0; i < s_Size.y; i++)
    {
        for(int y = 0; y < s_Size.y-1; y++)
        {
            for(int x = 0; x < s_Size.x; x++)
            {
                int curIndex = Index(x,y);
                int nexIndex = Index(x,y+1);

                if(s_Board[curIndex] == -1 && s_Board[nexIndex] != -1)
                {
                    s_Board[curIndex] = s_Board[nexIndex];
                    s_Board[nexIndex] = -1;
                    moved = true;
                }
            }
        }
    }

    if(moved)
    {
        PlaceRandom();
    }
}