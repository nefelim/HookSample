#pragma once

class DetoursTransaction
{
public:
    DetoursTransaction()
    {
        CHECK_WIN32(::DetourTransactionBegin());
        CHECK_WIN32(::DetourUpdateThread(GetCurrentThread()));
    }
    ~DetoursTransaction()
    {
        ::DetourTransactionCommit();
    }
};

