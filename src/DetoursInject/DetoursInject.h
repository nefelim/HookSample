#pragma once
#include <string>
#include <processthreadsapi.h>

PROCESS_INFORMATION CreateProcessWithDll(const std::wstring processPath, const std::string& dllPath);