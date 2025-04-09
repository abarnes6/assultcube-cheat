#include "main.h"
#include "cheat.hpp"
#include <windows.h>
#include <cstdio>
#include "hook.hpp"

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
    FILE* pFile;

    switch (fdwReason) {
    case DLL_PROCESS_ATTACH: {
        AllocConsole();
        freopen_s(&pFile, "CONIN$", "r", stdin);
        freopen_s(&pFile, "CONOUT$", "w", stdout);
        freopen_s(&pFile, "CONOUT$", "w", stderr);
        init();
        break;
    }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        unHook();
        break;
    }   
    
    

    return TRUE;
}