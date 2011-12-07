#include "ScriptPCH.h"

#define spell_supernova 74136 // Supernova
#define spell_astral 74366 // Pluie Astral
#define spell_bouclier 74372 // Bouclier

#define SAY_AGGRO "Des siècles de ténèbres… par votre faute."
#define SAY_DIED "Mon lustre… se ternit."

class boss_isiset: public CreatureScript
{
public:
 boss_isiset() : CreatureScript("boss_isiset") { }

 struct boss_isisetAI : public ScriptedAI
    {
        boss_isisetAI(Creature *c) : ScriptedAI(c) {}

uint32 supernova;
        uint32 astral;
        uint32 bouclier_Timer;

        void Reset()
        {
           supernova = 10000;
           astral = 18000;
bouclier_Timer = 15000;
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

            if (supernova<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_supernova);
                supernova = 10000;
            }
            else
                supernova -= diff;

            if (astral<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_astral);
                astral = 18000;
            }
            else
                astral -= diff;

if (!UpdateVictim())
                    return;

if (bouclier_Timer <= diff)
            {
                DoCast(me->getVictim(), spell_bouclier, true);

                bouclier_Timer = 15000;
            } else bouclier_Timer -= diff;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_isisetAI (pCreature);
    }

};

void AddSC_boss_isiset()
{
    new boss_isiset();
}