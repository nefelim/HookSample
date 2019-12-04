#pragma once
#include <processthreadsapi.h>

PROCESS_INFORMATION CreateProcessWithDll(LPCTSTR processPath, LPCSTR dllPath);