#include "pch.h"
#include "MHookProcessor.h"

const char* MHookProcessor::GetName() const
{
    return "MHook";
}

bool MHookProcessor::NeedSkip() const
{
    return false;
}

void MHookProcessor::Override(void** origFn, void* trapFn)
{
    m_functionMap.emplace_back(HOOK_INFO{ origFn, trapFn });
}

void MHookProcessor::AttachHooks()
{
    auto size = static_cast<int>(m_functionMap.size());
    THROW_WIN32_IF(::Mhook_SetHookEx(m_functionMap.data(), size) != size, ERROR_INTERNAL_ERROR);
}

void MHookProcessor::DetachHooks()
{
    std::vector<void**> functions;
    std::transform(m_functionMap.begin(), m_functionMap.end(), std::back_inserter(functions), 
        [](const HOOK_INFO& info) {return info.ppSystemFunction; });
    int size = static_cast<int>(functions.size());

    THROW_WIN32_IF(::Mhook_UnhookEx(functions.data(), size) != size, ERROR_INTERNAL_ERROR);
    m_functionMap.clear();
}