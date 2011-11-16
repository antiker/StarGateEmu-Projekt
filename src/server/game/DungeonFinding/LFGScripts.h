/*
 * Copyright (C) 2010-2011 Project StarGate
 */

/*
 * Interaction between core and LFGScripts
 */

#include "Common.h"
#include "SharedDefines.h"
#include "ScriptPCH.h"

class Player;
class Group;

class LFGScripts: public GroupScript, public PlayerScript
{
    public:
        LFGScripts();

        // Group Hooks
        void OnAddMember(Group* group, uint64 guid);
        void OnRemoveMember(Group* group, uint64 guid, RemoveMethod& method, uint64 kicker, const char* reason);
        void OnDisband(Group* group);
        void OnChangeLeader(Group* group, uint64 newLeaderGuid, uint64 oldLeaderGuid);
        void OnInviteMember(Group* group, uint64 guid);

        // Player Hooks
        void OnLevelChanged(Player* player, uint8 newLevel);
        void OnLogout(Player* player);
        void OnLogin(Player* player);
        void OnBindToInstance(Player* player, Difficulty difficulty, uint32 mapId, bool permanent);
};