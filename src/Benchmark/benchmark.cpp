#include "pch.h"
#include "HookEngineLoader.h"

using namespace std::chrono_literals;

extern "C"
{
#pragma optimize( "", off )
    BOOL(WINAPI * Real_ReadFile)(
        HANDLE       hFile,
        LPVOID       lpBuffer,
        DWORD        nNumberOfBytesToRead,
        LPDWORD      lpNumberOfBytesRead,
        LPOVERLAPPED lpOverlapped
    ) = ReadFile;

    BOOL WINAPI Mine_ReadFile(
        HANDLE       hFile,
        LPVOID       lpBuffer,
        DWORD        nNumberOfBytesToRead,
        LPDWORD      lpNumberOfBytesRead,
        LPOVERLAPPED lpOverlapped
    )
    {
        return Real_ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
    }
#pragma optimize( "", on )
}

const char g_separator[] = ",";

using HookEngineLoaders = std::vector<HookEngineLoader>;
HookEngineLoaders LoadAllEngines()
{ 
    auto namesOfPlugins = {"DetoursHook.dll", "DeviareHook.dll", "MHookHook.dll", };
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
auto g_hookMap = HookMapT{ { &reinterpret_cast<PVOID&>(Real_ReadFile), Mine_ReadFile } };

double TestFunc()
{
    auto startTime = std::chrono::high_resolution_clock::now();
    int count = 10000000;
    for (auto i = 0; i < count; ++i)
    {
        ::ReadFile(NULL, NULL, 0, NULL, NULL);
    }
    auto timePassed = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(std::chrono::high_resolution_clock::now() - startTime);
    return timePassed.count() / count;
}

void TestCalls()
{
    TestFunc();// ignore first result
    auto withoutHook = TestFunc();
    for (int i = 0; i < 100; ++i)
    {
        std::cout << i;
        for (const auto& hookEngineLoader : g_hookEngineLoaders) try
        {
            auto& engine = hookEngineLoader.GetEngine();
            DllProcessor(engine, g_hookMap, DLL_PROCESS_ATTACH);
            auto withHook = TestFunc();
            DllProcessor(engine, g_hookMap, DLL_PROCESS_DETACH);
            std::cout << g_separator << withHook - withoutHook;
        }
        catch (const std::exception& ex)
        {
            std::cerr << ex.what() << std::endl;
        }
        std::cout << std::endl;
    }
}

void TestInstallHook()
{
    for (const auto& hookEngineLoader : g_hookEngineLoaders) try
    {
        auto& engine = hookEngineLoader.GetEngine();
        auto startTime = std::chrono::high_resolution_clock::now();
        const int count = 100;
        for (int i = 0; i < count; ++i)
        {
            DllProcessor(engine, g_hookMap, DLL_PROCESS_ATTACH);
            DllProcessor(engine, g_hookMap, DLL_PROCESS_DETACH);
        }
        auto timePassed = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(std::chrono::high_resolution_clock::now() - startTime);
        std::cout << g_separator << timePassed.count() / count;
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
    std::cout << std::endl;
}

void TestInstallHooksWithThreads()
{
    std::vector<std::thread> threadsToTest;

    const int kThreadsCount = 10000;
    const int kThreadsCountStep = 100;
    bool testFinished = false;

    for (int k = 0; k <= kThreadsCount; k += kThreadsCountStep)
    {
        for (int i = 0; i < kThreadsCountStep; ++i)
        {
            threadsToTest.push_back(std::thread([&]()
            {
                while (!testFinished)
                {
                    std::this_thread::sleep_for(10ms);
                }
            }));
        }
        std::cout << k;
        TestInstallHook();
    }

    testFinished = true;

    std::for_each(threadsToTest.begin(), threadsToTest.end(), [](auto& thread) {thread.join(); });
    std::cout << std::endl;
}

void PrintHeader(const char* testName)
{
    std::cout << testName;
    for (const auto& hookEngineLoader : g_hookEngineLoaders)
    {
        auto& engine = hookEngineLoader.GetEngine();
        std::cout << g_separator << engine.GetName();
    }
    std::cout << std::endl;
}

int main()
{
    PrintHeader("TestCalls");
    TestCalls();
    PrintHeader("TestInstallHooksWithThreads");
    TestInstallHooksWithThreads();
    return 0;
}
