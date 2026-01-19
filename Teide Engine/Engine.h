#pragma once
#include "core.h"

extern "C" TEIDE_API bool EngineInit();
extern "C" TEIDE_API bool EngineUpdate();
extern "C" TEIDE_API void EngineShutdown();

extern "C" TEIDE_API float EngineGetDeltaTime();