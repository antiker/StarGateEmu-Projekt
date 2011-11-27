/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#include "ScriptPCH.h"
#include "bastion_of_twilight.h"
/* boss id's = 43688,43735,43687,43686,43689,*/
enum Spells 
{
    //Spells
    SPELL_Gravitationsschmettern              = 84948,
    SPELL_Kryogenische_Aura    				  = 84918,
    SPELL_Lavasaat							  = 84913,
    SPELL_Gefroren                            = 82772,
	SPELL_Herz_aus_Eis                        = 82665,
	SPELL_Hydrolanze                          = 82752,
	SPELL_Vergletscherung                     = 82746,
	SPELL_Wasserbombe                         = 82699,
	SPELL_Aegis_der_Flamme                    = 82631,
	SPELL_Aufsteigende_Flammen                = 82636,
	SPELL_Aufsteigende_Flammen_10             = 82639,
	SPELL_Brennendes_Blut                     = 82660,
	SPELL_Flammensog                          = 88558,
	SPELL_Flammensog_10                       = 82777,
	SPELL_Infernoansturm                      = 82859,
	SPELL_Infernoansturm_10                   = 82860,
	SPELL_Infernosprung                       = 82857,
	SPELL_Beben								  = 83565,
	SPELL_Elementare_Stasis                   = 82285,
	SPELL_Eruption                            = 83675,
	SPELL_Gravitationsbrunnen                 = 83572,
	SPELL_Haut_festigen                       = 83718,
	SPELL_Blitzableiter						  = 83099,
	SPELL_Blitzgeschoss						  = 83070,
	SPELL_Dispersion                          = 83087,
	SPELL_Donnerschock                        = 83067,
	SPELL_Winde_rufen                         = 83491,


};

enum Events  
{
    EVENT_Gravitationsschmettern			  = 1,
    EVENT_Kryogenische_Aura					  = 2,
    EVENT_Lavasaat							  = 3,
	EVENT_Gefroren							  = 4,
    EVENT_Herz_aus_Eis						  = 5,
    EVENT_Hydrolanze						  = 6,
	EVENT_Vergletscherung					  = 7,
    EVENT_Wasserbombe						  = 8,
    EVENT_Aegis_der_Flamme					  = 9,
	EVENT_Aufsteigende_Flammen				  = 10,
	EVENT_Aufsteigende_Flammen_10			  = 11,
	EVENT_Brennendes_Blut					  = 12,
	EVENT_Flammensog						  = 13,
	EVENT_Flammensog_10						  = 14,
	EVENT_Infernoansturm					  = 15,
	EVENT_Infernoansturm_10					  = 16,
	EVENT_Infernosprung						  = 17,
	EVENT_Beben							      = 18,
	EVENT_Elementare_Stasis					  = 19,
	EVENT_Eruption							  = 20,
	EVENT_Gravitationsbrunnen				  = 21,
	EVENT_Haut_festigen						  = 22,
	EVENT_Blitzableiter						  = 23,
	EVENT_Blitzgeschoss						  = 24,
	EVENT_Dispersion					      = 25,
	EVENT_Donnerschock						  = 26,
	EVENT_Winde_rufen						  = 27,

};

class boss_assembly_of_ascendents : public CreatureScript
{
public:
    boss_assembly_of_ascendents() : CreatureScript("boss_assembly_of_ascendents") { }

    struct boss_assembly_of_ascendentsAI : public BossAI
    {
        boss_assembly_of_ascendentsAI(Creature *c) : BossAI(c,DATA_ASCENDANT_COUNCIL)
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
           me->RemoveAurasDueToSpell(SPELL_Gravitationsschmettern); 
                   events.ScheduleEvent(EVENT_Gravitationsschmettern, urand(20000, 23000));
                   events.ScheduleEvent(EVENT_Kryogenische_Aura, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Gefroren, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Herz_aus_Eis, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Hydrolanze, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Vergletscherung, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Wasserbombe, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Aegis_der_Flamme, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Aufsteigende_Flammen, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Aufsteigende_Flammen_10, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Brennendes_Blut, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Flammensog, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Flammensog_10, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Infernoansturm, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Infernoansturm_10, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Infernosprung, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Beben, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Elementare_Stasis, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Eruption, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Gravitationsbrunnen, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Haut_festigen, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Blitzableiter, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Blitzgeschoss, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Dispersion, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Donnerschock, urand(20000, 23000));
				   events.ScheduleEvent(EVENT_Winde_rufen, urand(20000, 23000));

            if (instance)
                instance->SetData(DATA_ASCENDANT_COUNCIL, NOT_STARTED);
        }

        void EnterCombat(Unit* /*who*/)
        {
                        me->setActive(true);
                        Reset();
            if (instance)
                instance->SetData(DATA_ASCENDANT_COUNCIL, IN_PROGRESS);
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
                instance->SetData(DATA_ASCENDANT_COUNCIL, DONE);
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
                        case EVENT_Gravitationsschmettern:
                            DoCast(me, SPELL_Gravitationsschmettern, true);
                            break;

						case EVENT_Kryogenische_Aura:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Kryogenische_Aura, true);
							events.ScheduleEvent(EVENT_Kryogenische_Aura, urand(20000, 23000));
							break;

						case EVENT_Gefroren:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Gefroren, true);
							events.ScheduleEvent(EVENT_Gefroren, urand(20000, 23000));
							break;

						case EVENT_Herz_aus_Eis:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Herz_aus_Eis, true);
							events.ScheduleEvent(EVENT_Herz_aus_Eis, urand(20000, 23000));
							break;

						case EVENT_Hydrolanze:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Hydrolanze, true);
							events.ScheduleEvent(EVENT_Hydrolanze, urand(20000, 23000));
							break;

						case EVENT_Vergletscherung:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Vergletscherung, true);
							events.ScheduleEvent(EVENT_Vergletscherung, urand(20000, 23000));
							break;

						case EVENT_Wasserbombe:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Wasserbombe, true);
							events.ScheduleEvent(EVENT_Wasserbombe, urand(20000, 23000));
							break;

						case EVENT_Aegis_der_Flamme:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Aegis_der_Flamme, true);
							events.ScheduleEvent(EVENT_Aegis_der_Flamme, urand(20000, 23000));
							break;

						case EVENT_Aufsteigende_Flammen:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Aufsteigende_Flammen, true);
							events.ScheduleEvent(EVENT_Aufsteigende_Flammen, urand(20000, 23000));
							break;

						case EVENT_Aufsteigende_Flammen_10:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Aufsteigende_Flammen_10, true);
							events.ScheduleEvent(EVENT_Aufsteigende_Flammen_10, urand(20000, 23000));
							break;

						case EVENT_Brennendes_Blut:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Brennendes_Blut, true);
							events.ScheduleEvent(EVENT_Brennendes_Blut, urand(20000, 23000));
							break;

						case EVENT_Flammensog:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Flammensog, true);
							events.ScheduleEvent(EVENT_Flammensog, urand(20000, 23000));
							break;

						case EVENT_Flammensog_10:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Flammensog_10, true);
							events.ScheduleEvent(EVENT_Flammensog_10, urand(20000, 23000));
							break;

						case EVENT_Infernoansturm:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Infernoansturm, true);
							events.ScheduleEvent(EVENT_Infernoansturm, urand(20000, 23000));
							break;

						case EVENT_Infernoansturm_10:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Infernoansturm_10, true);
							events.ScheduleEvent(EVENT_Infernoansturm_10, urand(20000, 23000));
							break;

						case EVENT_Infernosprung:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Infernosprung, true);
							events.ScheduleEvent(EVENT_Infernosprung, urand(20000, 23000));
							break;

						case EVENT_Beben:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Beben, true);
							events.ScheduleEvent(EVENT_Beben, urand(20000, 23000));
							break;

						case EVENT_Elementare_Stasis:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Elementare_Stasis, true);
							events.ScheduleEvent(EVENT_Elementare_Stasis, urand(20000, 23000));
							break;

						case EVENT_Eruption:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Eruption, true);
							events.ScheduleEvent(EVENT_Eruption, urand(20000, 23000));
							break;

						case EVENT_Gravitationsbrunnen:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Gravitationsbrunnen, true);
							events.ScheduleEvent(EVENT_Gravitationsbrunnen, urand(20000, 23000));
							break;

						case EVENT_Haut_festigen:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Haut_festigen, true);
							events.ScheduleEvent(EVENT_Haut_festigen, urand(20000, 23000));
							break;

						case EVENT_Blitzableiter:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Blitzableiter, true);
							events.ScheduleEvent(EVENT_Blitzableiter, urand(20000, 23000));
							break;

						case EVENT_Blitzgeschoss:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Blitzgeschoss, true);
							events.ScheduleEvent(EVENT_Blitzgeschoss, urand(20000, 23000));
							break;

						case EVENT_Dispersion:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Dispersion, true);
							events.ScheduleEvent(EVENT_Dispersion, urand(20000, 23000));
							break;

						case EVENT_Donnerschock:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Donnerschock, true);
							events.ScheduleEvent(EVENT_Donnerschock, urand(20000, 23000));
							break;

						case EVENT_Winde_rufen:
							fire= 1;
							if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
								DoCast(pTarget, SPELL_Winde_rufen, true);
							events.ScheduleEvent(EVENT_Winde_rufen, urand(20000, 23000));
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
      return new boss_assembly_of_ascendentsAI(creature);
    }
};

void AddSC_boss_assembly_of_ascendents()
{
    new boss_assembly_of_ascendents();
}
