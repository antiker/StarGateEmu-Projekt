/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "Common.h"
#include <ace/Singleton.h>
#include "Define.h"

class ACE_Configuration_Heap;

class Config
{
    friend class ACE_Singleton<Config, ACE_Null_Mutex>;
    Config();
    public:
        ~Config();

        bool SetSource(const char *file);
        bool Reload();

        std::string GetStringDefault(const char * name, std::string def);
        bool GetBoolDefault(const char * name, const bool def);
        int32 GetIntDefault(const char * name, const int32 def);
        float GetFloatDefault(const char * name, const float def);

        std::string GetFilename() const { return mFilename; }

        ACE_Thread_Mutex mMtx;

    private:
        std::string mFilename;
        ACE_Configuration_Heap *mConf;
};

#define sConfig ACE_Singleton<Config, ACE_Null_Mutex>::instance()

#endif