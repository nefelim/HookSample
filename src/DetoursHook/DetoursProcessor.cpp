#include "pch.h"
#include "DetoursProcessor.h"
#include "DetoursTransaction.h"

static LONG s_nTlsIndent = -1;
static LONG s_nTlsThread = -1;
static LONG s_nThreadCnt = 0;

PROCESS_INFORMATION DetoursProcessor::CreateProcessWithDll(const std::wstring processPath, const std::string& dllPath)
{
    DWORD dwFlags = CREATE_DEFAULT_ERROR_MODE;
    STARTUPINFO si = {};
    PROCESS_INFORMATION pi = {};

    auto res = ::DetourCreateProcessWithDllEx(NULL,
        const_cast<LPWSTR>(processPath.data()), NULL, NULL, TRUE,
        dwFlags, NULL, NULL, &si, &pi,
        &dllPath[0], NULL);
    return pi;
}

DetoursProcessor::DetoursProcessor(HMODULE hDll)
    : m_hDll(hDll)
{
}

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
        case DLL_PROCESS_ATTACH: ProcessAttach(); break;
        case DLL_PROCESS_DETACH: ProcessDetach(); break;
        case DLL_THREAD_ATTACH:  ThreadAttach(); break;
        case DLL_THREAD_DETACH:  ThreadDetach(); break;
    }
}

void DetoursProcessor::ThreadAttach()
{
    if (s_nTlsIndent >= 0)
    {
        TlsSetValue(s_nTlsIndent, NULL);
    }
    if (s_nTlsThread >= 0)
    {
        LONG nThread = InterlockedIncrement(&s_nThreadCnt);
        TlsSetValue(s_nTlsThread, (PVOID)(LONG_PTR)nThread);
    }
}

void DetoursProcessor::ThreadDetach()
{
    if (s_nTlsIndent >= 0)
    {
        TlsSetValue(s_nTlsIndent, NULL);
    }
    if (s_nTlsThread >= 0)
    {
        TlsSetValue(s_nTlsThread, NULL);
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

void DetoursProcessor::ProcessAttach()
{
    THROW_LAST_WIN32_IF(!::DetourRestoreAfterWith());
    s_nTlsIndent = TlsAlloc();
    s_nTlsThread = TlsAlloc();

    AttachDetours();
    ThreadAttach();
}

void DetoursProcessor::ProcessDetach()
{
    ThreadDetach();
    DetachDetours();

    if (s_nTlsIndent >= 0)
    {
        TlsFree(s_nTlsIndent);
    }
    if (s_nTlsThread >= 0)
    {
        TlsFree(s_nTlsThread);
    }
}
