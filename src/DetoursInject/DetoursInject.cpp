#include "pch.h"

PROCESS_INFORMATION CreateProcessWithDll(const std::wstring processPath, const std::string& dllPath)
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
