/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#include "gamePCH.h"
/** \file
    \ingroup u2w
*/

#include "WorldLog.h"
#include "Config.h"
#include "Log.h"
#include "DatabaseWorkerPool.h"

WorldLog::WorldLog() : i_file(NULL)
{
    Initialize();
}

WorldLog::~WorldLog()
{
    if (i_file != NULL)
        fclose(i_file);
    i_file = NULL;
}

/// Open the log file (if specified so in the configuration file)
void WorldLog::Initialize()
{
    std::string logsDir = sConfig->GetStringDefault("LogsDir", "");

    if (!logsDir.empty())
    {
        if ((logsDir.at(logsDir.length()-1) != '/') && (logsDir.at(logsDir.length()-1) != '\\'))
            logsDir.append("/");
    }

    std::string logname = sConfig->GetStringDefault("WorldLogFile", "");
    if (!logname.empty())
    {
        i_file = fopen((logsDir+logname).c_str(), "w");
    }

    m_dbWorld = sConfig->GetBoolDefault("LogDB.World", false); // can be VERY heavy if enabled
}

void WorldLog::outTimestampLog(char const *fmt, ...)
{
    if (LogWorld())
    {
        ACE_GUARD(ACE_Thread_Mutex, Guard, Lock);
        ASSERT(i_file);

        Log::outTimestamp(i_file);
        va_list args;
        va_start(args, fmt);
        vfprintf(i_file, fmt, args);
        //fprintf(i_file, "\n");
        va_end(args);

        fflush(i_file);
    }

    if (sLog->GetLogDB() && m_dbWorld)
    {
        va_list ap2;
        va_start(ap2, fmt);
        char nnew_str[MAX_QUERY_LEN];
        vsnprintf(nnew_str, MAX_QUERY_LEN, fmt, ap2);
        sLog->outDB(LOG_TYPE_WORLD, nnew_str);
        va_end(ap2);
    }
}

void WorldLog::outLog(char const *fmt, ...)
{
    if (LogWorld())
    {
        ACE_GUARD(ACE_Thread_Mutex, Guard, Lock);
        ASSERT(i_file);

        va_list args;
        va_start(args, fmt);
        vfprintf(i_file, fmt, args);
        //fprintf(i_file, "\n");
        va_end(args);

        fflush(i_file);
    }

    if (sLog->GetLogDB() && m_dbWorld)
    {
        va_list ap2;
        va_start(ap2, fmt);
        char nnew_str[MAX_QUERY_LEN];
        vsnprintf(nnew_str, MAX_QUERY_LEN, fmt, ap2);
        sLog->outDB(LOG_TYPE_WORLD, nnew_str);
        va_end(ap2);
    }
}