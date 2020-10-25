#pragma once

#include <stdio.h>
#include <Windows.h>

#include "get_interfaces.h"

int init_hack(HMODULE hModule) 
{
    AllocConsole();
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);

    init::get_interfaces();

    while (true) {
        if (GetAsyncKeyState(VK_F9) & 1)
            break;
        Sleep(100);
    }

    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    switch (ul_reason_for_call) {
        case DLL_PROCESS_ATTACH:
            CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) init_hack, hModule, NULL, NULL);
            break;
        case DLL_PROCESS_DETACH:
            break;
    }
    return TRUE;
}

