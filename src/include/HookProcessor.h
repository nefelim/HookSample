#pragma once
#include <memory>
#include <vector>
#include <plog/Log.h>

class IHookProcessor
{
public:
    virtual ~IHookProcessor() {}
    virtual const char* GetName() const = 0;
    virtual bool NeedSkip() const = 0;
    virtual void Override(void **origFn, void* trapFn) = 0;
    virtual void AttachHooks() = 0;
    virtual void DetachHooks() = 0;
};

using GetIntanceFn = IHookProcessor & (*)();
using HookMapT = std::vector<std::pair<void**, void*> >; //orig -> mine

inline bool DllProcessor(IHookProcessor& processor, HookMapT& functions, DWORD dwReason)
{
    if (processor.NeedSkip())
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
                for (auto& function : functions)
                {
                    processor.Override(function.first, function.second);
                }
                processor.AttachHooks();
            }
            break;
            case DLL_PROCESS_DETACH:
            {
                processor.DetachHooks();
            }
            break;
        }
    }
    catch (const std::exception& ex)
    {
        LOGE << ex.what();
        return false;
    }
    return true;
}