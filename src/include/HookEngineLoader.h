#pragma once
#include "HookProcessor.h"

class HookEngineLoader
{
public:
    HookEngineLoader(LPCSTR fileName)
    {
        m_hModule = ::LoadLibraryA(fileName);
        THROW_LAST_ERRNO_IF(m_hModule == NULL);
    }

    IHookProcessor& GetEngine() const
    {
        auto getIntance = reinterpret_cast<GetIntanceFn>(::GetProcAddress(m_hModule, "GetInstance"));
        THROW_LAST_ERRNO_IF(getIntance == NULL);
        return getIntance();
    }

    ~HookEngineLoader()
    {
        auto res = ::FreeLibrary(m_hModule);
        LOGE_IF(res) << "Can't free library! LastError = " << ::GetLastError();
    }
private:
    HMODULE m_hModule;
};