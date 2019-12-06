#include "pch.h"
#include "DetoursProcessor.h"
#include "DetoursTransaction.h"

bool DetoursProcessor::NeedSkip() const
{
    return ::DetourIsHelperProcess();
}

void DetoursProcessor::Override(void **origFn, void* trapFn)
{
    m_functionMap[trapFn] = origFn;
}

void DetoursProcessor::AttachHooks()
{
    THROW_LAST_WIN32_IF(!::DetourRestoreAfterWith());
    DetoursTransaction transaction;
    for (auto fn : m_functionMap)
    {
        CHECK_WIN32(::DetourAttach(fn.second, fn.first));
    }
}

void DetoursProcessor::DetachHooks()
{
    DetoursTransaction transaction;
    for (auto fn : m_functionMap)
    {
        CHECK_WIN32(::DetourDetach(fn.second, fn.first));
    }
}