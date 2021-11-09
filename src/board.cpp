#include "board.h"

#include <cstring>
#include <iostream>
#include <Random.h>
#include <renderer/renderer.h>
#include <macros.h>

namespace Board
{
    // Static function declarations
    static int Index(int x, int y);

    // Shift the board in one of these directions.
    static void MoveLeft();
    static void MoveRight();
    static void MoveUp();
    static void MoveDown();

    // Place a tile somewhere on the board randomly
    static void PlaceRandom();
    // Static vars
    static glm::vec2 s_Size;
    static int s_1DSize;
    static int* s_Board;

    void Init(const glm::vec2& size)
    {
        s_Size = size;
        s_1DSize = size.x * size.y;
        s_Board = new int[s_1DSize];
        
        
        // Initializing board
        memset(s_Board, -1, sizeof(int) * s_1DSize);

        int count = 2; // Number of starting cells
        for(int i = 0; i < count; i++) // Randomly place cells
        {
            PlaceRandom();
        }
    }

    void Shutdown()
    {
        delete[] s_Board;
    }

    void DrawBoard()
    {
        // The size that each tile should be
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
                                            (0.0f + y) * size.y + (size.y / 2)};
                    
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

    // Shifts all the blocks to the left and combines them if needed
    for(int y = 0; y < s_Size.y; y++) // The row being tested
    {
        for(int x = 0; x < s_Size.x ;x++) // The main tile being tested against
        {
            for(int xi = x+1; xi < s_Size.x; xi++) // the secondary tile being tested against
            {
                // If both tiles are -1 then skip to the next one
                if(s_Board[Index(x,y)] == -1 && s_Board[Index(xi,y)] == -1)
                    continue;

                if(s_Board[Index(x,y)] != -1 && s_Board[Index(xi,y)] != -1 && s_Board[Index(x,y)] != s_Board[Index(xi,y)]) // If two (non empty) tiles aren't equal, then
                    break;

                // If the space is empty, move the square into that empty space
                if(s_Board[Index(x,y)] == -1 && s_Board[Index(xi,y)] != -1)
                {
                    moved = true;
                    s_Board[Index(x,y)] = s_Board[Index(xi,y)];
                    s_Board[Index(xi,y)] = -1;
                    xi--;
                }
                
                // If the two tiles match then add them together
                else if(s_Board[Index(x,y)] == s_Board[Index(xi,y)])
                {
                    moved = true;
                    s_Board[Index(x,y)] = s_Board[Index(xi,y)] + 1;
                    s_Board[Index(xi,y)] = -1;
                    break;
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

    // Shifts all the blocks to the right  and combines them if needed
    for(int y = 0; y < s_Size.y; y++) // The row being tested
    {
        for(int x = s_Size.x-1; x > 0; x--) // The main tile being tested against
        {
            for(int xi = x-1; xi >= 0; xi--) // the secondary tile being tested against
            {
                // If both tiles are -1 then skip to the next one
                if(s_Board[Index(x,y)] == -1 && s_Board[Index(xi,y)] == -1)
                    continue;

                if(s_Board[Index(x,y)] != -1 && s_Board[Index(xi,y)] != -1 && s_Board[Index(x,y)] != s_Board[Index(xi,y)]) // If two (non empty) tiles aren't equal, then
                    break;

                // If the space is empty, move the square into that empty space
                if(s_Board[Index(x,y)] == -1 && s_Board[Index(xi,y)] != -1)
                {
                    moved = true;
                    s_Board[Index(x,y)] = s_Board[Index(xi,y)];
                    s_Board[Index(xi,y)] = -1;
                    xi--;
                }
                
                // If the two tiles match then add them together
                else if(s_Board[Index(x,y)] == s_Board[Index(xi,y)])
                {
                    moved = true;
                    s_Board[Index(x,y)] = s_Board[Index(xi,y)] + 1;
                    s_Board[Index(xi,y)] = -1;
                    break;
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

    // Shifts all the blocks up and combines them if needed
    for(int x = 0; x < s_Size.x; x++) // The row being tested
    {
        for(int y = s_Size.y-1; y > 0 ;y--) // The main tile being tested against
        {
            for(int yi = y-1; yi >= 0; yi--) // the secondary tile being tested against
            {
                // If both tiles are -1 then skip to the next one
                if(s_Board[Index(x,y)] == -1 && s_Board[Index(x,yi)] == -1)
                    continue;

                if(s_Board[Index(x,y)] != -1 && s_Board[Index(x,yi)] != -1 && s_Board[Index(x,y)] != s_Board[Index(x,yi)]) // If two (non empty) tiles aren't equal, then
                    break;

                // If the space is empty, move the square into that empty space
                if(s_Board[Index(x,y)] == -1 && s_Board[Index(x,yi)] != -1)
                {
                    moved = true;
                    s_Board[Index(x,y)] = s_Board[Index(x,yi)];
                    s_Board[Index(x,yi)] = -1;
                    yi++;
                }
                
                // If the two tiles match then add them together
                else if(s_Board[Index(x,y)] == s_Board[Index(x,yi)])
                {
                    moved = true;
                    s_Board[Index(x,y)] = s_Board[Index(x,yi)] + 1;
                    s_Board[Index(x,yi)] = -1;
                    break;
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

    // Shifts all the blocks down and combines them if needed
    for(int x = 0; x < s_Size.x; x++) // The row being tested
    {
        for(int y = 0; y < s_Size.y;y++) // The main tile being tested against
        {
            for(int yi = y+1; yi < s_Size.y; yi++) // the secondary tile being tested against
            {
                // If both tiles are -1 then skip to the next one
                if(s_Board[Index(x,y)] == -1 && s_Board[Index(x,yi)] == -1)
                    continue;

                if(s_Board[Index(x,y)] != -1 && s_Board[Index(x,yi)] != -1 && s_Board[Index(x,y)] != s_Board[Index(x,yi)]) // If two (non empty) tiles aren't equal, then
                    break;

                // If the space is empty, move the square into that empty space
                if(s_Board[Index(x,y)] == -1 && s_Board[Index(x,yi)] != -1)
                {
                    moved = true;
                    s_Board[Index(x,y)] = s_Board[Index(x,yi)];
                    s_Board[Index(x,yi)] = -1;
                    yi--;
                }
                
                // If the two tiles match then add them together
                else if(s_Board[Index(x,y)] == s_Board[Index(x,yi)])
                {
                    moved = true;
                    s_Board[Index(x,y)] = s_Board[Index(x,yi)] + 1;
                    s_Board[Index(x,yi)] = -1;
                    break;
                }
            }
        }
    }

    if(moved)
    {
        PlaceRandom();
    }
}

void Board::ResetBoard(const glm::vec2& size)
{
    Shutdown();
    Init(size);
}