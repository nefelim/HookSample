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
        std::string str = "Hello Detours Hook!\n";
        if (hFile == hCout)
        {
            lpBuffer = str.c_str();
            nNumberOfBytesToWrite = static_cast<DWORD>(str.length());
        }
        return Real_WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
    }

    __declspec(dllexport)
    IHookProcessor& GetInstance()
    {
        static DetoursProcessor processor;
        return processor;
    }
}

__declspec(dllexport)
BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, PVOID /*lpReserved*/)
{
    plog::init(plog::verbose, "c:\\DetoursHook.log");

    auto& processor = GetInstance();
    auto hookMap = HookMapT{ { &reinterpret_cast<PVOID&>(Real_WriteFile), Mine_WriteFile } };
    return DllProcessor(processor, hookMap, dwReason);
}