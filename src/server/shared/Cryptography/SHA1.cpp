/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#include "SHA1.h"
#include "BigNumber.h"
#include <stdarg.h>

SHA1Hash::SHA1Hash()
{
    SHA1_Init(&mC);
}

SHA1Hash::~SHA1Hash()
{
    SHA1_Init(&mC);
}

void SHA1Hash::UpdateData(const uint8 *dta, int len)
{
    SHA1_Update(&mC, dta, len);
}

void SHA1Hash::UpdateData(const std::string &str)
{
    UpdateData((uint8 const*)str.c_str(), str.length());
}

void SHA1Hash::UpdateBigNumbers(BigNumber *bn0, ...)
{
    va_list v;
    BigNumber *bn;

    va_start(v, bn0);
    bn = bn0;
    while (bn)
    {
        UpdateData(bn->AsByteArray(), bn->GetNumBytes());
        bn = va_arg(v, BigNumber *);
    }
    va_end(v);
}

void SHA1Hash::Initialize()
{
    SHA1_Init(&mC);
}

void SHA1Hash::Finalize(void)
{
    SHA1_Final(mDigest, &mC);
}