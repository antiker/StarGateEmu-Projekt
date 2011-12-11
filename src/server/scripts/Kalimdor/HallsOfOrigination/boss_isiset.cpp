#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptPCH.h"
#include "halls_of_origination.h"

class OrientationCheck : public std::unary_function<Unit*, bool>
{
    public:
        explicit OrientationCheck(Unit* _caster) : caster(_caster) { }
        bool operator() (Unit* unit)
        {
            return !unit->isInFront(caster, 40.0f, 2.5f);
        }

    private:
        Unit* caster;
};

#define SAY_AGGRO "Jahrhunderte der Dunkelheit ... wegen dir !"
#define SAY_SUPERNOVA ""
#define SAY_KILL_1 "Mein Glanz trübt ..."
#define SAY_DEATH_1 "Ihr werdet schon sehen !"



enum Spells
{
    SPELL_SUPERNOVA = 74136,
    SPELL_ASTRAL_RAIN = 74370,
    SPELL_CELESTIAL_CALL_P1 = 74362,
    SPELL_CELESTIAL_CALL_P2 = 74355,
    SPELL_CELESTIAL_CALL_P3 = 74364,
    SPELL_VEIL_OF_SKY_P1 = 74133,
    SPELL_VEIL_OF_SKY_P2 = 74372,
    SPELL_VEIL_OF_SKY_P3 = 74373,
};

class boss_isiset : public CreatureScript
{
    public:
        boss_isiset() : CreatureScript("boss_isiset") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_isisetAI(creature);
        }

        struct boss_isisetAI : public ScriptedAI
        {
            boss_isisetAI(Creature* creature) : ScriptedAI(creature)
            {
                pInstance = creature->GetInstanceScript();
                SetCombatMovement(true);
            }

            std::list<uint64> SummonList;

            InstanceScript *pInstance;

            uint32 SupernovaTimer;
            uint32 AstralRainTimer;
            uint32 CelestialCallPhase3Timer;
            uint32 CelestialCallPhase2Timer;
            uint32 CelestialCallPhase1Timer;
            uint32 VeilOfSkyPhase3Timer;
            uint32 VeilOfSkyPhase2Timer;
            uint32 VeilOfSkyPhase1Timer;
            uint32 Phase;
            bool Phased;

            bool AstralRain, VeilOfSky, CelestialCall;

            void EnterCombat(Unit *who)
            {
                me->MonsterYell(SAY_AGGRO, 0, 0);
            }

            void KilledUnit(Unit* victim)
            {
                me->MonsterYell(SAY_KILL_1, 0, 0);
            }

            void JustDied(Unit* Killer)
            {
                me->MonsterYell(SAY_DEATH_1, 0, 0);
            }

            void Reset()
            {
                RemoveSummons();
                SupernovaTimer = 15000+rand()%5000;
                AstralRainTimer = 10000;
                CelestialCallPhase3Timer = 25000;
                CelestialCallPhase2Timer = 25000;
                CelestialCallPhase1Timer = 25000;
                VeilOfSkyPhase3Timer = 20000;
                VeilOfSkyPhase2Timer = 20000;
                VeilOfSkyPhase1Timer = 20000;
                Phased = false;
                AstralRain = true;
                VeilOfSky = true;
                CelestialCall = true;
                Phase = 0;
            }

            void SummonedCreatureDespawn(Creature* summon)
            {
                switch(summon->GetEntry())
                {
                    case 39720: // Astral Rain
                        AstralRain = false;
                        break;
                    case 39721: // Celestial Call
                        CelestialCall = false;
                        break;
                    case 39722: // Veil of Sky
                        VeilOfSky = false;
                        break;
                }
                RemoveSummons();
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

            void JustSummoned(Creature* pSummon)
            {
                SummonList.push_back(pSummon->GetGUID());
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                if ((me->GetHealth() * 100 / me->GetMaxHealth() <= 66) && Phase == 0)
                {
                    Phase = 1;
                    Phased = true;
                    Position pos;
                    me->GetPosition(&pos);
                    me->SummonCreature(39720, pos, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                    me->SummonCreature(39721, pos, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                    me->SummonCreature(39722, pos, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                }

                if ((me->GetHealth() * 100 / me->GetMaxHealth() <= 33) && Phase == 1)
                {
                    Phase = 2;
                    Phased = true;
                    Position pos;
                    me->GetPosition(&pos);
                    if (AstralRain == true)
                        me->SummonCreature(39720, pos, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                    if (CelestialCall == true)
                        me->SummonCreature(39721, pos, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                    if (VeilOfSky == true)
                        me->SummonCreature(39722, pos, TEMPSUMMON_CORPSE_DESPAWN, 1000);
                }

                if (Phase == 0)
                {
                    if (CelestialCallPhase1Timer <= diff && Phased == false && CelestialCall == true)
                    {
                        DoCast(me, SPELL_CELESTIAL_CALL_P1);
                        CelestialCallPhase1Timer = 45000;
                    } else CelestialCallPhase1Timer -= diff;

                    if (VeilOfSkyPhase1Timer <= diff && Phased == false && VeilOfSky == true)
                    {
                        DoCast(me, SPELL_VEIL_OF_SKY_P1);
                        VeilOfSkyPhase1Timer = 45000;
                    } else VeilOfSkyPhase1Timer -= diff;
                }

                if (Phase == 1)
                {
                    if (CelestialCallPhase2Timer <= diff && Phased == false && CelestialCall == true)
                    {
                        DoCast(me, SPELL_CELESTIAL_CALL_P2);
                        CelestialCallPhase2Timer = 45000;
                    } else CelestialCallPhase2Timer -= diff;

                    if (VeilOfSkyPhase2Timer <= diff && Phased == false && VeilOfSky == true)
                    {
                        DoCast(me, SPELL_VEIL_OF_SKY_P2);
                        VeilOfSkyPhase2Timer = 45000;
                    } else VeilOfSkyPhase2Timer -= diff;
                }

                if (Phase == 2)
                {
                    if (CelestialCallPhase3Timer <= diff && Phased == false && CelestialCall == true)
                    {
                        DoCast(me, SPELL_CELESTIAL_CALL_P3);
                        CelestialCallPhase3Timer = 45000;
                    } else CelestialCallPhase3Timer -= diff;

                    if (VeilOfSkyPhase3Timer <= diff && Phased == false && VeilOfSky == true)
                    {
                        DoCast(me, SPELL_VEIL_OF_SKY_P3);
                        VeilOfSkyPhase3Timer = 45000;
                    } else VeilOfSkyPhase3Timer -= diff;
                }

                if (SupernovaTimer <= diff && Phased == false)
                {
                    me->MonsterYell(SAY_SUPERNOVA, 0, 0);
                    DoCast(me->getVictim(), SPELL_SUPERNOVA);
                    SupernovaTimer = 15000+rand()%5000;
                } else SupernovaTimer -= diff;

                if (AstralRainTimer <= diff && Phased == false && CelestialCall == true)
                {
                    DoCast(SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true), SPELL_ASTRAL_RAIN);
                    AstralRainTimer = 10000;
                } else AstralRainTimer -= diff;

                DoMeleeAttackIfReady();
            }
        };
};

class spell_isiset_supernova : public SpellScriptLoader
{
    public:
        spell_isiset_supernova() : SpellScriptLoader("spell_isiset_supernova") { }
        class spell_isiset_supernova_SpellScript : public SpellScript
        {
            PrepareSpellScript(spell_isiset_supernova_SpellScript);
            void FilterTargets(std::list<Unit*>& unitList)
            {
                unitList.remove_if(OrientationCheck(GetCaster()));
            }

            void Register()
            {
                //OnUnitTargetSelect += SpellUnitTargetFn(spell_isiset_supernova_SpellScript::FilterTargets, EFFECT_0, TARGET_UNIT_AREA_ENEMY_SRC);
                //OnUnitTargetSelect += SpellUnitTargetFn(spell_isiset_supernova_SpellScript::FilterTargets, EFFECT_1, TARGET_UNIT_AREA_ENEMY_SRC);
            }
        };

        SpellScript *GetSpellScript() const
        {
            return new spell_isiset_supernova_SpellScript();
        }
};

void AddSC_boss_isiset()
{
    new boss_isiset();
    new spell_isiset_supernova();
}