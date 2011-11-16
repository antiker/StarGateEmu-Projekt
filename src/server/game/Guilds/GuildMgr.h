/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef _GUILDMGR_H
#define _GUILDMGR_H

#include "Guild.h"

class GuildMgr
{
    friend class ACE_Singleton<GuildMgr, ACE_Null_Mutex>;
    GuildMgr();
    ~GuildMgr();

public:
    typedef UNORDERED_MAP<uint32, Guild*> GuildContainer;

    Guild* GetGuildByLeader(uint64 const& guid) const;
    Guild* GetGuildById(uint32 guildId) const;
    Guild* GetGuildByName(const std::string& guildName) const;
    std::string GetGuildNameById(uint32 guildId) const;

    void LoadGuilds();
    void AddGuild(Guild* guild);
    void RemoveGuild(uint32 guildId);

    uint32 GenerateGuildId();
    void SetNextGuildId(uint32 Id) { NextGuildId = Id; }

protected:
    uint32 NextGuildId;
    GuildContainer GuildStore;
};

#define sGuildMgr ACE_Singleton<GuildMgr, ACE_Null_Mutex>::instance()

#endif