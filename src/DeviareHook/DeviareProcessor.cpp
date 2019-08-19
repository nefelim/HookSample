#include "pch.h"
#include "DeviareProcessor.h"
//#include <NktHookLib.h>

bool DeviareProcessor::NeedSkip()
{
    return false;
}

void DeviareProcessor::Override(void **origFn, void* trapFn)
{
    m_functionMap[trapFn] = origFn;
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
    for (auto fn : m_functionMap)
    {
    }
}

void DeviareProcessor::DetachHooks()
{
    for (auto fn : m_functionMap)
    {
    }
}