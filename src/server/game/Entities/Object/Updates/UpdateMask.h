/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef __UPDATEMASK_H
#define __UPDATEMASK_H

#include "UpdateFields.h"
#include "Errors.h"

class UpdateMask
{
    public:
        UpdateMask() : mCount(0), mBlocks(0), mUpdateMask(0) { }
        UpdateMask(const UpdateMask& mask) : mUpdateMask(0) { *this = mask; }

        ~UpdateMask()
        {
            delete [] mUpdateMask;
        }

        void SetBit (uint32 index)
        {
            ((uint8 *)mUpdateMask)[ index >> 3 ] |= 1 << (index & 0x7);
        }

        void UnsetBit (uint32 index)
        {
            ((uint8 *)mUpdateMask)[ index >> 3 ] &= (0xff ^ (1 <<  (index & 0x7)));
        }

        bool GetBit (uint32 index) const
        {
            return (((uint8 *)mUpdateMask)[ index >> 3 ] & (1 << (index & 0x7))) != 0;
        }

        uint32 GetBlockCount() const { return mBlocks; }
        uint32 GetLength() const { return mBlocks << 2; }
        uint32 GetCount() const { return mCount; }
        uint8* GetMask() { return (uint8*)mUpdateMask; }

        void SetCount (uint32 valuesCount)
        {
            delete [] mUpdateMask;

            mCount = valuesCount;
            mBlocks = (valuesCount + 31) / 32;

            mUpdateMask = new uint32[mBlocks];
            memset(mUpdateMask, 0, mBlocks << 2);
        }

        void Clear()
        {
            if (mUpdateMask)
                memset(mUpdateMask, 0, mBlocks << 2);
        }

        UpdateMask& operator = (const UpdateMask& mask)
        {
            SetCount(mask.mCount);
            memcpy(mUpdateMask, mask.mUpdateMask, mBlocks << 2);

            return *this;
        }

        void operator &= (const UpdateMask& mask)
        {
            ASSERT(mask.mCount <= mCount);
            for (uint32 i = 0; i < mBlocks; ++i)
                mUpdateMask[i] &= mask.mUpdateMask[i];
        }

        void operator |= (const UpdateMask& mask)
        {
            ASSERT(mask.mCount <= mCount);
            for (uint32 i = 0; i < mBlocks; ++i)
                mUpdateMask[i] |= mask.mUpdateMask[i];
        }

        UpdateMask operator & (const UpdateMask& mask) const
        {
            ASSERT(mask.mCount <= mCount);

            UpdateMask newmask;
            newmask = *this;
            newmask &= mask;

            return newmask;
        }

        UpdateMask operator | (const UpdateMask& mask) const
        {
            ASSERT(mask.mCount <= mCount);

            UpdateMask newmask;
            newmask = *this;
            newmask |= mask;

            return newmask;
        }

    private:
        uint32 mCount;
        uint32 mBlocks;
        uint32 *mUpdateMask;
};
#endif