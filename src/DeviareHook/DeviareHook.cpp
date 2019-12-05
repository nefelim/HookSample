#include "pch.h"
#include "DeviareProcessor.h"

extern "C" 
{
    BOOL(WINAPI * Real_WriteFile)(HANDLE hFile,
            LPCVOID lpBuffer,
            DWORD nNumberOfBytesToWrite,
            LPDWORD lpNumberOfBytesWritten,
            LPOVERLAPPED lpOverlapped)
        = WriteFile;

    BOOL WINAPI Mine_WriteFile(HANDLE hFile,
        LPCVOID lpBuffer,
        DWORD nNumberOfBytesToWrite,
        LPDWORD lpNumberOfBytesWritten,
        LPOVERLAPPED lpOverlapped)
    {
        HANDLE hCout = ::GetStdHandle(STD_OUTPUT_HANDLE);
        std::string str = "Hello Deviare Hook!\n";
        if (hFile == hCout)
        {
            lpBuffer = str.c_str();
            nNumberOfBytesToWrite = static_cast<DWORD>(str.length());
        }
        return Real_WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
    }
}

__declspec(dllexport)
BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, PVOID /*lpReserved*/)
{
    plog::init(plog::verbose, "c:\\DeviareHook.log");

    static DeviareProcessor g_processor;
    if (g_processor.NeedSkip())
    {
        LOGV << "Skip process DllMain";
        return TRUE;
    }
    try
    {
        switch (dwReason)
        {
            case DLL_PROCESS_ATTACH:
            {
                g_processor.Override(&reinterpret_cast<PVOID&>(Real_WriteFile), Mine_WriteFile);
                g_processor.AttachHooks();
            }
            break;
            case DLL_PROCESS_DETACH:
            {
                g_processor.DetachHooks();
            }
            break;
        }
    }
    catch (const std::exception& ex)
    {
        LOGE << ex.what();
        return FALSE;
    }
    return TRUE;
}