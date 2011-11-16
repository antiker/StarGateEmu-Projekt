/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef TRINITY_GUARDAI_H
#define TRINITY_GUARDAI_H

#include "ScriptedCreature.h"
#include "Timer.h"

class Creature;

class GuardAI : public ScriptedAI
{
    enum GuardState
    {
        STATE_NORMAL = 1,
        STATE_LOOK_AT_VICTIM = 2
    };

    public:

        explicit GuardAI(Creature *c);

        void MoveInLineOfSight(Unit *);
        void EnterEvadeMode();
        void JustDied(Unit *);
        bool CanSeeAlways(WorldObject const* obj);

        void UpdateAI(const uint32);
        static int Permissible(const Creature *);

    private:
        uint64 i_victimGuid;
        GuardState i_state;
        TimeTracker i_tracker;
};
#endif