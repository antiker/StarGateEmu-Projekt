#include "ScriptPCH.h"

/*
Script 50%
*/
#define spell_chaos 77069 // Trait du Chaos
#define spell_chaos_H 89873
#define spell_vide 77030
#define spell_explo 76681
#define spell_graine 76870

// Setesh seeks a portal every 25 seconds

#define SAY_AGGRO "Ce que vous ne contrôlez pas vous fait peur. Mais pourrez-vous contrôler votre peur ?"
#define SAY_DIED "Oui ! Domptez… votre… haine…"

class boss_setesh: public CreatureScript
{
public:
 boss_setesh() : CreatureScript("boss_setesh") { }

 struct boss_seteshAI : public ScriptedAI
    {
        boss_seteshAI(Creature *c) : ScriptedAI(c) {}

uint32 chaos;
uint32 vide;
uint32 explo;
uint32 graine;

        void Reset()
        {
           chaos = 5000;
vide = 10000;
explo = 7000;
graine = 15000;
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
           
            if (chaos <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, IsHeroic() ? spell_chaos_H : spell_chaos);
                chaos = 5000;
            }
            else
                chaos -= diff;

            if (vide <= diff)
            {
                DoCast(me->getVictim(), spell_vide);
                vide = 10000;
            }
            else
                vide -= diff;

            if (explo <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_explo);
                explo = 7000;
            }
            else
                explo -= diff;

            if (graine <= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_graine);
                graine = 15000;
            }
            else
                graine -= diff;

if (!UpdateVictim())
                    return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_seteshAI (pCreature);
    }

};

void AddSC_boss_setesh()
{
    new boss_setesh();
}