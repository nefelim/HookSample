#include "pch.h"
#include "DetoursInject.h"

int main()
{
    auto pi = CreateProcessWithDll(_T("HelloWorld.exe"), "MHookHook.dll"/*"DetoursHook.dll"*/);
    DWORD error = ::ResumeThread(pi.hThread);
    error = ::WaitForSingleObject(pi.hProcess, INFINITE);
}