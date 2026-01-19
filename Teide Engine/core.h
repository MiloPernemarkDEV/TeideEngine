#pragma once

#ifdef TEIDE_EXPORTS
#define TEIDE_API __declspec(dllexport)
#else
#define TEIDE_API __declspec(dllimport)
#endif