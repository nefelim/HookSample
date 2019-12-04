#include "pch.h"
#include "DeviareProcessor.h"

bool DeviareProcessor::NeedSkip()
{
    return false;
}

void DeviareProcessor::Override(void **origFn, void* trapFn)
{
    m_hookInfos.emplace_back(CNktHookLib::HOOK_INFO{ m_hookInfos.size(), *origFn, trapFn, nullptr });
}

void DeviareProcessor::ProcessAll(DWORD dwReason)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH: 
        {
            AttachHooks();
        }
        break;
        case DLL_PROCESS_DETACH:
        {
            DetachHooks();
        }
        break;
    }
}

void DeviareProcessor::AttachHooks()
{
    CHECK_WIN32(m_nktHook.Hook(m_hookInfos.data(), m_hookInfos.size(), NKTHOOKLIB_DisallowReentrancy));
}

void DeviareProcessor::DetachHooks()
{
    CHECK_WIN32(m_nktHook.Unhook(m_hookInfos.data(), m_hookInfos.size()));
}