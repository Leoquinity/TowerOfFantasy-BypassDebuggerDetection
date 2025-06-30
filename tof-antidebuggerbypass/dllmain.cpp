// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <iostream>
#include <MinHook.h>
using namespace std;

typedef void(__fastcall* tDebugBreak)();
typedef BOOL(__fastcall* tIsDebuggerPresent)();
tDebugBreak oDebugBreak = nullptr;
tIsDebuggerPresent oIsDebuggerPresent = nullptr;
void AllocateConsole() {
    FILE* fp;
    AllocConsole();
    freopen_s(&fp, "CONOUT$", "w", stdout);
    SetConsoleTitleA("tof-antidebugger!!!");
}
void __stdcall hDebugBreak() {
    MessageBoxA(0, "Intercepted!!!", "tof-antidebuggerbypass", MB_OK);
    return (void)0x0;
}
BOOL __stdcall hIsDebuggerPresent() 
{
    MessageBoxA(0, "Intercepted!!!", "tof-antidebuggerbypass", MB_OK);
    return FALSE;
}
namespace tofantidebugger 
{
    void** GetKernel32_AntiDebuggerPresentAddr() {
        HMODULE kernel32mod = GetModuleHandleA("kernel32.dll");
        FARPROC znm = GetProcAddress(kernel32mod, (LPCSTR)"AntiDebuggerPresent");
        return (void**)znm;
    }
    void** GetKernel32_DebugBreakAddr() {
        HMODULE kernel32mod = GetModuleHandleA("kernel32.dll");
        FARPROC sxx = GetProcAddress(kernel32mod, "DebugBreak");
        return (void**)sxx;
    }
}
DWORD WINAPI Thread() 
{
    AllocateConsole();
    MH_STATUS st_init = MH_Initialize();
    if (st_init == MH_OK) {
        cout << "Successfully Initializated MinHook!!!" << endl;
    }
    MH_STATUS statuszx = MH_CreateHook(tofantidebugger::GetKernel32_AntiDebuggerPresentAddr(), &hIsDebuggerPresent,(LPVOID*)(&oIsDebuggerPresent));
    if (statuszx == MH_OK) {
        cout << "Successfully Added AntiDebuggerPresent Anti-Detection!!!" << endl;
    }
    MH_STATUS azzquerty = MH_CreateHook(tofantidebugger::GetKernel32_DebugBreakAddr(), &hDebugBreak, (LPVOID*)(&oDebugBreak));
    if (azzquerty == MH_OK) {
        cout << "Successfully Added DebugBreak Anti-Detection!!!" << endl;
    }
    MH_EnableHook(tofantidebugger::GetKernel32_AntiDebuggerPresentAddr());
    MH_EnableHook(tofantidebugger::GetKernel32_DebugBreakAddr());
    return TRUE;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Thread, 0, 0, 0);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

