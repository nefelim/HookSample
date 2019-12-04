#include "pch.h"
#include "DetoursInject.h"
using tstring = std::basic_string<TCHAR, std::char_traits<TCHAR>, std::allocator<TCHAR>>;

PROCESS_INFORMATION CreateProcessWithDll(LPCTSTR processPath, LPCSTR dllPath)
{
    DWORD dwFlags = CREATE_DEFAULT_ERROR_MODE;
    STARTUPINFO si = {};
    PROCESS_INFORMATION pi = {};
    tstring path = processPath;

    THROW_WIN32_IF(!::DetourCreateProcessWithDllEx(
                                                    NULL
                                                    , const_cast<LPTSTR>(path.c_str())
                                                    , NULL
                                                    , NULL
                                                    , TRUE
                                                    , dwFlags
                                                    , NULL
                                                    , NULL
                                                    , &si
                                                    , &pi
                                                    , dllPath
                                                    , NULL
                                                )
                    , ERROR_INTERNAL_ERROR);
    return pi;
}
