#define spell_floraison 76043
#define spell_conso 75790

#define SAY_AGGRO "!"
#define SAY_DIED "…"

/*######
##Ammunae
######*/
class boss_ammunae: public CreatureScript
{
public:
 boss_ammunae() : CreatureScript("boss_ammunae") { }

 struct boss_ammunaeAI : public ScriptedAI
    {
        boss_ammunaeAI(Creature *c) : ScriptedAI(c) {}

uint32 floraison;
        uint32 conso;

        void Reset()
        {
           floraison = 15000;
conso = 5000;
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

            if (floraison<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_floraison);
                floraison = 15000;
            }
            else
                floraison -= diff;

            if (conso<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_conso);
                conso = 5000;
            }
            else
                conso -= diff;

if (!UpdateVictim())
                    return;

DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_ammunaeAI (pCreature);
    }

};

/*######
##Cosse de Boutures
######*/

/*######
##Fleur de pétale-de-sang
######*/

/*######
##Spore
######*/

void AddSC_boss_ammunae()
{
    new boss_ammunae();
}