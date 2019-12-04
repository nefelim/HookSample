#include "pch.h"
#include "DetoursInject.h"

int main()
{
    auto namesOfPlugins = {"MHookHook.dll", "DetoursHook.dll", "DeviareHook.dll"};
    for (auto name : namesOfPlugins) try
    {
        auto pi = CreateProcessWithDll(_T("HelloWorld.exe"), name);
        CHECK_WIN32(::ResumeThread(pi.hThread));
        CHECK_WIN32(::WaitForSingleObject(pi.hProcess, INFINITE));
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}