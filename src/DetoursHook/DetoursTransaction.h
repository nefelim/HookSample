#pragma once

class DetoursTransaction
{
public:
    DetoursTransaction()
    {
        LONG error = ::DetourTransactionBegin();
        THROW_WIN32_IF(error, error);
        error = ::DetourUpdateThread(GetCurrentThread());
        THROW_WIN32_IF(error, error);
    }
    ~DetoursTransaction()
    {
        ::DetourTransactionCommit();
    }
};

