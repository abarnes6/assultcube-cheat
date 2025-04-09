#include <windows.h>
#include <iostream>

void* Trampoline(DWORD targetFunction, DWORD ourFunction);
void unHook();