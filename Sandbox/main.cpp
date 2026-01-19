#include "Engine.h"
#include "window.h"

int main()
{
    EngineInit();  
    while (EngineUpdate())
    {

    }
    EngineShutdown();
}
