#include "pch.h"
#include "DetoursProcessor.h"
#include "DetoursTransaction.h"

bool DetoursProcessor::NeedSkip()
{
    return ::DetourIsHelperProcess();
}

void DetoursProcessor::Override(void **origFn, void* trapFn)
{
    m_functionMap[trapFn] = origFn;
}

void DetoursProcessor::ProcessAll(DWORD dwReason)
{
    switch (dwReason)
    {
        case DLL_PROCESS_ATTACH: 
        {
            THROW_LAST_WIN32_IF(!::DetourRestoreAfterWith());
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

void DetoursProcessor::AttachHooks()
{
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