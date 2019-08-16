#include "pch.h"
#include "DetoursProcessor.h"

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
        std::string str = "Hello Detours Hook!";
        if (hFile == hCout)
        {
            lpBuffer = &str[0];
            nNumberOfBytesToWrite = static_cast<DWORD>(str.length()) + 1;
        }
        return Real_WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
    }
}

__declspec(dllexport)
BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, PVOID /*lpReserved*/)
{
    plog::init(plog::verbose, "c:\\DetoursHook.log");
    DetoursProcessor processor;
    if (processor.IsHelperProcess())
    {
        LOGV << "IsHelperProcess is TRUE";
        return TRUE;
    }
    try
    {
        processor.Override(&(PVOID&)Real_WriteFile, Mine_WriteFile);
        processor.ProcessAll(dwReason);
    }
    catch (const std::exception& ex)
    {
        LOGE << ex.what();
        return FALSE;
    }
    return TRUE;
}