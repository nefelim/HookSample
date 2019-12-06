#pragma once
#include "HookProcessor.h"

class DetoursProcessor : public IHookProcessor
{
public:
    bool NeedSkip() const override;
    void Override(void **origFn, void* trapFn) override;
    void AttachHooks() override;
    void DetachHooks() override;
private:
    using FunctionMapT = std::map<void*, void**>;
    FunctionMapT m_functionMap;
};
