/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef _LOGINDATABASE_H
#define _LOGINDATABASE_H

#include "DatabaseWorkerPool.h"
#include "MySQLConnection.h"

class LoginDatabaseConnection : public MySQLConnection
{
    public:
        //- Constructors for sync and async connections
        LoginDatabaseConnection(MySQLConnectionInfo& connInfo) : MySQLConnection(connInfo) {}
        LoginDatabaseConnection(ACE_Activation_Queue* q, MySQLConnectionInfo& connInfo) : MySQLConnection(q, connInfo) {}

        //- Loads databasetype specific prepared statements
        void DoPrepareStatements();
};

typedef DatabaseWorkerPool<LoginDatabaseConnection> LoginDatabaseWorkerPool;

enum LoginDatabaseStatements
{
    /*  Naming standard for defines:
        {DB}_{SET/DEL/ADD/REP}_{Summary of data changed}
        When updating more than one field, consider looking at the calling function
        name for a suiting suffix.
    */

    LOGIN_GET_REALMLIST,
    LOGIN_SET_EXPIREDIPBANS,
    LOGIN_SET_EXPIREDACCBANS,
    LOGIN_GET_IPBANNED,
    LOGIN_SET_IPAUTOBANNED,
    LOGIN_GET_ACCBANNED,
    LOGIN_SET_ACCAUTOBANNED,
    LOGIN_GET_SESSIONKEY,
    LOGIN_SET_VS,
    LOGIN_SET_LOGONPROOF,
    LOGIN_GET_LOGONCHALLENGE,
    LOGIN_SET_FAILEDLOGINS,
    LOGIN_GET_FAILEDLOGINS,
    LOGIN_GET_ACCIDBYNAME,
    LOGIN_GET_NUMCHARSONREALM,
    LOGIN_GET_ACCOUNT_BY_IP,
    LOGIN_SET_IP_BANNED,
    LOGIN_SET_IP_NOT_BANNED,
    LOGIN_SET_ACCOUNT_BANNED,
    LOGIN_SET_ACCOUNT_NOT_BANNED,

    MAX_LOGINDATABASE_STATEMENTS,
};

#endif