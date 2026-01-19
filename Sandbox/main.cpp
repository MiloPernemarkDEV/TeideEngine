#include "Engine.h"
#include "window.h"
#include <iostream>

int main()
{
    EngineInit();  
    while (EngineUpdate())
    {
        std::cout << EngineGetDeltaTime() << "\n";


        Sleep(100);
    }
    EngineShutdown();
}
