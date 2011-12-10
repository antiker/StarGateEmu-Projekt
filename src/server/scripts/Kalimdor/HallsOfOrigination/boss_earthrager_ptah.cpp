#include "ScriptPCH.h"
#include "WorldPacket.h"
#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "SpellScript.h"
#include "SpellAuraEffects.h"
#include "halls_of_origination.h"

#define SAY_AGGRO "More carrion for the swarm..."
#define SAY_DIED "Ptah... is... no more..."
#define SAY_SPELL "Dust to dust."


enum Spells
{
    SPELL_FLAME_BOLT = 77370,
    SPELL_RAGING_SMASH = 83650,
    SPELL_EARTH_POINT = 75339,
    SPELL_DUST_MOVE = 75547,
    SPELL_VORTEX_DUST = 93570,
};

enum Events
{
    EVENT_FLAME_BOLT,
    EVENT_RAGING_SMASH,
    EVENT_EARTH_POINT,
    EVENT_SUMMON,
    EVENT_DUST_MOVE,
    EVENT_VORTEX_DUST,
};

enum SummonIds
{
    NPC_HORROR = 40810,
    NPC_SCARAB = 40458,
};

const Position aSpawnLocations[3] =
{
    {-530.561584f, -370.613525f, 156.935913f, 5.081081f},
    {-484.478302f, -371.117584f, 155.954208f, 4.429200f},
    {-507.319977f, -381.939392f, 154.764664f, 4.700163f},
};

class boss_ptah : public CreatureScript
{
    public:
        boss_ptah() : CreatureScript("boss_ptah") {}

        struct boss_ptahAI : public BossAI
        {
			boss_ptahAI(Creature* creature) : BossAI(creature, DATA_EARTHRAGER_PTAH_EVENT)
            {
                instance = me->GetInstanceScript();
            }

            InstanceScript* instance;
            EventMap events;

			void Reset()
            {
                if (instance)
                    instance->SetData(DATA_EARTHRAGER_PTAH_EVENT, NOT_STARTED);
            }

            void EnterCombat(Unit * /*who*/)
            {
                EnterPhaseGround();
                me->MonsterYell(SAY_AGGRO, 0, 0);
				if (instance)
                    instance->SetData(DATA_EARTHRAGER_PTAH_EVENT, IN_PROGRESS);
            }

            void JustDied(Unit* /*killer*/)
            {
                me->MonsterYell(SAY_DIED, 0, 0);
				//GameObject* Door = me->FindNearestGameObject(GO_Lights_Hall_Door, 20000);
                //if (Door)
                //Door->SetGoState(GO_STATE_ACTIVE);
				me->SummonCreature(39908, -499.269f, 248.134f, 83.518f, 4.657f, TEMPSUMMON_CORPSE_DESPAWN, 0);
				me->SummonGameObject(GO_Controller, -499.406f, 246.231f, 82.90f, 1.5202f, 0, 0, 0, 0, 0);
            }

            void JustSummoned(Creature *pSummoned)
            {
                pSummoned->SetInCombatWithZone();
                if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM,0))
                    pSummoned->AI()->AttackStart(pTarget);
				if (instance)
                    instance->SetData(DATA_EARTHRAGER_PTAH_EVENT, DONE);


            }

            void SummonedCreatureDespawn(Creature *summon)
            {
                //Summons.Despawn(summon);
            }

            void EnterPhaseGround()
            {
                events.ScheduleEvent(EVENT_FLAME_BOLT, 7500);
                events.ScheduleEvent(EVENT_RAGING_SMASH, urand(4000, 10000));
                events.ScheduleEvent(EVENT_EARTH_POINT, 8000);
                events.ScheduleEvent(EVENT_SUMMON, 50000);
                events.ScheduleEvent(EVENT_DUST_MOVE, 15000);
                events.ScheduleEvent(EVENT_VORTEX_DUST, urand(14000, 20000));
            }

            void UpdateAI(const uint32 diff)
            {
                if (!UpdateVictim())
                    return;

                events.Update(diff);

                while (uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                    case EVENT_FLAME_BOLT:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, true))
                            DoCast(target, SPELL_FLAME_BOLT);
                        events.ScheduleEvent(EVENT_FLAME_BOLT, 7500);
                        return;
                    case EVENT_RAGING_SMASH:
                        DoCast(me->getVictim(), SPELL_RAGING_SMASH);
                        events.ScheduleEvent(EVENT_RAGING_SMASH, urand(4000, 10000));
                        return;
                    case EVENT_EARTH_POINT:
                        me->MonsterYell(SAY_SPELL, LANG_UNIVERSAL, NULL);
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM,1,100,true))
                            DoCast(target, SPELL_EARTH_POINT);
                        events.ScheduleEvent(EVENT_EARTH_POINT, 8000);
                        return;
                    case EVENT_SUMMON:
                        me->SummonCreature(NPC_HORROR, aSpawnLocations[0].GetPositionX(), aSpawnLocations[0].GetPositionY(), aSpawnLocations[0].GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_DESPAWN);
                        me->SummonCreature(NPC_SCARAB, aSpawnLocations[1].GetPositionX(), aSpawnLocations[1].GetPositionY(), aSpawnLocations[1].GetPositionZ(), 0.0f, TEMPSUMMON_CORPSE_DESPAWN);
                        events.ScheduleEvent(EVENT_SUMMON, 50000);
                        return;
                    case EVENT_DUST_MOVE:
                        if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, true))
                            DoCast(target, SPELL_DUST_MOVE);
                        events.ScheduleEvent(EVENT_DUST_MOVE, 15000);
                        return;
                    case EVENT_VORTEX_DUST:
                        if (IsHeroic())
                        {
                            DoCastAOE(SPELL_VORTEX_DUST);
                        }
                        events.ScheduleEvent(EVENT_VORTEX_DUST, urand(14000, 20000));
                        return;
                    }
                }
                DoMeleeAttackIfReady();
            }
        };

    CreatureAI* GetAI(Creature* creature) const
    {
                return new boss_ptahAI(creature);
    }
};

class go_lights_hall_door : public GameObjectScript
{
public:
    go_lights_hall_door() : GameObjectScript("go_lights_hall_door") { }

    bool OnGossipHello(Player* pPlayer, GameObject* me)
	{

     GameObject* Door = me->FindNearestGameObject(GO_Lights_Hall_Door, 20000);
      if (Door)
          Door->SetGoState(GO_STATE_ACTIVE);

        return true;
    }
};

void AddSC_boss_ptah()
{
    new boss_ptah();
	new go_lights_hall_door();
}