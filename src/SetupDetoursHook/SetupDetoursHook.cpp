#include "pch.h"
#include "DetoursInject.h"

int main()
{
    auto pi = CreateProcessWithDll(_T("HelloWorld.exe"), "DetoursHook.dll");
    DWORD error = ::ResumeThread(pi.hThread);
    error = ::WaitForSingleObject(pi.hProcess, INFINITE);
}