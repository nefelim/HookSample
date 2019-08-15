#include "pch.h"

int main()
{
    DetoursProcessor::CreateProcessWithDll(_T("HelloWorld.exe"), "DetoursHook.dll");
    DWORD error = ::ResumeThread(pi.hThread);
    error = ::WaitForSingleObject(pi.hProcess, INFINITE);
}