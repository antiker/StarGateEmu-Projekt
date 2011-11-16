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

/* ScriptData
SDName: boss_nefarian2
SD%Complete: 80
SDComment: Some issues with class calls effecting more than one class
SDCategory: Blackwing Lair
EndScriptData */

#include"ScriptPCH.h"
#include"WorldPacket.h"
#include"blackwing_descent.h"
#include"ScriptMgr.h"
#include"ScriptedCreature.h"
#include"SpellScript.h"
#include"SpellAuraEffects.h"

#define SAY_AGGRO               -1469007
#define SAY_XHEALTH             -1469008
#define SAY_SHADOWFLAME         -1469009
#define SAY_RAISE_SKELETONS     -1469010
#define SAY_SLAY                -1469011
#define SAY_DEATH               -1469012

#define SAY_MAGE                -1469013
#define SAY_WARRIOR             -1469014
#define SAY_DRUID               -1469015
#define SAY_PRIEST              -1469016
#define SAY_PALADIN             -1469017
#define SAY_SHAMAN              -1469018
#define SAY_WARLOCK             -1469019
#define SAY_HUNTER              -1469020
#define SAY_ROGUE               -1469021

enum Spells 

{  //Spell list
 SPELL_BERSERK_ALL              =  26662,
 SPELL_CHILDREN_OF_DEATHWING_ALL  =  78620,
 SPELL_DOMINION_H                 =  79318,
 SPELL_EXPLOSIVE_CINDERS_H        =  79339,
 SPELL_HAIL_OF_BONES_H10          =  94105,
 SPELL_HAIL_OF_BONES_N10          =  78684,
 SPELL_HAIL_OF_BONES_N25          =  94104,               //
 SPELL_HAIL_OF_BONES_H25          =  94106,
 SPELL_SHADOW_OF_COWARDIGE_ALL    =  79353,
 SPELL_SHADOWBLAZE_SPARK_ALL      =  81031,
 SPELL_SHADOWFLAME_BARRAGE_N25    =  94121,
 SPELL_SHADOWFLAME_BARRAGE_H25    =  94123,
 SPELL_SHADOWFLAME_BARRAGE_N10    =  78621,
 SPELL_SHADOWFLAME_BARRAGE_H10    =  94122,
 SPELL_SHADOWFLAME_BREATH_H10     =  94125,
 SPELL_SHADOWFLAME_BREATH_N25     =  94124,
 SPELL_SHADOWFLAME_BREATH_H25     =  94126,
 SPELL_SHADOWFLAME_BREATH_N10     =  77826,
 SPELL_TAIL_LASH_H10              =  94129,
 SPELL_TAIL_LASH_N10              =  77827,
 SPELL_TAIL_LASH_N25              =  94128,
 SPELL_TAIL_LASH_H25              =  94130,
 };

#define SPELL_MAGE                  23410                   //wild magic
#define SPELL_WARRIOR               23397                   //beserk
#define SPELL_DRUID                 23398                   // cat form
#define SPELL_PRIEST                23401                   // corrupted healing
#define SPELL_PALADIN               23418                   //syphon blessing
#define SPELL_SHAMAN                23425                   //totems
#define SPELL_WARLOCK               23427                   //infernals
#define SPELL_HUNTER                23436                   //bow broke
#define SPELL_ROGUE                 23414                   //Paralise

class boss_nefarian2 : public CreatureScript
{
public:
    boss_nefarian2() : CreatureScript("boss_nefarian2") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_nefarian2AI (pCreature);
    }

    struct boss_nefarian2AI : public BossAI
    {
        boss_nefarian2AI(Creature *c) : BossAI(c, DATA_NEFARIAN) {}

        uint32 Berserk_Timer;
        uint32 Children_of_Deathwing_Timer;
        uint32 Dominion_Timer;
        uint32 Explosive_Cinders_Timer;
        uint32 Hail_of_Bones_Timer;
        uint32 Shadow_of_Cowardige_Timer;
        uint32 Shadowblaze_Spark_Timer;
        uint32 Shadowflame_Barrage_Timer;
        uint32 Shadowflame_Breath_Timer;
        uint32 Tail_Lash_Timer;
        uint32 ClassCall_Timer;
        bool Phase3;

        uint32 DespawnTimer;

        void Reset()
        {
            Berserk_Timer = 15000;
            Children_of_Deathwing_Timer = 20000;
            Dominion_Timer = 25000;
            Explosive_Cinders_Timer = 17000;
            Hail_of_Bones_Timer = 15000;
            Shadow_of_Cowardige_Timer = 30000;
            Shadowblaze_Spark_Timer = 25000;
            Shadowflame_Barrage_Timer = 12000;                  //These times are probably wrong
            Shadowflame_Breath_Timer = 7000;
            Tail_Lash_Timer = 10000;
            ClassCall_Timer = 35000;                            //35-40 seconds
            Phase3 = false;

            DespawnTimer = 5000000;
        }

        void KilledUnit(Unit* Victim)
        {
            if (rand()%5)
                return;

            DoScriptText(SAY_SLAY, me, Victim);
        }

        void JustDied(Unit* /*Killer*/)
        {
 		_JustDied();
			if (instance)
            DoScriptText(SAY_DEATH, me);
        }

        void EnterCombat(Unit * who)
        {
            DoScriptText(RAND(SAY_XHEALTH, SAY_AGGRO, SAY_SHADOWFLAME), me);

            DoCast(who, SPELL_CHILDREN_OF_DEATHWING_ALL);
            DoZoneInCombat();
        }

        void UpdateAI(const uint32 diff)
        {
            if (DespawnTimer <= diff)
            {
                if (!UpdateVictim())
                    me->ForcedDespawn();
                DespawnTimer = 5000000;
            } else DespawnTimer -= diff;

            if (!UpdateVictim())
                return;

            //Shadowflame_Barrage_Timer
            if (Shadowflame_Barrage_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_SHADOWFLAME_BARRAGE_N10);
                Shadowflame_Barrage_Timer = 12000;
            } else Shadowflame_Barrage_Timer -= diff;

            //Hail_of_Bones_Timer
            if (Hail_of_Bones_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_HAIL_OF_BONES_H10);
                Hail_of_Bones_Timer = 15000;
            } else Hail_of_Bones_Timer -= diff;

            //Berserk_Timer
            if (Berserk_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_BERSERK_ALL);
                Berserk_Timer = 15000;
            } else Berserk_Timer -= diff;

            //Shadowflame_Breath_Timer
            if (Shadowflame_Breath_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_SHADOWFLAME_BREATH_H10);
                Shadowflame_Breath_Timer = 7000;
            } else Shadowflame_Breath_Timer -= diff;

            //Tail_Lash_Timer
            if (Tail_Lash_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_TAIL_LASH_H10);
                Tail_Lash_Timer = 10000;
            } else Tail_Lash_Timer -= diff;

            //Children_of_Deathwing_Timer
            if (Children_of_Deathwing_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_CHILDREN_OF_DEATHWING_ALL);
                Children_of_Deathwing_Timer = 20000;
            } else Children_of_Deathwing_Timer -= diff;
            //Dominion_Timer
            if (Dominion_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_DOMINION_H);
                Dominion_Timer = 25000;
            } else Dominion_Timer -= diff;
            //Explosive_Cinders_Timer
            if (Explosive_Cinders_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_EXPLOSIVE_CINDERS_H);
                Explosive_Cinders_Timer = 17000;
            } else Explosive_Cinders_Timer -= diff;
            //Shadow_of_Cowardige_Timer
            if (Explosive_Cinders_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_SHADOW_OF_COWARDIGE_ALL);
                Shadow_of_Cowardige_Timer = 30000;
            } else Shadow_of_Cowardige_Timer -= diff;
            //Shadowblaze_Spark_Timer
            if (Shadowblaze_Spark_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_SHADOWBLAZE_SPARK_ALL);
                Shadowblaze_Spark_Timer = 25000;
            } else Shadowblaze_Spark_Timer -= diff;

            //ClassCall_Timer
            if (ClassCall_Timer <= diff)
            {
                //Cast a random class call
                //On official it is based on what classes are currently on the hostil list
                //but we can't do that yet so just randomly call one

                switch (urand(0, 8))
                {
                    case 0:
                        DoScriptText(SAY_MAGE, me);
                        DoCast(me, SPELL_MAGE);
                        break;
                    case 1:
                        DoScriptText(SAY_WARRIOR, me);
                        DoCast(me, SPELL_WARRIOR);
                        break;
                    case 2:
                        DoScriptText(SAY_DRUID, me);
                        DoCast(me, SPELL_DRUID);
                        break;
                    case 3:
                        DoScriptText(SAY_PRIEST, me);
                        DoCast(me, SPELL_PRIEST);
                        break;
                    case 4:
                        DoScriptText(SAY_PALADIN, me);
                        DoCast(me, SPELL_PALADIN);
                        break;
                    case 5:
                        DoScriptText(SAY_SHAMAN, me);
                        DoCast(me, SPELL_SHAMAN);
                        break;
                    case 6:
                        DoScriptText(SAY_WARLOCK, me);
                        DoCast(me, SPELL_WARLOCK);
                        break;
                    case 7:
                        DoScriptText(SAY_HUNTER, me);
                        DoCast(me, SPELL_HUNTER);
                        break;
                    case 8:
                        DoScriptText(SAY_ROGUE, me);
                        DoCast(me, SPELL_ROGUE);
                        break;
                }

                ClassCall_Timer = 35000 + (rand() % 5000);
            } else ClassCall_Timer -= diff;

            //Phase3 begins when we are below X health
            if (!Phase3 && HealthBelowPct(20))
            {
                Phase3 = true;
                DoScriptText(SAY_RAISE_SKELETONS, me);
            }

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_nefarian2()
{
    new boss_nefarian2();
}