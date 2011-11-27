
/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#include "ScriptPCH.h"
#include "bastion_of_twilight.h"
/* boss id= 45213 */
enum Spells /*Hier daten einfügen */
{
    //Spells
    SPELL_Zermuerben                  = 89421,
    SPELL_Flammenatem    	          = 18435,
    SPELL_Zwielichtschlitzer		  = 92852,
    SPELL_Zwielichtdruckwelle         = 87947,
	SPELL_Zwielichtspucken            = 89299,
	SPELL_Zwielichtessenz             = 88146,
    SPELL_Pyrrhischer_Fokus           = 87323,
    SPELL_Manabarriere                = 70842,
    SPELL_Zwielichtpanzer             = 87654,
    SPELL_Essenz_entfesseln           = 90028,
    SPELL_Unbezaehmbar                = 90045,
	SPELL_Zwielichtatem               = 76817,
	SPELL_Essenz_absorbieren          = 90107,

};

enum Events 
{
    EVENT_Zermuerben                  = 1,
    EVENT_Flammenatem                 = 2,
    EVENT_Zwielichtschlitzer          = 3,
	EVENT_Zwielichtdruckwelle         = 4,
    EVENT_Zwielichtspucken            = 5,
    EVENT_Zwielichtessenz             = 6,
	EVENT_Pyrrhischer_Fokus           = 7,
    EVENT_Manabarriere                = 8,
    EVENT_Zwielichtpanzer             = 9,
	EVENT_Essenz_entfesseln           = 10,
    EVENT_Unbezaehmbar                = 11,
    EVENT_Zwielichtatem               = 12,
	EVENT_Essenz_absorbieren          = 13,

};

class boss_sinestra : public CreatureScript
{
public:
    boss_sinestra() : CreatureScript("boss_sinestra") { }

    struct boss_sinestraAI : public BossAI
    {
        boss_sinestraAI(Creature *c) : BossAI(c,DATA_SINESTRA)
        {
            //pInstance = c->GetInstanceScript();
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

        //InstanceScript* pInstance;

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
           me->RemoveAurasDueToSpell(SPELL_Zermuerben); 
                   events.ScheduleEvent(EVENT_Zermuerben, urand(20000, 23000));
                   events.ScheduleEvent(EVENT_Flammenatem, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Zwielichtschlitzer, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Zwielichtdruckwelle, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Zwielichtspucken, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Zwielichtessenz, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Pyrrhischer_Fokus, urand(20000, 23000));
                   events.ScheduleEvent(EVENT_Manabarriere, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Zwielichtpanzer, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Essenz_entfesseln, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Unbezaehmbar, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Zwielichtatem, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Essenz_absorbieren, urand(20000, 23000));

            if (instance)
                instance->SetData(DATA_SINESTRA, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
                        me->setActive(true);
                        Reset();
            if (instance)
                instance->SetData(DATA_SINESTRA, IN_PROGRESS);
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
                instance->SetData(DATA_SINESTRA, DONE);
        }

        void UpdateAI(const uint32 diff)
        {
           events.Update(diff);
                        
                        if (!UpdateVictim())
                return;

                   if (me->HasUnitState(UNIT_STAT_CASTING))
           return;

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_Zermuerben:
                            DoCast(me, SPELL_Zermuerben, true); 
                            break;

						case EVENT_Flammenatem:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Flammenatem, true);
							events.ScheduleEvent(EVENT_Flammenatem, urand(20000, 23000));
							break;

						case EVENT_Zwielichtschlitzer:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Zwielichtschlitzer, true);
							events.ScheduleEvent(EVENT_Zwielichtschlitzer, urand(20000, 23000));
							break;

						case EVENT_Zwielichtdruckwelle:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Zwielichtdruckwelle, true);
							events.ScheduleEvent(EVENT_Zwielichtdruckwelle, urand(20000, 23000));
							break;

						case EVENT_Zwielichtspucken:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Zwielichtspucken, true);
							events.ScheduleEvent(EVENT_Zwielichtspucken, urand(20000, 23000));
							break;
							
						case EVENT_Zwielichtessenz:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Zwielichtessenz, true);
							events.ScheduleEvent(EVENT_Zwielichtessenz, urand(20000, 23000));
							break;

						case EVENT_Pyrrhischer_Fokus:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Pyrrhischer_Fokus, true);
							events.ScheduleEvent(EVENT_Pyrrhischer_Fokus, urand(20000, 23000));
							break;

						case EVENT_Manabarriere:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Manabarriere, true);
							events.ScheduleEvent(EVENT_Manabarriere, urand(20000, 23000));
							break;

						case EVENT_Zwielichtpanzer:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Zwielichtpanzer, true);
							events.ScheduleEvent(EVENT_Zwielichtpanzer, urand(20000, 23000));
							break;

						case EVENT_Essenz_entfesseln:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Essenz_entfesseln, true);
							events.ScheduleEvent(EVENT_Essenz_entfesseln, urand(20000, 23000));
							break;
							
						case EVENT_Unbezaehmbar:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Unbezaehmbar, true);
							events.ScheduleEvent(EVENT_Unbezaehmbar, urand(20000, 23000));
							break;
       
						case EVENT_Zwielichtatem:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Zwielichtatem, true);
							events.ScheduleEvent(EVENT_Zwielichtatem, urand(20000, 23000));
							break;
							
						case EVENT_Essenz_absorbieren:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Essenz_absorbieren, true);
							events.ScheduleEvent(EVENT_Essenz_absorbieren, urand(20000, 23000));
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
      return new boss_sinestraAI(creature);
    }
};

void AddSC_boss_sinestra()
{
    new boss_sinestra();
}
