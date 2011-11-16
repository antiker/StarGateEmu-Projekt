/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef _AUTH_SHA1_H
#define _AUTH_SHA1_H

#include "Common.h"
#include <openssl/sha.h>
#include <openssl/crypto.h>

class BigNumber;

class SHA1Hash
{
    public:
        SHA1Hash();
        ~SHA1Hash();

        void UpdateFinalizeBigNumbers(BigNumber *bn0, ...);
        void UpdateBigNumbers(BigNumber *bn0, ...);

        void UpdateData(const uint8 *dta, int len);
        void UpdateData(const std::string &str);

        void Initialize();
        void Finalize();

        uint8 *GetDigest(void) { return mDigest; };
        int GetLength(void) const { return SHA_DIGEST_LENGTH; };

    private:
        SHA_CTX mC;
        uint8 mDigest[SHA_DIGEST_LENGTH];
};
#endif