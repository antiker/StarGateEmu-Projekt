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
#include ".h"

enum Spells
{
    //Spells
    SPELL_Einhuellende_Magie          = 86622,
    SPELL_Wunderbare_Flammen    	  = 86505,
    SPELL_Zwielichtverschiebung		  = 93051,
    SPELL_Verschobene_Realitaet       = 93055,
	SPELL_Zwielichtdruckwelle         = 86369,
	SPELL_Blendende_Zerstoerung       = 86408,
	SPELL_Blackout                    = 86788,
    SPELL_Verschlingende_Flammen	  = 86844,
    SPELL_Zwielichtverschiebung 	  = 93051,
    SPELL_Verschobene_Realitaet       = 93055,
	SPELL_Zwielichtmeteorit           = 86013,
	SPELL_Tiefer_Atem                 = 86059,

};

enum Events
{
    EVENT_Einhuellende_Magie		  = 1,
    EVENT_Wunderbare_Flammen		  = 2,
    EVENT_Zwielichtverschiebung		  = 3,
	EVENT_Verschobene_Realitaet		  = 4,
    EVENT_Zwielichtdruckwelle		  = 5,
    EVENT_Blendende_Zerstoerung       = 6,
	EVENT_Blackout			          = 7,
    EVENT_Verschlingende_Flammen	  = 8,
    EVENT_Zwielichtverschiebung		  = 9,
	EVENT_Verschobene_Realitaet		  = 10,
    EVENT_Zwielichtmeteorit		      = 11,
    EVENT_Tiefer_Atem                 = 12,
};

class boss_theralion_and_valiona : public CreatureScript
{
public:
    boss_theralion_and_valiona() : CreatureScript("boss_theralion_and_valiona") { }

    struct boss_theralion_and_valionaAI : public BossAI
    {
        boss_theralion_and_valionaAI(Creature *c) : BossAI(c,DATA_THERALION_AND_VALIONA)
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
           me->RemoveAurasDueToSpell(SPELL_Einhuellende_Magie);
                   events.ScheduleEvent(EVENT_Einhuellende_Magie, urand(20000, 23000));
                   events.ScheduleEvent(EVENT_Wunderbare_Flammen, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Zwielichtverschiebung, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Verschobene_Realitaet, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Zwielichtdruckwelle, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Blendende_Zerstörung, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Einhüllende_Magie, urand(20000, 23000));
                   events.ScheduleEvent(EVENT_Wunderbare_Flammen, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Zwielichtverschiebung, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Verschobene_Realitaet, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Zwielichtmeteorit, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Tiefer_Atem, urand(20000, 23000));

            if (pInstance)
                pInstance->SetData(DATA_THERALION_AND_VALIONA, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
                        me->setActive(true);
                        Reset();
            if (pInstance)
                pInstance->SetData(DATA_THERALION_AND_VALIONA, IN_PROGRESS);
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
                instance->SetData(DATA_THERALION_AND_VALIONA, DONE);
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
                                DoCastVictim(SPELL_name);
                                fire = 1;
                        }
                        else
                        if (HealthBelowPct(33) && fire == 1)
                        {
                                DoCastVictim(SPELL_name);
                                fire = 2;
                        }


                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_Einhuellende_Magie:
                            DoCast(me, SPELL_Einhuellende_Magie, true); 

						case EVENT_Wunderbare_Flammen;
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Wunderbare_Flammen, true);
							events.ScheduleEvent(EVENT_Wunderbare_Flammen, urand(20000, 23000));
							break;

						case EVENT_Zwielichtverschiebung;
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Zwielichtverschiebung, true);
							events.ScheduleEvent(EVENT_Zwielichtverschiebung, urand(20000, 23000));
							break;

						case EVENT_Verschobene_Realitaet;
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Verschobene_Realitaet, true);
							events.ScheduleEvent(EVENT_Verschobene_Realitaet, urand(20000, 23000));
							break;

						case EVENT_Zwielichtdruckwelle;
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Zwielichtdruckwelle, true);
							events.ScheduleEvent(EVENT_Zwielichtdruckwelle, urand(20000, 23000));
							break;
							
						case EVENT_Blendende_Zerstoerung;
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Blendende_Zerstoerung, true);
							events.ScheduleEvent(EVENT_Blendende_Zerstoerung, urand(20000, 23000));
							break;
											
						case EVENT_Verschlingende_Flammen;
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Verschlingende_Flammen, true);
							events.ScheduleEvent(EVENT_Verschlingende_Flammen, urand(20000, 23000));
							break;

						case EVENT_Zwielichtverschiebung;
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Zwielichtverschiebung, true);
							events.ScheduleEvent(EVENT_Zwielichtverschiebung, urand(20000, 23000));
							break;

						case EVENT_Verschobene_Realitaet;
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Verschobene_Realitaet, true);
							events.ScheduleEvent(EVENT_Verschobene_Realitaet, urand(20000, 23000));
							break;

						case EVENT_Zwielichtmeteorit;
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Zwielichtmeteorit, true);
							events.ScheduleEvent(EVENT_Zwielichtmeteorit, urand(20000, 23000));
							break;
							
						case EVENT_Tiefer_Atem;
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Tiefer_Atem, true);
							events.ScheduleEvent(EVENT_Tiefer_Atem, urand(20000, 23000));
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
      return new boss_theralion_and_valionaAI(creature);
    }
};

void AddSC_boss_theralion_and_valiona()
{
    new boss_theralion_and_valiona();
}
