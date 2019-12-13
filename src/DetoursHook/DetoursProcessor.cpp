#include "pch.h"
#include "DetoursProcessor.h"
#include "DetoursTransaction.h"

const char* DetoursProcessor::GetName() const
{
    return "Detours";
}

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
    ::DetourRestoreAfterWith();//Not checked
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
    m_functionMap.clear();
}