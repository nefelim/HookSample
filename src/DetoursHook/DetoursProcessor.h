#pragma once

class DetoursProcessor
{
public:
    static bool NeedSkip();
    void Override(void **origFn, void* trapFn);
    void AttachHooks();
    void DetachHooks();
private:
    using FunctionMapT = std::map<void*, void**>;
    FunctionMapT m_functionMap;
};
