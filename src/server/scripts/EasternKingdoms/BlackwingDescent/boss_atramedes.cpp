/*
 * Copyright (C) 2005-2011 MaNGOS <http://www.getmangos.com/>
 *
 * Copyright (C) 2008-2011 Trinity <http://www.trinitycore.org/>
 *
 * Copyright (C) 2006-2011 ScriptDev2 <http://www.scriptdev2.com/>
 *
 * Copyright (C) 2010-2011 Project SkyFire <http://www.projectskyfire.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "ScriptPCH.h"
#include "blackwing_descent.h"
/*boss id = 41442 */
enum Spells
{
    //Spells
    SPELL_Modulation                  = 92451,
    SPELL_Hallender_Klang		      = 77611,
    SPELL_Verwuestung				  = 78868,
    SPELL_Vertigo                     = 77717,
	SPELL_Sonarpuls                   = 92418,
	SPELL_Schallatem                  = 78100,
	SPELL_Sengende_Flammen            = 77657,
	SPELL_Prasselnder_Flammenatem     = 78353,
	SPELL_Sonar_Bombe                 = 92553,
	SPELL_Schallfeuerball             = 78115,
	SPELL_Nerviges_Scheusal           = 49740,
	SPELL_Phasenverschiebung          = 8611,
	SPELL_Nerven                      = 92677,

};

enum Events
{
    EVENT_Modulation				  = 1,
    EVENT_Hallender_Klang             = 2,
    EVENT_Verwuestung				  = 3,
	EVENT_Vertigo					  = 4,
    EVENT_Sonarpuls					  = 5,
    EVENT_Schallatem				  = 6,
	EVENT_Sengende_Flammen 			  = 7,
    EVENT_Prasselnder_Flammenatem 	  = 8,
    EVENT_Sonar_Bombe				  = 9,
	EVENT_Schallfeuerball			  = 10,
    EVENT_Nerviges_Scheusal			  = 11,
    EVENT_Phasenverschiebung		  = 12,
	EVENT_Nerven					  = 13,

};

class boss_atramedes : public CreatureScript
{
public:
    boss_atramedes() : CreatureScript("boss_atramedes") { }

    struct boss_atramedesAI : public BossAI
    {
        boss_atramedesAI(Creature *c) : BossAI(c,DATA_ATRAMEDES)
        {
            pInstance = c->GetInstanceScript();
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

        InstanceScript* pInstance;

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
           me->RemoveAurasDueToSpell(SPELL_Modulation);
                   events.ScheduleEvent(EVENT_Modulation, urand(20000, 23000));
                   events.ScheduleEvent(EVENT_Hallender_Klang, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Verwuestung, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Vertigo, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Sonarpuls, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Schallatem, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Sengende_Flammen, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Prasselnder_Flammenatem, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Sonar_Bombe, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Schallfeuerball, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Nerviges_Scheusal, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Phasenverschiebung, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Nerven, urand(20000, 23000));

            if (pInstance)
                pInstance->SetData(DATA_ATRAMEDES, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
                        me->setActive(true);
                        Reset();
            if (pInstance)
                pInstance->SetData(DATA_ATRAMEDES, IN_PROGRESS);
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
                instance->SetData(DATA_ATRAMEDES, DONE);
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
                        case EVENT_Modulation:
                            DoCast(me, SPELL_Modulation, true);
                            break;

						case EVENT_Hallender_Klang:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Hallender_Klang, true);
							events.ScheduleEvent(EVENT_Hallender_Klang, urand(20000, 23000));
							break;

						case EVENT_Verwuestung:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Verwuestung, true);
							events.ScheduleEvent(EVENT_Verwuestung, urand(20000, 23000));
							break;

						case EVENT_Vertigo:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Vertigo, true);
							events.ScheduleEvent(EVENT_Vertigo, urand(20000, 23000));
							break;

						case EVENT_Sonarpuls:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Sonarpuls, true);
							events.ScheduleEvent(EVENT_Sonarpuls, urand(20000, 23000));
							break;

						case EVENT_Schallatem:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Schallatem, true);
							events.ScheduleEvent(EVENT_Schallatem, urand(20000, 23000));
							break;

						case EVENT_Sengende_Flammen:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Sengende_Flammen, true);
							events.ScheduleEvent(EVENT_Sengende_Flammen, urand(20000, 23000));
							break;

						case EVENT_Prasselnder_Flammenatem:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Prasselnder_Flammenatem, true);
							events.ScheduleEvent(EVENT_Prasselnder_Flammenatem, urand(20000, 23000));
							break;

						case EVENT_Sonar_Bombe:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Sonar_Bombe, true);
							events.ScheduleEvent(EVENT_Sonar_Bombe, urand(20000, 23000));
							break;

						case EVENT_Schallfeuerball:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Schallfeuerball, true);
							events.ScheduleEvent(EVENT_Schallfeuerball, urand(20000, 23000));
							break;

						case EVENT_Nerviges_Scheusal:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Nerviges_Scheusal, true);
							events.ScheduleEvent(EVENT_Nerviges_Scheusal, urand(20000, 23000));
							break;

						case EVENT_Phasenverschiebung:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Phasenverschiebung, true);
							events.ScheduleEvent(EVENT_Phasenverschiebung, urand(20000, 23000));
							break;

						case EVENT_Nerven:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Nerven, true);
							events.ScheduleEvent(EVENT_Nerven, urand(20000, 23000));
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
      return new boss_atramedesAI(creature);
    }
};

void AddSC_boss_atramedes()
{
    new boss_atramedes();
}