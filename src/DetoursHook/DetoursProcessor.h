#pragma once
#include <map>

class DetoursProcessor
{
public:
    static bool IsHelperProcess();
    void Override(void **origFn, void* trapFn);
    void ProcessAll(DWORD dwReason);
private:
    void AttachDetours();
    void DetachDetours();
private:
    using FunctionMapT = std::map<void*, void**>;
    FunctionMapT m_functionMap;
};
