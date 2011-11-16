/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef __BATTLEGROUNDDS_H
#define __BATTLEGROUNDDS_H

class Battleground;

enum BattlegroundDSObjectTypes
{
    BG_DS_OBJECT_DOOR_1         = 0,
    BG_DS_OBJECT_DOOR_2         = 1,
    BG_DS_OBJECT_WATER_1        = 2,
    BG_DS_OBJECT_WATER_2        = 3,
    BG_DS_OBJECT_BUFF_1         = 4,
    BG_DS_OBJECT_BUFF_2         = 5,
    BG_DS_OBJECT_MAX            = 6
};

enum BattlegroundDSObjects
{
    BG_DS_OBJECT_TYPE_DOOR_1    = 192642,
    BG_DS_OBJECT_TYPE_DOOR_2    = 192643,
    BG_DS_OBJECT_TYPE_WATER_1   = 194395,
    BG_DS_OBJECT_TYPE_WATER_2   = 191877,
    BG_DS_OBJECT_TYPE_BUFF_1    = 184663,
    BG_DS_OBJECT_TYPE_BUFF_2    = 184664
};

enum BattlegroundDSData
{ // These values are NOT blizzlike... need the correct data!
    BG_DS_WATERFALL_TIMER_MIN                    = 30000,
    BG_DS_WATERFALL_TIMER_MAX                    = 60000,
    BG_DS_WATERFALL_DURATION                     = 10000,
};

class BattlegroundDSScore : public BattlegroundScore
{
    public:
        BattlegroundDSScore() {};
        virtual ~BattlegroundDSScore() {};
        //TODO fix me
};

class BattlegroundDS : public Battleground
{
    friend class BattlegroundMgr;

    public:
        BattlegroundDS();
        ~BattlegroundDS();
        void Update(uint32 diff);

        /* inherited from BattlegroundClass */
        virtual void AddPlayer(Player *plr);
        virtual void StartingEventCloseDoors();
        virtual void StartingEventOpenDoors();

        void RemovePlayer(Player *plr, uint64 guid);
        void HandleAreaTrigger(Player *Source, uint32 Trigger);
        bool SetupBattleground();
        virtual void Reset();
        virtual void FillInitialWorldStates(WorldPacket &d);
        void HandleKillPlayer(Player* player, Player *killer);
        bool HandlePlayerUnderMap(Player * plr);
    private:
        uint32 m_waterTimer;
        bool m_waterfallActive;
    protected:
        bool isWaterFallActive() { return m_waterfallActive; };
        void setWaterFallActive(bool active) { m_waterfallActive = active; };
        void setWaterFallTimer(uint32 timer) { m_waterTimer = timer; };
        uint32 getWaterFallTimer() { return m_waterTimer; };
};
#endif