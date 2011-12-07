#define SPELL_ALPHA_BEAMS 39788
#define H_SPELL_ALPHA_BEAMS 39788
#define SPELL_CRUMBLING_RUIN 75609
#define H_SPELL_CRUMBLING_RUIN 91206
//#define SPELL_DESTRUCTION_PROTOCOL 77437
#define SPELL_NEMESIS_STRIKE 75604
#define H_SPELL_NEMESIS_STRIKE 91175
#define SPELL_OMEGA_STANCE 75622
#define H_SPELL_OMEGA_STANCE 91208

#define SAY_AGGRO "."
#define SAY_DIED "…"
#define SAY_OMEGA "."

class boss_anraphet: public CreatureScript
{
public:
 boss_anraphet() : CreatureScript("boss_anraphet") { }

 struct boss_anraphetAI : public ScriptedAI
    {
        boss_anraphetAI(Creature *c) : ScriptedAI(c) {}

uint32 nemesis;
uint32 rayon;
uint32 omega;
uint32 ruine;

        void Reset()
        {
           nemesis = 2000;
rayon = 1000;
omega = 14000;
ruine = 16000;
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
           
            if (nemesis <= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, SPELL_NEMESIS_STRIKE);
                nemesis = 2000;
            }
            else
                nemesis -= diff;

            if (omega <= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, SPELL_OMEGA_STANCE);
me->MonsterYell(SAY_OMEGA, LANG_UNIVERSAL, NULL);
                omega = 14000;
            }
            else
                omega -= diff;

            if (rayon <= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, SPELL_ALPHA_BEAMS);
                rayon = 1000;
            }
            else
                rayon -= diff;

            if (ruine <= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, SPELL_CRUMBLING_RUIN);
                ruine = 16000;
            }
            else
                ruine -= diff;

if (!UpdateVictim())
                    return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_anraphetAI (pCreature);
    }

};

void AddSC_boss_anraphet()
{
    new boss_anraphet();
}