#include "2048.h"
#include <macros.h>

#include <iostream>

int main()
{
    std::ios_base::sync_with_stdio(false);
    CONSOLE_PRINT("========STARTING GAME========");

    if(!g2048::Init())
    {
        CONSOLE_PRINT("Failed to initialize the program!");
        return -1;
    }
    
    CONSOLE_PRINT("Running game");
    g2048::Run();
    
    CONSOLE_PRINT("\n====SHUTTING DOWN GAME====");
    if(!g2048::Shutdown())
    {
        std::cout<<"FAILURE : Failure shutting down!\n";
        return 1;
    }

    return 0;
}