#define spell_soleil 73872 // Coup de soleil
#define spell_invocation 80352 // Invocation d'un orbe du soleil
#define spell_enfer 87653 // Bond du feu d'enfer
#define spell_vent 89130 // Vents solaires
#define spell_feu 89131 // Feu solaire
#define spell_bene 76355 // Bénédiction du soleil

#define SAY_AGGRO "Sentez-vous cette caresse ? La chaleur bénie du soleil … ?"
#define SAY_DIED "Lumière étincelante… Emporte-moi."

/*######
##Rajh
######*/
class boss_rajh: public CreatureScript
{
public:
 boss_rajh() : CreatureScript("boss_rajh") { }

 struct boss_rajhAI : public ScriptedAI
    {
        boss_rajhAI(Creature *c) : ScriptedAI(c) {}

uint32 soleil;
        uint32 invocation;
uint32 enfer;
uint32 vent;
uint32 feu;
uint32 bene;

        void Reset()
        {
           soleil = 5000;
invocation = 10000;
           enfer = 3000;
vent = 60000;
           feu = 15000;
bene = 4000;
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

            if (soleil<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_soleil);
                soleil = 5000;
            }
            else
                soleil -= diff;

            if (invocation<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_invocation);
                invocation = 10000;
            }
            else
                invocation -= diff;

            if (enfer<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_enfer);
                enfer = 3000;
            }
            else
                enfer -= diff;

            if (vent<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_vent);
                vent = 60000;
            }
            else
                vent -= diff;

            if (feu<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_feu);
                feu = 15000;
            }
            else
                feu -= diff;

            if (bene<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_bene);
                bene = 4000;
            }
            else
                bene -= diff;

if (!UpdateVictim())
                    return;
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_rajhAI (pCreature);
    }

};

void AddSC_boss_rajh()
{
    new boss_rajh();
}