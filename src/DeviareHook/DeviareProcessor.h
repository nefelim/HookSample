#pragma once
#include <vector>
#include <NktHookLib.h>

class DeviareProcessor
{
public:
    static bool NeedSkip();
    void Override(void **origFn, void* trapFn);
    void AttachHooks();
    void DetachHooks();
private:
    using HookInfosT = std::vector<CNktHookLib::HOOK_INFO>;
    HookInfosT m_hookInfos;
    CNktHookLib m_nktHook;
};
