/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#include"ScriptPCH.h"
#include"bastion_of_twilight.h"

enum Spells
{
    //Spells
    SPELL_Befehle_des_Schattens               = 81556,
    SPELL_Bekehrung    						  = 91303,
    SPELL_Berserker							  = 64238,
    SPELL_Blut_der_Alten_Gottes_verzehren     = 82630,
	SPELL_Eiterblut                           = 82299,
	SPELL_Flammenbefehl                       = 81171,
	SPELL_Furor_des_Chogall                   = 82524,
	SPELL_Verderbenden_Kultisten_beschwoeren  = 81628,
	SPELL_Verderbnis_des_Alten_Gottes         = 82361,
	SPELL_Verfinsterte_Geschoepfe			  = 82414,
	SPELL_Finstere_Gebete					  = 91331,
	SPELL_Verderbnis_Beschleunigung			  = 81836,
	SPELL_Verderbnis_Krankheit				  = 81831,
	SPELL_Verderbnis_Missbildung		      = 82125,
	SPELL_Verderbnis_Vollendet				  = 82170,
	SPELL_Flammende_Zerstoerung				  = 93265,
	SPELL_Lohe								  = 81532,
	SPELL_Machtvolle_Schatten				  = 93219,
	SPELL_Vergossenes_Blut_des_alten_Gottes   = 81757,

};

enum Events
{
    EVENT_Befehle_des_Schattens				  = 1,
    EVENT_Bekehrung							  = 2,
    EVENT_Berserker							  = 3,
	EVENT_Blut_der_Alten_Gottes_verzehren	  = 4,
	EVENT_Eiterblut							  = 5,
	EVENT_Flammenbefehl						  = 6,
	EVENT_Furor_des_Chogall					  = 7,
	EVENT_Verderbenden_Kultisten_beschwoeren  = 8,
	EVENT_Verderbnis_des_Alten_Gottes		  = 9,
	EVENT_Verfinsterte_Geschoepfe			  = 10,
	EVENT_Finstere_Gebete					  = 11,
	EVENT_Verderbnis_Beschleunigung			  = 12,
	EVENT_Verderbnis_Krankheit				  = 13,
	EVENT_Verderbnis_Missbildung			  = 14,
	EVENT_Verderbnis_Vollendet				  = 15,
	EVENT_Flammende_Zerstoerung				  = 16,
	EVENT_Lohe								  = 17,
	EVENT_Machtvolle_Schatten				  = 18,
	EVENT_Vergossenes_Blut_des_alten_Gottes	  = 19,

};

class boss_Chogall : public CreatureScript
{
public:
    boss_Chogall() : CreatureScript("boss_Chogall") { }

    struct boss_ChogallAI : public BossAI
    {
        boss_ChogallAI(Creature *c) : BossAI(c,DATA_CHOGALL)
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
           me->RemoveAurasDueToSpell(SPELL_Berserker);
                   events.ScheduleEvent(EVENT_Befehle_des_Schattens, urand(20000, 23000));
                   events.ScheduleEvent(EVENT_Bekehrung, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Berserker, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Blut_der_Alten_Gottes_verzehren, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Eiterblut, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Flammenbefehl, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Furor_des_Chogall, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Verderbenden_Kultisten_beschwoeren, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Verderbnis_des_Alten_Gottes, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Verfinsterte_Geschoepfe, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Verderbnis_Beschleunigung, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Verderbnis_Krankheit, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Verderbnis_Missbildung, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Flammende_Zerstoerung, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Lohe, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Machtvolle_Schatten, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Vergossenes_Blut_des_alten_Gottes, urand(20000, 23000));

            if (instance)
                instance->SetData(DATA_CHOGALL, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
                        me->setActive(true);
                        Reset();
            if (instance)
                instance->SetData(DATA_CHOGALL, IN_PROGRESS);
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
                instance->SetData(DATA_CHOGALL, DONE);
        }

        void UpdateAI(const uint32 diff)
        {
           events.Update(diff);
                        
                        if (!UpdateVictim())
                return;

                   if (me->HasUnitState(UNIT_STAT_CASTING))
           return;
                
                        if (HealthBelowPct(25) && fire == 0)
                        {
                                DoCastVictim(SPELL_Furor_des_Chogall);
                                fire = 1;
                        }
                        else
                        if (HealthBelowPct(24) && fire == 1)
                        {
                                DoCastVictim(SPELL_Verderbnis_des_Alten_Gottes);
                                fire = 2;
                        }
						if (HealthBelowPct(23) && fire == 2)
                        {
                                DoCastVictim(SPELL_Verfinsterte_Geschoepfe);
                                fire = 3;
                        }


                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch (eventId)
                    {
                        case EVENT_Berserker:
                            DoCast(me,SPELL_Berserker, true);
                            break;

						case EVENT_Befehle_des_Schattens:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Befehle_des_Schattens, true);
							events.ScheduleEvent(EVENT_Befehle_des_Schattens, urand(20000, 23000));
							break;

						case EVENT_Bekehrung:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Bekehrung, true);
							events.ScheduleEvent(EVENT_Bekehrung, urand(20000, 23000));
							break;

						case EVENT_Blut_der_Alten_Gottes_verzehren:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Blut_der_Alten_Gottes_verzehren, true);
							events.ScheduleEvent(EVENT_Blut_der_Alten_Gottes_verzehren, urand(20000, 23000));
							break;

						case EVENT_Eiterblut:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Eiterblut, true);
							events.ScheduleEvent(EVENT_Eiterblut, urand(20000, 23000));
							break;

						case EVENT_Flammenbefehl:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Flammenbefehl, true);
							events.ScheduleEvent(EVENT_Flammenbefehl, urand(20000, 23000));
							break;

						case EVENT_Verderbenden_Kultisten_beschwoeren:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Verderbenden_Kultisten_beschwoeren, true);
							events.ScheduleEvent(EVENT_Verderbenden_Kultisten_beschwoeren, urand(20000, 23000));
							break;

						case EVENT_Verderbnis_Beschleunigung:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Verderbnis_Beschleunigung, true);
							events.ScheduleEvent(EVENT_Verderbnis_Beschleunigung, urand(20000, 23000));
							break;

						case EVENT_Verderbnis_Krankheit:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Verderbnis_Krankheit, true);
							events.ScheduleEvent(EVENT_Verderbnis_Krankheit, urand(20000, 23000));
							break;

						case EVENT_Verderbnis_Missbildung:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Verderbnis_Missbildung, true);
							events.ScheduleEvent(EVENT_Verderbnis_Missbildung, urand(20000, 23000));
							break;

						case EVENT_Verderbnis_Vollendet:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Verderbnis_Vollendet, true);
							events.ScheduleEvent(EVENT_Verderbnis_Vollendet, urand(20000, 23000));
							break;

						case EVENT_Flammende_Zerstoerung:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Flammende_Zerstoerung, true);
							events.ScheduleEvent(EVENT_Flammende_Zerstoerung, urand(20000, 23000));
							break;

						case EVENT_Lohe:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Lohe, true);
							events.ScheduleEvent(EVENT_Lohe, urand(20000, 23000));
							break;

						case EVENT_Machtvolle_Schatten:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Machtvolle_Schatten, true);
							events.ScheduleEvent(EVENT_Machtvolle_Schatten, urand(20000, 23000));
							break;
       
						case EVENT_Vergossenes_Blut_des_alten_Gottes:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Vergossenes_Blut_des_alten_Gottes, true);
							events.ScheduleEvent(EVENT_Vergossenes_Blut_des_alten_Gottes, urand(20000, 23000));
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
      return new boss_ChogallAI(creature);
    }
};

void AddSC_boss_Chogall()
{
    new boss_Chogall();
}
