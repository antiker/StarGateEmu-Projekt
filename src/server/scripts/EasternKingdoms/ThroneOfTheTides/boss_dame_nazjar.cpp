#include "ScriptPCH.h"
#include "throne_of_the_tides.h"

// Boss
#define SPELL_FUNGAL_SPORES 76001
#define SPELL_SHOCK_BLAST 76008
#define SPELL_SUMMON_GEYSER 75722
#define SPELL_WATERSPOUT 75683
#define SPELL_WATERSPOUT_SUMMON DUNGEON_MODE(90495,90497) // summons tornado every 7/3 secs.
// Adds
#define SPELL_CHAIN_LIGHTNING 75813
#define SPELL_LIGHTNING_SURGE 75992
#define SPELL_ARC_SLASH 75907
#define SPELL_ENRAGE 75998

enum Yells
{
    SAY_AGGRO = -1643001,
    SAY_66_PRECENT = -1643002,
    SAY_33_PRECENT = -1643003,
    SAY_DEATH = -1643004,
    SAY_KILL_1 = -1643005,
    SAY_KILL_2 = -1643006,
};

enum Phases
{
    PHASE_ALL = 0,
    PHASE_NORMAL = 1,
    PHASE_WATERSPOUT = 2,
};

class boss_lady_nazjar : public CreatureScript
{
public:
    boss_lady_nazjar() : CreatureScript("boss_lady_nazjar") { }

    struct boss_lady_nazjarAI : public ScriptedAI
    {
        boss_lady_nazjarAI(Creature* pCreature) : ScriptedAI(pCreature)
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
            pInstance = pCreature->GetInstanceScript();
        }

        std::list<uint64> SummonList;

        InstanceScript *pInstance;

        uint8 Phase;
        bool Phased;
        uint8 SpawnCount;
        uint8 PhaseCount;

        uint32 FungalSporesTimer;
        uint32 ShockBlastTimer;
        uint32 SummonGeyserTimer;
        uint32 Phase2EndTimer;

        void Reset()
        {
            Phased = false;
            RemoveSummons();

            Phase = PHASE_NORMAL;

            SpawnCount = 3;
            PhaseCount = 0;

            FungalSporesTimer = urand(8000,13000);
            ShockBlastTimer = 22000;
            SummonGeyserTimer = urand(11000,16000);

            me->RemoveAurasDueToSpell(SPELL_WATERSPOUT);
            me->RemoveAurasDueToSpell(SPELL_WATERSPOUT_SUMMON);

            me->GetMotionMaster()->MoveTargetedHome();

            if (pInstance)
                pInstance->SetData(DATA_LADY_NAZJAR_EVENT, NOT_STARTED);
        }

        void SummonedCreatureDespawn(Creature* summon)
        {
            switch(summon->GetEntry())
            {
                case NPC_SUMMONED_WITCH:
                case NPC_SUMMONED_GUARD:
                    SpawnCount--;
                    break;
            }
        }

        void RemoveSummons()
        {
            if (SummonList.empty())
                return;

            for (std::list<uint64>::const_iterator itr = SummonList.begin(); itr != SummonList.end(); ++itr)
            {
                if (Creature* pTemp = Unit::GetCreature(*me, *itr))
                    if (pTemp)
                        pTemp->DisappearAndDie();
            }
            SummonList.clear();
        }

        void KilledUnit(Unit* /*victim*/)
        {
            DoScriptText(RAND(SAY_KILL_1,SAY_KILL_2), me);
        }

        void JustSummoned(Creature* pSummon)
        {
            switch (pSummon->GetEntry())
            {
                case NPC_SUMMONED_WITCH:
                case NPC_SUMMONED_GUARD:
                    if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                        pSummon->AI()->AttackStart(pTarget);
                    SummonList.push_back(pSummon->GetGUID());
                    break;
            }
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoScriptText(SAY_AGGRO, me);

            if (pInstance)
                pInstance->SetData(DATA_LADY_NAZJAR_EVENT, IN_PROGRESS);
        }

        void JustDied(Unit* /*pKiller*/)
        {
            me->SummonCreature(BOSS_COMMANDER_ULTHOK, 59.185f, 802.251f, 805.730f, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60480000);
            DoScriptText(SAY_DEATH, me);
            RemoveSummons();

            if (pInstance)
                pInstance->SetData(DATA_LADY_NAZJAR_EVENT, DONE);
        }

        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;

            if (SpawnCount == 0 && Phase == PHASE_WATERSPOUT)
            {
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, false);
                SpawnCount = 3;
                SetCombatMovement(true);
                Phase = PHASE_NORMAL;
                Phased = false;
                FungalSporesTimer = urand(8000,13000);
                ShockBlastTimer = 22000;
                SummonGeyserTimer = urand(11000,16000);
                me->RemoveAurasDueToSpell(SPELL_WATERSPOUT);
                me->RemoveAurasDueToSpell(SPELL_WATERSPOUT_SUMMON);
            }

            if (me->HealthBelowPct(67) && Phase == PHASE_NORMAL && PhaseCount == 0)
            {
                DoScriptText(SAY_66_PRECENT, me);

                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
                PhaseCount++;
                SetCombatMovement(false);
                Phase = PHASE_WATERSPOUT;
                DoTeleportTo(192.056f, 802.527f, 807.638f, 3);
                DoCast(me, SPELL_WATERSPOUT);
                me->AddAura(SPELL_WATERSPOUT_SUMMON, me);
                Position pos;
                me->GetPosition(&pos);
                me->SummonCreature(NPC_SUMMONED_WITCH, pos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                me->SummonCreature(NPC_SUMMONED_WITCH, pos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                me->SummonCreature(NPC_SUMMONED_GUARD, pos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                Phase2EndTimer = 60000;
            }

            if (me->HealthBelowPct(34) && Phase == PHASE_NORMAL && PhaseCount == 1)
            {
                me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_INTERRUPT, true);
                DoScriptText(SAY_33_PRECENT, me);

                PhaseCount++;
                SetCombatMovement(false);
                Phase = PHASE_WATERSPOUT;
                DoTeleportTo(192.056f, 802.527f, 807.638f, 3);
                DoCast(me, SPELL_WATERSPOUT);
                me->AddAura(SPELL_WATERSPOUT_SUMMON, me);
                Position pos;
                me->GetPosition(&pos);
                me->SummonCreature(NPC_SUMMONED_WITCH, pos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                me->SummonCreature(NPC_SUMMONED_WITCH, pos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                me->SummonCreature(NPC_SUMMONED_GUARD, pos, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
                Phase2EndTimer = 60000;
            }

            if (FungalSporesTimer <= diff && Phase == PHASE_NORMAL)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(target, SPELL_FUNGAL_SPORES);
                FungalSporesTimer = urand(5000,7000);
            } else FungalSporesTimer -= diff;

            if (ShockBlastTimer <= diff && Phase == PHASE_NORMAL)
            {
                DoCastVictim(SPELL_SHOCK_BLAST);
                ShockBlastTimer = urand(12000,15000);
            } else ShockBlastTimer -= diff;

            if (SummonGeyserTimer <= diff && Phase == PHASE_NORMAL)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(target, SPELL_SUMMON_GEYSER);
                SummonGeyserTimer = urand(13000,16000);
            } else SummonGeyserTimer -= diff;

            if (Phase == PHASE_WATERSPOUT)
            {
                if (Phase2EndTimer <= diff)
                {
                    SpawnCount = 3;
                    SetCombatMovement(true);
                    Phase = PHASE_NORMAL;
                    Phased = false;
                    FungalSporesTimer = urand(8000,13000);
                    ShockBlastTimer = 22000;
                    SummonGeyserTimer = urand(11000,16000);
                    me->RemoveAurasDueToSpell(SPELL_WATERSPOUT);
                    me->RemoveAurasDueToSpell(SPELL_WATERSPOUT_SUMMON);
                } else Phase2EndTimer -= diff;
            }


            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature *pCreature) const
    {
        return new boss_lady_nazjarAI (pCreature);
    }
};

void AddSC_boss_lady_nazjar()
{
    new boss_lady_nazjar();
}