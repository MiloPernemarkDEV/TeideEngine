#include "Engine.h"
#include "window.h"

static window* g_Window = nullptr;

extern "C" TEIDE_API bool EngineInit()
{
    g_Window = new window();
    return g_Window != nullptr;
}

extern "C" TEIDE_API bool EngineUpdate()
{
    if (!g_Window) return false;

    if (!g_Window->ProcessMessages())
        return false;

    // TODO: render + update here

    return true;
}

extern "C" TEIDE_API void EngineShutdown()
{
    delete g_Window;
    g_Window = nullptr;
}
