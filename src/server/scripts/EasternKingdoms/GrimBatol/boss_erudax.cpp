#include "ScriptPCH.h"
#include"ScriptedCreature.h"
#include"grim_batol.h"

#define spell_ombre 82622
#define spell_trombe 75664
#define spell_spawn 75704

#define SAY_AGGRO "Kommt!!!  Betritt... das Chaos !"
#define SAY_DIED "Ywaq maq oou; ywaq maq ssaggh. Ywaq ma shg'fhn."

class boss_erudax: public CreatureScript
{
public:
 boss_erudax() : CreatureScript("boss_erudax") { }

 struct boss_erudaxAI : public ScriptedAI
    {
        boss_erudaxAI(Creature *c) : ScriptedAI(c) {}

uint32 ombre;
uint32 trombe;
uint32 spawn;

        void Reset()
        {
           ombre = 10000;
           trombe = 15000;
spawn = 30000;
        }

        void EnterCombat(Unit* /*who*/)
        {
me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);
        }

        void JustDied(Unit* /*killer*/)
        {
me->MonsterYell(SAY_DIED, LANG_UNIVERSAL, NULL);
        }

        void UpdateAI(const uint32 diff)
        {
                if (!UpdateVictim())
                    return;
           
            if (ombre <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_ombre);
                ombre = 10000;
            }
            else
                ombre -= diff;

            if (trombe <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_trombe);
                trombe = 15000;
            }
            else
                trombe -= diff;

            if (spawn <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_spawn);
                spawn = 30000;
            }
            else
                spawn -= diff;

if (!UpdateVictim())
                    return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_erudaxAI (pCreature);
    }

};

/*
Mob Erudax id = 40600
*/

#define spell_corruption 75520
#define spell_umbrale 75763
#define spell_siphon 75755

class mob_erudax: public CreatureScript
{
public:
 mob_erudax() : CreatureScript("mob_erudax") { }

 struct mob_erudaxAI : public ScriptedAI
    {
        mob_erudaxAI(Creature *c) : ScriptedAI(c) {}

uint32 corruption;
uint32 umbrale;
uint32 siphon;

        void Reset()
        {
           corruption = 10000;
           umbrale = 15000;
siphon = 20000;
        }

        void UpdateAI(const uint32 diff)
        {
                if (!UpdateVictim())
                    return;
           
            if (corruption <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_corruption);
                corruption = 10000;
            }
            else
                corruption -= diff;

            if (umbrale <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_umbrale);
                umbrale = 15000;
            }
            else
                umbrale -= diff;

            if (siphon <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_siphon);
                siphon = 20000;
            }
            else
                siphon -= diff;

if (!UpdateVictim())
                    return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_erudaxAI (pCreature);
    }

};

void AddSC_boss_erudax()
{
    new boss_erudax();
new mob_erudax();
}