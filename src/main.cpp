#include "2048.h"

#include <iostream>

int main()
{
    if(!g2048::Init())
        return -1;
    
    g2048::Run();
    
    if(!g2048::Shutdown())
    {
        std::cout<<"Failure shutting down!\n";
        return 1;
    }

    return 0;
}