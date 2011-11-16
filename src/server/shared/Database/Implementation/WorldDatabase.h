/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef _WORLDDATABASE_H
#define _WORLDDATABASE_H

#include "DatabaseWorkerPool.h"
#include "MySQLConnection.h"

class WorldDatabaseConnection : public MySQLConnection
{
    public:
        //- Constructors for sync and async connections
        WorldDatabaseConnection(MySQLConnectionInfo& connInfo) : MySQLConnection(connInfo) {}
        WorldDatabaseConnection(ACE_Activation_Queue* q, MySQLConnectionInfo& connInfo) : MySQLConnection(q, connInfo) {}

        //- Loads database type specific prepared statements
        void DoPrepareStatements();
};

typedef DatabaseWorkerPool<WorldDatabaseConnection> WorldDatabaseWorkerPool;

enum WorldDatabaseStatements
{
    /*  Naming standard for defines:
        {DB}_{SET/DEL/ADD/REP}_{Summary of data changed}
        When updating more than one field, consider looking at the calling function
        name for a suiting suffix.
    */

    WORLD_LOAD_QUEST_POOLS,
    WORLD_DEL_CRELINKED_RESPAWN,
    WORLD_REP_CRELINKED_RESPAWN,
    WORLD_LOAD_CRETEXT,
    WORLD_LOAD_SMART_SCRIPTS,
    WORLD_LOAD_SMARTAI_WP,

    MAX_WORLDDATABASE_STATEMENTS,
};

#endif