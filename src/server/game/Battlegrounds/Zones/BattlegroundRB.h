/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef __BATTLEGROUNDRB_H
#define __BATTLEGROUNDRB_H

class Battleground;

class BattlegroundRBScore : public BattlegroundScore
{
    public:
        BattlegroundRBScore() {};
        virtual ~BattlegroundRBScore() {};
};

class BattlegroundRB : public Battleground
{
    friend class BattlegroundMgr;

    public:
        BattlegroundRB();
        ~BattlegroundRB();
        void Update(uint32 diff);

        virtual void AddPlayer(Player *plr);
        virtual void StartingEventCloseDoors();
        virtual void StartingEventOpenDoors();

        void RemovePlayer(Player *plr, uint64 guid);
        void HandleAreaTrigger(Player *Source, uint32 Trigger);

        /* Scorekeeping */
        void UpdatePlayerScore(Player *Source, uint32 type, uint32 value, bool doAddHonor = true);

    private:
};
#endif