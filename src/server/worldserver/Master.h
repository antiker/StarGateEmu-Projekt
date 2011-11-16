/*
 * Copyright (C) 2010-2011 Project StarGate
 */

/// \addtogroup Trinityd
/// @{
/// \file

#ifndef _MASTER_H
#define _MASTER_H

#include "Common.h"

/// Start the server
class Master
{
    public:
        Master();
        ~Master();
        int Run();

    private:
        bool _StartDB();
        void _StopDB();

        void clearOnlineAccounts();
};

#define sMaster ACE_Singleton<Master, ACE_Null_Mutex>::instance()
#endif
/// @}