/*
 * Copyright (C) 2010-2011 Project StarGate
 */

/// \addtogroup u2w
/// @{
/// \file

#ifndef TRINITY_WORLDLOG_H
#define TRINITY_WORLDLOG_H

#include "Common.h"
#include <ace/Singleton.h>
#include "Errors.h"

#include <stdarg.h>

/// %Log packets to a file
class WorldLog
{
    friend class ACE_Singleton<WorldLog, ACE_Thread_Mutex>;
    WorldLog();
    WorldLog(const WorldLog &);
    WorldLog& operator=(const WorldLog &);
    ACE_Thread_Mutex Lock;

    /// Close the file in destructor
    ~WorldLog();

    public:
        void Initialize();
        /// Is the world logger active?
        bool LogWorld(void) const { return (i_file != NULL); }
        /// %Log to the file
        void outLog(char const *fmt, ...);
        void outTimestampLog(char const *fmt, ...);

    private:
        FILE *i_file;

        bool m_dbWorld;
};

#define sWorldLog ACE_Singleton<WorldLog, ACE_Thread_Mutex>::instance()
#endif
/// @}