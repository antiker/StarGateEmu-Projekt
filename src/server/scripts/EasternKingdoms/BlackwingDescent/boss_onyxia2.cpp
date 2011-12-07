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
#include"blackwing_descent.h"
#include"ScriptMgr.h"
#include"ScriptedCreature.h"
#include"SpellScript.h"
#include"SpellAuraEffects.h"

enum Spells
{   // Phase 1 spells
    SPELL_SHADOWFLAME_BREATH_25H = 94126,
	SPELL_SHADOWFLAME_BREATH_10N = 77826,
	SPELL_SHADOWFLAME_BREATH_10H = 94125,
	SPELL_SHADOWFLAME_BREATH_25N = 94124,
	// Phase 2 spells
	SPELL_TAIL_LASH_25H = 94130,
	SPELL_TAIL_LASH_10N = 77827,
	SPELL_TAIL_LASH_10H = 94129,
	SPELL_TAIL_LASH_25N = 94128,
	//Not much choise about these. We have to make own defintion on the direction/start-end point
	SPELL_CHILDREN_OF_DEATHWING = 78619,
	SPELL_SHADOW_OF_COWARDICE = 79353,
	// Phase 3 spells
	SPELL_TAIL_LASH_10H3TH = 94129,
    };
    
    
    
#define SAY_NEFARIAN_TO_ME    -1000005


struct sOnyxMove
{
    uint32 uiLocId;
    uint32 uiLocIdEnd;
    uint32 uiSpellId;
    float fX, fY, fZ;
};

const Position MiddleRoomLocation = {-116.851997f, -228.835007f, -23.796700f, 0.0f};

const Position Phase2Location = {-69.695496f, -223.680176f, -63.564503f, 0.0f};


class boss_onyxia2 : public CreatureScript
{
public:
    boss_onyxia2() : CreatureScript("boss_onyxia2") {}
	
    CreatureAI* GetAI(Creature* pCreature) const
    {
       return new boss_onyxia2AI(pCreature);
    }
    struct boss_onyxia2AI : public ScriptedAI
	{
		boss_onyxia2AI(Creature* pCreature) : ScriptedAI(pCreature), Summons(me)
        {
            pInstance = pCreature->GetInstanceScript();
        }

        InstanceScript *pInstance;
        EventMap events;
        SummonList Summons;
        bool check_in;
		bool summoned_Nefarian;

        uint32 m_uiSayTimer;                                    // Timer for random chat
        uint32 m_uiRebuffTimer;                                 // Timer for rebuffing
        uint32 m_uiSpellTimerCTW;                               // Timer for start spell Call The Wind when in combat
        uint32 m_uiSpellTimerCTW_stop;                          // Timer for stop spell Call The Wind when in combat

        uint32 m_uiSpellTimerLB;                                 // Timer for spell 1 when in combat
        uint32 m_uiSpellTimerCB;                                 // Timer until we go into Beserk (enraged) mode

		uint32 m_uiSpellTimerSummTwister;

        uint32 m_uiPhase;                                       // The current battle phase we are in
        uint32 m_uiPhaseTimer;                                  // Timer until phase transition
		bool isCTW;
		float windOrientation;
		float windDiffOrientation;
		sOnyxMove* m_pPointData;
		bool m_bIsMoving;

        void Reset()
        {
            events.Reset();
			
			m_uiPhase = 1;                                      // Start in phase 1
            m_uiPhaseTimer = 60000;                             // 60 seconds

            m_uiSpellTimerCTW = urand(10000,15000);            // between 10 and 15 seconds
			m_uiSpellTimerCTW_stop = urand(2000,5000);         // between 2 and 5 seconds
			
            m_uiSpellTimerLB = urand(10000,20000);               // between 10 and 20 seconds
            m_uiSpellTimerCB = urand(10000,20000);               // between 10 and 20 seconds

            m_uiSpellTimerSummTwister = 10000;                           //  2 minutes
                            
            if (pInstance && (pInstance->GetData(DATA_ONYXIA_EVENT) != DONE && !check_in))
                pInstance->SetData(DATA_ONYXIA_EVENT, NOT_STARTED);
            
            check_in = false;
			isCTW = false;
			summoned_Nefarian = false ;
		}


        void JustDied(Unit* /*Kill*/)
        {

            if (pInstance)
                pInstance->SetData(DATA_ONYXIA_EVENT, DONE);
        }
        void KilledUnit(Unit* /*Killed*/)
        {
//            DoScriptText(RAND(SAY_KILL_1, SAY_KILL_2), me);
        }

        void EnterCombat(Unit* /*Ent*/)
        {

            DoZoneInCombat();

			if (pInstance)
                pInstance->SetData(DATA_ONYXIA_EVENT, IN_PROGRESS);
			
		}

        void UpdateAI(const uint32 uiDiff)
        {

            if (!UpdateVictim())  /* No target to kill */
                return;
							
			events.Update(uiDiff);

            if (me->HasUnitState(UNIT_STAT_CASTING))
                return;

                //Spell CTW timer
                if ( m_uiSpellTimerCTW <= uiDiff )
                {
					if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
						DoCast(SPELL_SHADOWFLAME_BREATH_10N);
					
					DoCast(me, SPELL_SHADOWFLAME_BREATH_10N);
					windOrientation = me->GetOrientation();
					
					m_uiSpellTimerCTW = 19000;
					isCTW = true;
                }
                else  
				{
                    m_uiSpellTimerCTW -= uiDiff;
					me->SetUnitMovementFlags(MOVEMENTFLAG_LEVITATING);
					me->setActive(true);
					//me->GetMotionMaster()->MoveIdle();
				}

                //Spell CB timer
                if (m_uiSpellTimerCB <= uiDiff)
                {
                    //Cast spell two on our current target.
                    DoCast(me->getVictim(), SPELL_TAIL_LASH_10N);
                    m_uiSpellTimerCB = urand(10000,20000);
                }
                else
                    m_uiSpellTimerCB -= uiDiff;

				//Spell LB timer
				if (m_uiSpellTimerLB <= uiDiff)
				{
					//Cast spell one on our current target.
					DoCast(me->getVictim(), SPELL_TAIL_LASH_10N);

					m_uiSpellTimerLB = urand(15000,30000);
				}
				else
					m_uiSpellTimerLB -= uiDiff;

				//Spell m_uiSpellTimerSummTwister timer
				if (m_uiSpellTimerSummTwister <= uiDiff)
				{
					 for (int i=0; i < 4; i++)
					 {
						me->SummonCreature(41918, -88.118896f, -235.529007f, 14.072900f, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
					 }

					 DoCast(me->getVictim(), SPELL_CHILDREN_OF_DEATHWING);

					m_uiSpellTimerSummTwister = 20000;
				}
				else
					m_uiSpellTimerSummTwister -= uiDiff;

				if( (me->GetHealth() < me->GetMaxHealth() / 4 ) && (!summoned_Nefarian)   ) 
				{
					DoScriptText(SAY_NEFARIAN_TO_ME, me);
	   	  	                me->SummonCreature(NPC_NEFARIAN, -88.118896f, -235.529007f, 14.072900f, 0, TEMPSUMMON_CORPSE_DESPAWN);  // will be sufficent ? si caliamo un po il summon che ne tira su
					summoned_Nefarian = true; // to prevent the continuos spawn of nefy 
				}
/*
				Map::PlayerList const &PlayerList = pInstance->instance->GetPlayers();
				for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
					if (Player *pPlayer = i->getSource())
					{
						//DoCast(pPlayer,  78068);
						if ( windDiffOrientation < 1.5f )
							DoCast(pPlayer,  SPELL_SHADOWFLAME_BREATH_10N);
						else 
							DoCast(pPlayer,  SPELL_SHADOWFLAME_BREATH_10N);
					}
*/
            					
        DoMeleeAttackIfReady();
    }
};
            
};

void AddSC_boss_onyxia2()
	
{
    new boss_onyxia2();
}