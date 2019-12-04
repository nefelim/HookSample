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
static DeviareProcessor processor;

__declspec(dllexport)
BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, PVOID /*lpReserved*/)
{
    plog::init(plog::verbose, "c:\\DeviareHook.log");
    
    if (processor.NeedSkip())
    {
        LOGV << "Skip process DllMain";
        return TRUE;
    }
    try
    {
        processor.Override(&reinterpret_cast<PVOID&>(Real_WriteFile), Mine_WriteFile);
        processor.ProcessAll(dwReason);
    }
    catch (const std::exception& ex)
    {
        LOGE << ex.what();
        return FALSE;
    }
    return TRUE;
}