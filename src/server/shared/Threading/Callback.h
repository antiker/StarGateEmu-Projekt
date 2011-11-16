/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef _CALLBACK_H
#define _CALLBACK_H

#include <ace/Future.h>
#include <ace/Future_Set.h>
#include "QueryResult.h"

typedef ACE_Future<QueryResult> QueryResultFuture;
typedef ACE_Future<PreparedQueryResult> PreparedQueryResultFuture;

/*! A simple template using ACE_Future to manage callbacks from the thread and object that
    issued the request. <ParamType> is variable type of parameter that is used as parameter
    for the callback function.
*/
template <typename Result, typename ParamType>
class QueryCallback
{
    public:
        QueryCallback() {}

        void SetFutureResult(ACE_Future<Result> value)
        {
            result = value;
        }

        ACE_Future<Result> GetFutureResult()
        {
            return result;
        }

        int IsReady()
        {
            return result.ready();
        }

        void GetResult(Result& res)
        {
            result.get(res);
        }

        void FreeResult()
        {
            result.cancel();
        }

        void SetParam(ParamType value)
        {
            param = value;
        }

        ParamType GetParam()
        {
            return param;
        }

    private:
        ACE_Future<Result> result;
        ParamType param;
};

template <typename Result, typename ParamType1, typename ParamType2>
class QueryCallback_2
{
    public:
        QueryCallback_2() {}

        void SetFutureResult(ACE_Future<Result> value)
        {
            result = value;
        }

        ACE_Future<Result> GetFutureResult()
        {
            return result;
        }

        int IsReady()
        {
            return result.ready();
        }

        void GetResult(Result& res)
        {
            result.get(res);
        }

        void FreeResult()
        {
            result.cancel();
        }

        void SetFirstParam(ParamType1 value)
        {
            param_1 = value;
        }

        void SetSecondParam(ParamType2 value)
        {
            param_2 = value;
        }

        ParamType1 GetFirstParam()
        {
            return param_1;
        }

        ParamType2 GetSecondParam()
        {
            return param_2;
        }

    private:
        ACE_Future<Result> result;
        ParamType1 param_1;
        ParamType2 param_2;
};

#endif