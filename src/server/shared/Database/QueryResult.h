/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef QUERYRESULT_H
#define QUERYRESULT_H

#include <ace/Refcounted_Auto_Ptr.h>
#include <ace/Thread_Mutex.h>

#include "Field.h"
#include "Log.h"

#ifdef _WIN32
  #include <winsock2.h>
#endif
#include <mysql.h>

class ResultSet
{
    public:
        ResultSet(MYSQL_RES *result, MYSQL_FIELD *fields, uint64 rowCount, uint32 fieldCount);
        ~ResultSet();

        bool NextRow();
        uint64 GetRowCount() const { return m_rowCount; }
        uint32 GetFieldCount() const { return m_fieldCount; }

        Field *Fetch() const { return m_currentRow; }
        const Field & operator [] (uint32 index) const
        {
            ASSERT(index < m_fieldCount);
            return m_currentRow[index];
        }

    protected:
        Field *m_currentRow;
        uint64 m_rowCount;
        uint32 m_fieldCount;

    private:
        void CleanUp();
        MYSQL_RES *m_result;
        MYSQL_FIELD *m_fields;
};

typedef ACE_Refcounted_Auto_Ptr<ResultSet, ACE_Thread_Mutex> QueryResult;

class PreparedResultSet
{
    public:
        PreparedResultSet(MYSQL_STMT* stmt, MYSQL_RES *result, uint64 rowCount, uint32 fieldCount);
        ~PreparedResultSet();

        bool NextRow();
        uint64 GetRowCount() const { return m_rowCount; }
        uint32 GetFieldCount() const { return m_fieldCount; }

        Field* Fetch() const
        {
            ASSERT(m_rowPosition < m_rowCount);
            return m_rows[uint32(m_rowPosition)];
        }

        const Field & operator [] (uint32 index) const
        {
            ASSERT(m_rowPosition < m_rowCount);
            ASSERT(index < m_fieldCount);
            return m_rows[uint32(m_rowPosition)][index];
        }

    protected:
        uint64 m_rowCount;
        uint64 m_rowPosition;
        std::vector<Field*> m_rows;
        uint32 m_fieldCount;

    private:
        MYSQL_BIND* m_rBind;
        MYSQL_STMT* m_stmt;
        MYSQL_RES* m_res;

        my_bool* m_isNull;
        unsigned long* m_length;

        void FreeBindBuffer();
        void CleanUp();
        bool _NextRow();
};

typedef ACE_Refcounted_Auto_Ptr<PreparedResultSet, ACE_Thread_Mutex> PreparedQueryResult;

#endif