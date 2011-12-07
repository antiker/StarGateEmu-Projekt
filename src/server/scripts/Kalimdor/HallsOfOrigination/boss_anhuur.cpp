#include "ScriptPCH.h"

/*
Script 50%
*/

#define spell_ardente 94951 // Lumière ardente
#define spell_divine 75592 // Rétribution divine
#define spell_divine_H 94949

#define SAY_AGGRO "Turn back, intruders ! These halls must not be disturbed !"
#define SAY_DIED "What... have you... done?"

/*######
##Ammunae
######*/
class boss_anhuur: public CreatureScript
{
public:
 boss_anhuur() : CreatureScript("boss_anhuur") { }

 struct boss_anhuurAI : public ScriptedAI
    {
        boss_anhuurAI(Creature *c) : ScriptedAI(c) {}

uint32 ardente;
        uint32 divine;

        void Reset()
        {
           ardente = 15000;
divine = 10000;
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

            if (ardente<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_ardente);
                ardente = 15000;
            }
            else
                ardente -= diff;

            if (divine<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, IsHeroic() ? spell_divine_H : spell_divine);
                divine = 10000;
            }
            else
                divine -= diff;

if (!UpdateVictim())
                    return;

DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_anhuurAI (pCreature);
    }

};

#define spell_crochet 74538 // Crochets empoisonnés

/*######
##Vipère de la Fosse
######*/
class mob_viper: public CreatureScript
{
public:
 mob_viper() : CreatureScript("mob_viper") { }

 struct mob_viperAI : public ScriptedAI
    {
        mob_viperAI(Creature *c) : ScriptedAI(c) {}

uint32 crochet;

        void Reset()
        {
           crochet = 15000;
        }

        void UpdateAI(const uint32 diff)
        {
                if (!UpdateVictim())
                    return;

            if (crochet<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_crochet);
                crochet = 15000;
            }
            else
                crochet -= diff;

if (!UpdateVictim())
                    return;

DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_viperAI (pCreature);
    }

};

void AddSC_boss_anhuur()
{
    new boss_anhuur();
	new mob_viper();
}