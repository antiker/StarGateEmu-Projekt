/*
* Copyright (C) 2010-2011 Project StarGate
*/

#include "ScriptPCH.h"
#include "baradin_hold.h"

enum Spells
{
    //Spells
    SPELL_BERSERK                                 = 47008,
    SPELL_METEOR_STRIKE_10                        = 88942,
    SPELL_DEVILSFIRESTORM                         = 88972,
    SPELL_DARKNESS_10                             = 88954,
};

enum Events
{
        EVENT_ENRAGE                    = 1,
        EVENT_METEOR_STRIKE             = 2,
        EVENT_DARKNESS                  = 3,
};

class boss_argaloth : public CreatureScript
{
public:
    boss_argaloth() : CreatureScript("boss_argaloth") { }

    struct boss_argalothAI : public BossAI
    {
        boss_argalothAI(Creature *c) : BossAI(c,DATA_ARGALOTH)
        {
                        baseSpeed = c->GetSpeedRate(MOVE_RUN);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_DISPEL, true);
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_FEAR, true);
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_PERIODIC_HEAL, true);
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_STUN, true);
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_ROOT, true);
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_DECREASE_SPEED, true);
            me->ApplySpellImmune(0, IMMUNITY_STATE, SPELL_AURA_MOD_CONFUSE, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_SHIELD, true);
            me->ApplySpellImmune(0, IMMUNITY_ID, 13810, true); // Frost Trap
            me->ApplySpellImmune(0, IMMUNITY_ID, 55741, true); // Desecration Rank 1
            me->ApplySpellImmune(0, IMMUNITY_ID, 68766, true); // Desecration Rank 2
        }
		void InitializeAI()
        {
                if (!me->isDead())
         Reset();
        }

        void Reset()
        {
                   _Reset();
                   fire=0;
           me->SetSpeed(MOVE_RUN, baseSpeed, true);
           me->RemoveAurasDueToSpell(SPELL_BERSERK);
                   events.ScheduleEvent(EVENT_DARKNESS, urand(23000, 28000));
                   events.ScheduleEvent(EVENT_METEOR_STRIKE, urand(20000, 25000));
           events.ScheduleEvent(EVENT_ENRAGE, 300000);

            if (instance)
                instance->SetData(DATA_ARGALOTH, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
                        me->setActive(true);
                        Reset();
            if (instance)
                instance->SetData(DATA_ARGALOTH, IN_PROGRESS);
        }
        void MoveInLineOfSight(Unit* victim) {}     
                
        void AttackStart(Unit* victim)
        {
                        if (me->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE))
                return;

            if (victim && me->Attack(victim, true))
                me->GetMotionMaster()->MoveChase(victim);
                                        
            if (me->Attack(victim, true))
            {
                me->AddThreat(victim, 0.0f);
                me->SetInCombatWith(victim);
                victim->SetInCombatWith(victim);
                DoStartMovement(victim);
                        }
        }


        void JustDied(Unit*killer)
        {
	    _JustDied();
            if (instance)
                instance->SetData(DATA_ARGALOTH, DONE);

                        
        }

        void UpdateAI(const uint32 diff)
        {
           events.Update(diff);
                        
                        if (!UpdateVictim())
                return;

                   if (me->HasUnitState(UNIT_STAT_CASTING))
           return;
                
                        if (HealthBelowPct(66) && fire == 0)
                        {
                                DoCastVictim(SPELL_DEVILSFIRESTORM);
                                fire = 1;
                        }
                        else
                        if (HealthBelowPct(33) && fire == 1)
                        {
                                DoCastVictim(SPELL_DEVILSFIRESTORM);
                                fire = 2;
                        }


                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_ENRAGE:
                            DoCast(me, SPELL_BERSERK, true);
                            break;
                                                case EVENT_METEOR_STRIKE:
                            DoCast(SPELL_METEOR_STRIKE_10);
                                                        events.ScheduleEvent(EVENT_METEOR_STRIKE, urand(20000, 25000));
                            break;
                                                case EVENT_DARKNESS:
                                                        for (int i = 0; i < 3; i++)
                                                        {
                                                                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
                                                                DoCast(pTarget, SPELL_DARKNESS_10);
                                                        }
                                                        events.ScheduleEvent(EVENT_DARKNESS, urand(23000, 28000));
                            break;
                    }
                }
                   DoMeleeAttackIfReady();
        }
        private:
            float baseSpeed;
                        int fire;
    };


        CreatureAI* GetAI(Creature* creature) const
    {
      return new boss_argalothAI(creature);
    }
};

void AddSC_boss_argaloth()
{
    new boss_argaloth();
}
