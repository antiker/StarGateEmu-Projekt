#include "ScriptPCH.h"
#include"ScriptedCreature.h"
#include"grim_batol.h"

#define spell_fireball 75245 // Trait de l'ombre ardent
#define spell_invo 75218 // Invocation d'esprit
#define spell_protec 76303 // Protection du Crépuscule

#define SAY_AGGRO "Ihr solltet besser vorbereitet sein !"
#define SAY_DIED "Schluss, dieser Alptraum ist vorbei ..."

class boss_drahga: public CreatureScript
{
public:
 boss_drahga() : CreatureScript("boss_drahga") { }

 struct boss_drahgaAI : public BossAI
    {
        boss_drahgaAI(Creature *c) : BossAI(c, DATA_DRAHGA_SHADOWBURNER)
		{}

        uint32 fireball;
uint32 invo;
uint32 protec;

        void Reset()
        {
           fireball = 3000;
invo = 3000;
protec = 0;
        }

        void EnterCombat(Unit* /*who*/)
        {
		me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);
        }

        void JustDied(Unit* /*killer*/)
        {
		_JustDied();
		summons.DespawnAll();
		if (instance)
        instance->SetData(DATA_DRAHGA_SHADOWBURNER, DONE);
		me->MonsterYell(SAY_DIED, LANG_UNIVERSAL, NULL);
        }

        void UpdateAI(const uint32 diff)
        {
                if (!UpdateVictim())
                    return;

            if (fireball<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_fireball);
                fireball = 3000;
            }
            else
                fireball -= diff;

            if (invo<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_invo);
                invo = 5000;
            }
            else
                invo -= diff;

if(!HealthAbovePct(30))
{
            if (protec<= diff)
            {
                DoCast(spell_protec);
            } else protec -= diff;
}

if (!UpdateVictim())
                    return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_drahgaAI (pCreature);
    }

};

#define spell_nova 75238 // Supernova

class mob_esprit: public CreatureScript
{
public:
 mob_esprit() : CreatureScript("mob_esprit") { }

 struct mob_espritAI : public ScriptedAI
    {
        mob_espritAI(Creature *c) : ScriptedAI(c) {}

        uint32 nova;

        void Reset()
        {
           nova = 5000;
        }

        void UpdateAI(const uint32 diff)
        {
                if (!UpdateVictim())
                    return;

            if (nova<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_nova);
                nova = 5000;
            }
            else
                nova -= diff;

if (!UpdateVictim())
                    return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_espritAI (pCreature);
    }

};

#define spell_transfert 75328 // Transfert
#define spell_coup 75271 // Ballayage
#define spell_flamme 75321 // Flamme de Valiona
#define spell_devorante_H 90950 // Flamme dévorante de Valiona

#define SAY_FUITE "I will not die for you, Drahga."

class mob_valiona: public CreatureScript
{
public:
 mob_valiona() : CreatureScript("mob_valiona") { }

 struct mob_valionaAI : public ScriptedAI
    {
        mob_valionaAI(Creature *c) : ScriptedAI(c) {}

        uint32 transfert;
uint32 flamme;
uint32 coup;

        void Reset()
        {
           transfert = 120000;
           flamme = 10000;
           coup = 2000;
        }

        void UpdateAI(const uint32 diff)
        {
                if (!UpdateVictim())
                    return;

            if (flamme<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, IsHeroic() ? spell_devorante_H : spell_flamme);
                flamme = 10000;
            }
            else
                flamme -= diff;

            if (coup<= diff)
            {
                if (Unit *pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                                                DoCast(pTarget, spell_coup);
                coup = 2000;
            }
            else
                coup -= diff;

if(!HealthAbovePct(20))
{
            if (transfert<= diff)
            {
                DoCast(spell_transfert);
me->MonsterYell(SAY_FUITE, LANG_UNIVERSAL, NULL);
            } else transfert -= diff;
}

if (!UpdateVictim())
                    return;

            DoMeleeAttackIfReady();
        }
    };

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_valionaAI (pCreature);
    }

};

void AddSC_boss_drahga()
{
    new boss_drahga();
new mob_valiona();
new mob_esprit();
}