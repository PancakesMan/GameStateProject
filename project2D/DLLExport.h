#pragma once
#ifdef _DLL_CONFIG
#define DLL __declspec(dllexport)
#else
#define DLL
#endif