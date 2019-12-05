#pragma once

class MHookProcessor
{
public:
    static bool NeedSkip();
    void Override(void **origFn, void* trapFn);
    void AttachHooks();
    void DetachHooks();
private:
    using FunctionMapT = std::vector<HOOK_INFO>;
    FunctionMapT m_functionMap;
};
