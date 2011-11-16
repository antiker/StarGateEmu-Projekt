/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef _AUTHCRYPT_H
#define _AUTHCRYPT_H

#include <Common.h>
#include "Cryptography/ARC4.h"

class BigNumber;

class AuthCrypt
{
    public:
        AuthCrypt();
        ~AuthCrypt();

        void Init(BigNumber *K);
        void DecryptRecv(uint8 *, size_t);
        void EncryptSend(uint8 *, size_t);

        bool IsInitialized() const { return _initialized; }

    private:
        ARC4 _clientDecrypt;
        ARC4 _serverEncrypt;
        bool _initialized;
};
#endif