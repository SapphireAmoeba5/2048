#include "2048.h"
#include "debug.h"


int main()
{
    if(!g2048::Init())
        return -1;
    
    g2048::Run();
    g2048::Shutdown();

    return 0;
}