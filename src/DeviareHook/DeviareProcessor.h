#pragma once
#include <vector>
#include <NktHookLib.h>
#include "HookProcessor.h"

class DeviareProcessor : public IHookProcessor
{
public:
    bool NeedSkip() const override;
    void Override(void **origFn, void* trapFn) override;
    void AttachHooks() override;
    void DetachHooks() override;
private:
    using HookInfosT = std::vector<CNktHookLib::HOOK_INFO>;
    HookInfosT m_hookInfos;
    CNktHookLib m_nktHook;
};
