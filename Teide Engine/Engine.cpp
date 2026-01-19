#include "Engine.h"
#include "window.h"

static LARGE_INTEGER g_Frequency;
static LARGE_INTEGER g_LastTime;
static float g_DeltaTime = 0.0f;

// Engine owns window lifetime controlled by EngineInit/Shutdown
static window* g_Window = nullptr;

static void InitTimer();
static void UpdateDeltaTime();

extern "C" TEIDE_API bool EngineInit()
{
    if (g_Window) return false;

    g_Window = new window();
    InitTimer();       
    return true;
}

extern "C" TEIDE_API bool EngineUpdate()
{
    if (!g_Window) return false;

    if (!g_Window->ProcessMessages())
        return false;

    UpdateDeltaTime();

    // Update systems using g_DeltaTime
    // Render here

    return true;
}

extern "C" TEIDE_API void EngineShutdown()
{
    if (g_Window)
    {
        delete g_Window;
        g_Window = nullptr;
    }
}

static void InitTimer()
{
    QueryPerformanceFrequency(&g_Frequency);
    QueryPerformanceCounter(&g_LastTime);
}

static void UpdateDeltaTime()
{
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);

    g_DeltaTime =
        float(now.QuadPart - g_LastTime.QuadPart) /
        float(g_Frequency.QuadPart);

    g_LastTime = now;
}

extern "C" TEIDE_API float EngineGetDeltaTime()
{
    return g_DeltaTime;
}
