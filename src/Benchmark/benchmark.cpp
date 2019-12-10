#include "pch.h"
#include <iostream>
#include "HookEngineLoader.h"

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
        return Real_WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
    }
}

using HookEngineLoaders = std::vector<HookEngineLoader>;
HookEngineLoaders LoadAllEngines()
{ 
    auto namesOfPlugins = { "MHookHook.dll", "DetoursHook.dll", "DeviareHook.dll"};
    HookEngineLoaders hookEngineLoaders;
    hookEngineLoaders.reserve(namesOfPlugins.size());
    for (auto name : namesOfPlugins) try
    {
        hookEngineLoaders.emplace_back(name);
        hookEngineLoaders.back().GetEngine().DetachHooks();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    return hookEngineLoaders;
}

auto g_hookEngineLoaders = LoadAllEngines();
auto g_hookMap = HookMapT{ { &reinterpret_cast<PVOID&>(Real_WriteFile), Mine_WriteFile } };

int main()
{
    for (const auto& hookEngineLoader : g_hookEngineLoaders) try
    {
        auto& engine = hookEngineLoader.GetEngine();
        DllProcessor(engine, g_hookMap, DLL_PROCESS_ATTACH);
        ::WriteFile(NULL, NULL, 0, NULL, NULL);
        DllProcessor(engine, g_hookMap, DLL_PROCESS_DETACH);
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    return 0;
}
