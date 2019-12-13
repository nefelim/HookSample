#pragma once
#include "HookProcessor.h"

class MHookProcessor : public IHookProcessor
{
public:
    const char* GetName() const override;
    bool NeedSkip() const override;
    void Override(void **origFn, void* trapFn) override;
    void AttachHooks() override;
    void DetachHooks() override;
private:
    using FunctionMapT = std::vector<HOOK_INFO>;
    FunctionMapT m_functionMap;
};
