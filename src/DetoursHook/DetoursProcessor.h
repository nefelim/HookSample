#pragma once
#include <map>

class DetoursProcessor
{
public:
    static PROCESS_INFORMATION CreateProcessWithDll(const std::wstring processPath, const std::string& dllPath);
    DetoursProcessor(HMODULE hDll);
    static bool IsHelperProcess();
    void Override(void **origFn, void* trapFn);
    void ProcessAll(DWORD dwReason);
private:
    void ThreadAttach();
    void ThreadDetach();
    void AttachDetours();
    void DetachDetours();
    void ProcessAttach();
    void ProcessDetach();

private:
    HMODULE m_hDll = 0;
    using FunctionMapT = std::map<void*, void**>;
    FunctionMapT m_functionMap;
};
