#include "pch.h"
#include "DeviareProcessor.h"

bool DeviareProcessor::NeedSkip() const
{
    return false;
}

void DeviareProcessor::Override(void **origFn, void* trapFn)
{
    m_hookInfos.emplace_back(CNktHookLib::HOOK_INFO{ m_hookInfos.size(), *origFn, trapFn, nullptr });
}

void DeviareProcessor::AttachHooks()
{
    CHECK_WIN32(m_nktHook.Hook(m_hookInfos.data(), m_hookInfos.size(), NKTHOOKLIB_DisallowReentrancy));
}

void DeviareProcessor::DetachHooks()
{
    if (m_hookInfos.empty())
    {
        return;
    }
    CHECK_WIN32(m_nktHook.Unhook(m_hookInfos.data(), m_hookInfos.size()));
    m_hookInfos.clear();
}