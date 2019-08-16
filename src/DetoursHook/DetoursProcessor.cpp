#include "pch.h"
#include "DetoursProcessor.h"
#include "DetoursTransaction.h"

bool DetoursProcessor::IsHelperProcess()
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
            AttachDetours();
        }
        break;
        case DLL_PROCESS_DETACH:
        {
            DetachDetours();
        }
        break;
    }
}

void DetoursProcessor::AttachDetours()
{
    DetoursTransaction transaction;
    LONG error = NO_ERROR;
    for (auto fn : m_functionMap)
    {
        error = ::DetourAttach(fn.second, fn.first);
        THROW_WIN32_IF(error, error);
    }
}

void DetoursProcessor::DetachDetours()
{
    DetoursTransaction transaction;
    LONG error = NO_ERROR;
    for (auto fn : m_functionMap)
    {
        error = ::DetourDetach(fn.second, fn.first);
        THROW_WIN32_IF(error, error);
    }
}