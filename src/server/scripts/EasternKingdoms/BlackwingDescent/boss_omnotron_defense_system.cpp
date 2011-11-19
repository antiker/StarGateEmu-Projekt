/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#include "ScriptPCH.h"
#include "blackwing_descent.h"

enum eSpell
{
    SPELL_ARCANE_ANNIHILATOR    = 79710,
	SPELL_Energieumwandlung		= 79729,
	SPELL_KonvertierteEnergie	= 79735,

	SPELL_Blitzableiter			= 79888,
	SPELL_ElektrischeEntladung	= 79879,
	SPELL_InstabilerSchild		= 79900,
	SPELL_Schattenmacht			= 92048,

	SPELL_Sicherheitsvorkehrung	= 79023,
	SPELL_Zielerfassung			= 79501,
	SPELL_Flammenwerfer			= 79505,
	SPELL_Barriere				= 79582,

	SPELL_ChemischeBombe		= 80157,
	SPELL_Giftprotokoll			= 91513,
	SPELL_GiftgetränkterPanzer	= 79835
};

enum eAchievments
{
    ACHIEV_TIMED_START_EVENT                      = 17726,
};

class boss_toxitron : public CreatureScript
{
public:
    boss_toxitron() : CreatureScript("boss_toxitron") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_toxitronAI (pCreature);
    }

    struct boss_toxitronAI : public BossAI
    {
        boss_toxitronAI(Creature* pCreature) : BossAI(pCreature, DATA_TOXITRON)
        {

        }

		uint32 ChemischeBombeTimer;
		uint32 GiftprotokollTimer;
		uint32 GiftgetränkterPanzerTimer;

        void Reset()
        {
			ChemischeBombeTimer = 5*IN_MILLISECONDS;
			GiftprotokollTimer = 5*IN_MILLISECONDS;
			GiftgetränkterPanzerTimer = 5*IN_MILLISECONDS;
			summons.DespawnAll();
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
			if (instance)
            {
            instance->SetData(DATA_TOXITRON, NOT_STARTED);
            instance->DoStopTimedAchievement(ACHIEVEMENT_TIMED_TYPE_EVENT, ACHIEV_TIMED_START_EVENT);
        }
		}



        void EnterCombat(Unit* /*who*/) {}

        void JustDied(Unit* /*Killer*/) 
        {
    	_JustDied();
		summons.DespawnAll();
        if (instance)
        instance->SetData(DATA_TOXITRON, DONE);


		}
        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;
			if (ChemischeBombeTimer <= Diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_ChemischeBombe, true);

                ChemischeBombeTimer = 50000;
			} else ChemischeBombeTimer -= Diff;

			if (GiftprotokollTimer <= Diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_Giftprotokoll, true);

                GiftprotokollTimer = 70000;
			} else GiftprotokollTimer -= Diff;

			if (GiftgetränkterPanzerTimer <= Diff)
            {
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
					me->CastSpell(target, SPELL_GiftgetränkterPanzer, true);
                GiftgetränkterPanzerTimer = 80000;
            } else GiftgetränkterPanzerTimer -= Diff;


			if (me->HasUnitState(UNIT_STAT_CASTING))
           return;
                
                        //if (HealthBelowPct(66))
                        //{
                        ////fire = 1;
                        //}
            //else

            DoMeleeAttackIfReady();
        }
    };
};

class boss_magmatron : public CreatureScript
{
public:
    boss_magmatron() : CreatureScript("boss_magmatron") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_magmatronAI (pCreature);
    }

    struct boss_magmatronAI : public BossAI
    {
        boss_magmatronAI(Creature* pCreature) : BossAI(pCreature, DATA_OMNOTRON_DEFENSE_SYSTEM)
        {

        }

		uint32 SicherheitsvorkehrungTimer;
		uint32 ZielerfassungTimer;
		uint32 FlammenwerferTimer;
		uint32 BarriereTimer;

        void Reset()
        {
            SicherheitsvorkehrungTimer = 5*IN_MILLISECONDS;
			ZielerfassungTimer = 5*IN_MILLISECONDS;
			FlammenwerferTimer = 5*IN_MILLISECONDS;
			BarriereTimer = 5*IN_MILLISECONDS;
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
        }

        void EnterCombat(Unit* /*who*/) { }

        void JustDied(Unit* /*Killer*/) 

	    {
		_JustDied();
        if (instance)
        instance->SetData(DATA_OMNOTRON_DEFENSE_SYSTEM, DONE);
		me->SummonCreature(42180, -324.8f, -398.1f, 213.8f, 1.4, TEMPSUMMON_CORPSE_DESPAWN, 0);
		
		}

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;
			if (SicherheitsvorkehrungTimer <= Diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_Sicherheitsvorkehrung, true);

                SicherheitsvorkehrungTimer = 60000;
			} else SicherheitsvorkehrungTimer -= Diff;

			if (ZielerfassungTimer <= Diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_Zielerfassung, true);

                ZielerfassungTimer = 50000;
			} else ZielerfassungTimer -= Diff;

			if (FlammenwerferTimer <= Diff)
            {
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
					me->CastSpell(target, SPELL_Flammenwerfer, true);
                FlammenwerferTimer = 45000;
            } else FlammenwerferTimer -= Diff;
			
				if (BarriereTimer <= Diff)
            {
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
					me->CastSpell(target, SPELL_Barriere, true);
                BarriereTimer = 120000;
            } else BarriereTimer -= Diff;

            DoMeleeAttackIfReady();
        }
    };
};

class boss_arcanotron : public CreatureScript
{
public:
    boss_arcanotron() : CreatureScript("boss_arcanotron") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_arcanotronAI (pCreature);
    }

    struct boss_arcanotronAI : public BossAI
    {
        boss_arcanotronAI(Creature* pCreature) : BossAI(pCreature, DATA_OMNOTRON_DEFENSE_SYSTEM)
        {

        }



        uint32 ArcaneAnnihilatorTimer;
		uint32 KonvertierteEnergieTimer;
		uint32 EnergieumwandlungTimer;

        void Reset()
        {
            instance->SetData(DATA_OMNOTRON_DEFENSE_SYSTEM, NOT_STARTED);

            ArcaneAnnihilatorTimer = 5*IN_MILLISECONDS;
			KonvertierteEnergieTimer = 5*IN_MILLISECONDS;
			EnergieumwandlungTimer = 5*IN_MILLISECONDS;
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
			me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_Energieumwandlung, true);



        }

        void EnterCombat(Unit* /*who*/)
        {
            instance->SetData(DATA_OMNOTRON_DEFENSE_SYSTEM, IN_PROGRESS);
        }

        void JustReachedHome()
        {
            instance->SetData(DATA_OMNOTRON_DEFENSE_SYSTEM, FAIL);
        }

        void JustDied(Unit* /*Killer*/)
        {
		_JustDied();
        if (instance)
	    instance->SetData(DATA_OMNOTRON_DEFENSE_SYSTEM, DONE);
				
		me->SummonCreature(42179, -340.6f, -386.4f, 213.9f, 1.0, TEMPSUMMON_CORPSE_DESPAWN, 0);
		
        }

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;
			
            if (ArcaneAnnihilatorTimer <= Diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_ARCANE_ANNIHILATOR, true);

                ArcaneAnnihilatorTimer = 55000;
			} else ArcaneAnnihilatorTimer -= Diff;

			if (ArcaneAnnihilatorTimer <= Diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_ARCANE_ANNIHILATOR, true);

                ArcaneAnnihilatorTimer = 75000;
			} else ArcaneAnnihilatorTimer -= Diff;

			if (KonvertierteEnergieTimer <= Diff)
            {
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
					me->CastSpell(target, SPELL_KonvertierteEnergie, true);
                KonvertierteEnergieTimer = 70000;
            } else KonvertierteEnergieTimer -= Diff;
			
				if (EnergieumwandlungTimer <= Diff)
            {
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
					me->CastSpell(target, SPELL_Energieumwandlung, true);
                EnergieumwandlungTimer = 50000;
            } else EnergieumwandlungTimer -= Diff;
           

            DoMeleeAttackIfReady();
        }
    };
};

class boss_electron : public CreatureScript
{
public:
    boss_electron() : CreatureScript("boss_electron") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_electronAI (pCreature);
    }

    struct boss_electronAI : public BossAI
    {
        boss_electronAI(Creature* pCreature) : BossAI(pCreature, DATA_OMNOTRON_DEFENSE_SYSTEM)
        {

        }

		uint32 BlitzableiterTimer;
		uint32 ElektrischeEntladungTimer;
		uint32 InstabilerSchildTimer;
		uint32 SchattenmachtTimer;

        void Reset()
        {
			instance->SetData(DATA_OMNOTRON_DEFENSE_SYSTEM, NOT_STARTED);

            BlitzableiterTimer = 5*IN_MILLISECONDS;
			ElektrischeEntladungTimer = 5*IN_MILLISECONDS;
			InstabilerSchildTimer = 5*IN_MILLISECONDS;
			SchattenmachtTimer = 5*IN_MILLISECONDS;
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);

        }

        void EnterCombat(Unit* /*who*/) { }

        void JustDied(Unit* /*Killer*/)

        {
		_JustDied();
        if (instance)
	    instance->SetData(DATA_OMNOTRON_DEFENSE_SYSTEM, DONE);
		me->SummonCreature(42178, -308.5f, -386.4f, 213.9f, 1.9, TEMPSUMMON_CORPSE_DESPAWN, 0);

        }

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;
			if (BlitzableiterTimer <= Diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_Blitzableiter, true);

                BlitzableiterTimer = 40000;
			} else BlitzableiterTimer -= Diff;

			if (ElektrischeEntladungTimer <= Diff)
            {
                if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    me->CastSpell(target, SPELL_ElektrischeEntladung, true);

                ElektrischeEntladungTimer = 35000;
			} else ElektrischeEntladungTimer -= Diff;

			if (InstabilerSchildTimer <= Diff)
            {
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
					me->CastSpell(target, SPELL_InstabilerSchild, true);
                InstabilerSchildTimer = 50000;
            } else InstabilerSchildTimer -= Diff;
			
				if (SchattenmachtTimer <= Diff)
            {
				if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
					me->CastSpell(target, SPELL_Schattenmacht, true);
                SchattenmachtTimer = 70000;
            } else SchattenmachtTimer -= Diff;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_omnotron_defense_system()
{
    new boss_toxitron();
    new boss_magmatron();
    new boss_arcanotron();
    new boss_electron();
}