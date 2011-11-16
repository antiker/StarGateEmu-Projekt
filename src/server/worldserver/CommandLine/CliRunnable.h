/*
 * Copyright (C) 2010-2011 Project StarGate
 */

/// \addtogroup Trinityd
/// @{
/// \file

#ifndef __CLIRUNNABLE_H
#define __CLIRUNNABLE_H

/// Command Line Interface handling thread
class CliRunnable : public ACE_Based::Runnable
{
    public:
        void run();
};
#endif
/// @}