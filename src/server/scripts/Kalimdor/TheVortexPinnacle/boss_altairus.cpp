/* 
 * Copyright (C) 2010-2011 Project StarGate
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include"ScriptPCH.h"
#include"WorldPacket.h"
#include"the_vortex_pinnacle.h"
#include"ScriptMgr.h"
#include"ScriptedCreature.h"
#include"SpellScript.h"
#include"SpellAuraEffects.h"

enum Spells
{
    SPELL_CALL_THE_WIND = 88772,
	SPELL_STOP_CALL_THE_WIND = 88244,
    SPELL_UPWIND_OF_ALTAIRUS = 88282,
    SPELL_DOWNWIND_OF_ALTAIRUS = 88286,
    SPELL_CHILLING_BREATH = 88308,
    SPELL_LIGHTING_BLAST = 88357,
    SPELL_TWISTING_WINDS = 88314
};

class boss_altairus : public CreatureScript
{
    public:
        boss_altairus() : CreatureScript("boss_altairus") {}
	
        CreatureAI* GetAI(Creature* pCreature) const
        {
           return new boss_altairusAI(pCreature);
        }
        struct boss_altairusAI : public ScriptedAI
		{
			boss_altairusAI(Creature* pCreature) : ScriptedAI(pCreature), Summons(me)
			{
				pInstance = pCreature->GetInstanceScript();
			}

			InstanceScript *pInstance;
            EventMap events;
            SummonList Summons;
            bool check_in;

            uint32 m_uiSayTimer;                                    // Timer for random chat
            uint32 m_uiRebuffTimer;                                 // Timer for rebuffing
            uint32 m_uiSpellTimerCTW;                                 // Timer for spell 1 when in combat
            uint32 m_uiSpellTimerCTW_stop;                                 // Timer for spell 1 when in combat

            uint32 m_uiSpellTimerLB;                                 // Timer for spell 1 when in combat
            uint32 m_uiSpellTimerCB;                                 // Timer until we go into Beserk (enraged) mode

			uint32 m_uiSpellTimerSummTwister;

            uint32 m_uiPhase;                                       // The current battle phase we are in
            uint32 m_uiPhaseTimer;                                  // Timer until phase transition
			bool isCTW;
			float windOrientation;

            void Reset ()
			{
                events.Reset();
				
				m_uiPhase = 1;                                      // Start in phase 1
                m_uiPhaseTimer = 60000;                             // 60 seconds

                m_uiSpellTimerCTW = urand(10000,15000);            // between 10 and 15 seconds
				m_uiSpellTimerCTW_stop = urand(2000,5000);         // between 2 and 5 seconds
				
                m_uiSpellTimerLB = urand(10000,20000);               // between 10 and 20 seconds
                m_uiSpellTimerCB = urand(10000,20000);               // between 10 and 20 seconds

                m_uiSpellTimerSummTwister = 5000;                           //  2 minutes
                                
                if (pInstance && (pInstance->GetData(DATA_ALTAIRUS_EVENT) != DONE && !check_in))
                    pInstance->SetData(DATA_ALTAIRUS_EVENT, NOT_STARTED);
                
                check_in = false;
				isCTW = false;
			}
			
            void JustDied(Unit* /*Kill*/)
            {

                if (pInstance)
                    pInstance->SetData(DATA_ALTAIRUS_EVENT, DONE);
            }

            void EnterCombat(Unit* /*Ent*/)
            {
				if (pInstance)
                    pInstance->SetData(DATA_ALTAIRUS_EVENT, IN_PROGRESS);

                DoZoneInCombat();
			}

			void UpdateAI(const uint32 uiDiff)
            {
                if (!UpdateVictim())  /* No target to kill */
                    return;
								
				events.Update(uiDiff);
	//Spell STOP CTW timer
              if (m_uiSpellTimerCTW <= uiDiff && isCTW)
              {
          if (me->HasAura(SPELL_CALL_THE_WIND))
            me-> RemoveAurasDueToSpell(SPELL_CALL_THE_WIND);
                  DoCast(me, SPELL_STOP_CALL_THE_WIND);
          m_uiSpellTimerCTW_stop = urand(2000,5000);
          isCTW = false;
              }
              else if ( isCTW ) 
                  m_uiSpellTimerCTW -= uiDiff;

        //Spell CTW timer
        if (m_uiSpellTimerCTW_stop <= uiDiff && !isCTW)
              {
                      DoCast(me, SPELL_CALL_THE_WIND);
            windOrientation = me->GetOrientation();
            m_uiSpellTimerCTW = urand(10000,20000);
            isCTW = true;
              }
              else if ( !isCTW ) 
                  m_uiSpellTimerCTW_stop -= uiDiff;

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;

		  //Spell CB timer
              if (m_uiSpellTimerCB <= uiDiff)
              {
                  //Cast spell two on our current target.
                  DoCast(me->getVictim(), SPELL_CHILLING_BREATH);
                  m_uiSpellTimerCB = urand(10000,20000);
              }
              else
                  m_uiSpellTimerCB -= uiDiff;
	
	  //Spell LB timer
        if (m_uiSpellTimerLB <= uiDiff)
        {
          //Cast spell one on our current target.
          DoCast(me->getVictim(), SPELL_LIGHTING_BLAST);

          m_uiSpellTimerLB = urand(10000,20000);
        }
        else
          m_uiSpellTimerLB -= uiDiff;

        //Spell m_uiSpellTimerSummTwister timer
        if (m_uiSpellTimerSummTwister <= uiDiff)
        {
          //Cast spell one on our current target.
          me->SummonCreature(47342, 0.0f, 0.0f, 0.0f, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
                    DoCast(me->getVictim(), SPELL_TWISTING_WINDS);

          m_uiSpellTimerSummTwister = 3000;
        }
        else
          m_uiSpellTimerSummTwister -= uiDiff;

        Map* pMap = me->GetMap();
                Map::PlayerList const &PlayerList = pMap->GetPlayers();
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    if (Player* i_pl = i->getSource())
                        if (i_pl->isAlive())
              if ( i_pl->isInFrontInMap(NULL , 4 , windOrientation ) )
                DoCast(i_pl,  SPELL_UPWIND_OF_ALTAIRUS);
              else 
                DoCast(i_pl,  SPELL_DOWNWIND_OF_ALTAIRUS);
	
                					
            DoMeleeAttackIfReady();
        }
    };
            
};

void AddSC_boss_altairus()
{
    new boss_altairus();
}