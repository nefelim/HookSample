#pragma once
#include <map>

class MHookProcessor
{
public:
    static bool NeedSkip();
    void Override(void **origFn, void* trapFn);
    void ProcessAll(DWORD dwReason);
private:
    void AttachHooks();
    void DetachHooks();
private:
    using FunctionMapT = std::vector<HOOK_INFO>;
    FunctionMapT m_functionMap;
};
