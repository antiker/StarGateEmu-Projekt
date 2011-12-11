#include "ScriptMgr.h"
#include "ScriptedCreature.h"
#include "ScriptPCH.h"
#include "halls_of_origination.h"

enum Spells
{
    //Rajh
    SPELL_SUN_STRIKE = 73872,
    SPELL_INFERNO_LEAP = 87647, //Value: 32375 to 37625
    SPELL_INFERNO_LEAP_2 = 89876, //Value: 120250 to 139750
    SPELL_SUMMON_SUN_ORB = 80352,
    SPELL_BLESSING_OF_THE_SUN = 76352,
    SPELL_SUMMON_SOLAR_WIND = 74104,

    //Solar Wind
    SPELL_SOLAR_WIND = 89130,
    SPELL_SOLAR_FIRE = 89131
};


#define SAY_AGGRO "Spührt ihr diesen Wind? Diese wärme der Sonne ..."
#define SAY_KILL ""
#define SAY_DEATH "Funkelndes Licht begleite mich auf meinen lezten weg ..."
#define SAY_ENERGIZE ""


enum EnergizeCords
{
    //Find cords for the center of room
    X = 0,
    Y = 0,
    Z = 0
};

enum Events
{
    EVENT_SUN_STRIKE = 1,
    EVENT_INFERNO_LEAP = 2,
    EVENT_BLESSING_OF_THE_SUN = 3,
    EVENT_SUMMON_SUN_ORB = 4,
    EVENT_SUMMON_SOLAR_WIND = 5
};

class boss_rajh : public CreatureScript
{
    public:
        boss_rajh() : CreatureScript("boss_rajh") { }

        struct boss_rajhAI : public BossAI
        {
            boss_rajhAI(Creature* creature) : BossAI(creature, DATA_RAJH_EVENT)
            {
                instance = me->GetInstanceScript();
            }

            InstanceScript* instance;

            void Reset()
            {
                if (instance)
                    instance->SetData(DATA_RAJH_EVENT, NOT_STARTED);

                me->SetPower(POWER_ENERGY, me->GetMaxPower(POWER_ENERGY));
            }

            void EnterCombat(Unit* /*who*/)
            {
                me->MonsterYell(SAY_AGGRO, 0, 0);

                if (instance)
                    instance->SetData(DATA_RAJH_EVENT, IN_PROGRESS);

                me->SetPower(POWER_ENERGY, me->GetMaxPower(POWER_ENERGY));

                events.ScheduleEvent(EVENT_SUN_STRIKE, 10000);
                events.ScheduleEvent(EVENT_INFERNO_LEAP, 15000);
                events.ScheduleEvent(EVENT_BLESSING_OF_THE_SUN, 12000);
                events.ScheduleEvent(EVENT_SUMMON_SUN_ORB, 25000);
                events.ScheduleEvent(EVENT_SUMMON_SOLAR_WIND, 20000);

                DoZoneInCombat();
            }

            void EnergizeSun()
            {
                me->MonsterYell(SAY_ENERGIZE, 0, 0);
                me->GetMotionMaster()->MovePoint(0, X, Y, Z);
                DoCastAOE(SPELL_BLESSING_OF_THE_SUN);
            }

            void UpdateAI(uint32 const diff)
            {
                if (!UpdateVictim())
                    return;

                if (me->HasUnitState(UNIT_STAT_CASTING))
                    return;

                while(uint32 eventId = events.ExecuteEvent())
                {
                    switch(eventId)
                    {
                        case EVENT_SUN_STRIKE:
                            DoCast(me->getVictim(), SPELL_SUN_STRIKE);
                            events.ScheduleEvent(EVENT_SUN_STRIKE, 10000);
                            break;
                        case EVENT_INFERNO_LEAP:
                            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, true))
                                DoCast(target, SPELL_INFERNO_LEAP);
                            events.ScheduleEvent(EVENT_INFERNO_LEAP, urand(15000, 22000));
                            break;
                        case EVENT_BLESSING_OF_THE_SUN:
                            if (me->GetPower(POWER_ENERGY) == 0)
                                EnergizeSun();
                            events.ScheduleEvent(EVENT_BLESSING_OF_THE_SUN, 15000);
                            break;
                        case EVENT_SUMMON_SUN_ORB:
                            DoCast(SPELL_SUMMON_SUN_ORB);
                            events.ScheduleEvent(EVENT_SUMMON_SUN_ORB, 25000);
                            break;
                        case EVENT_SUMMON_SOLAR_WIND:
                            DoCast(SPELL_SUMMON_SOLAR_WIND);
                            events.ScheduleEvent(EVENT_SUMMON_SOLAR_WIND, 30000);
                            break;
                        default:
                            break;
                    }
                }

                DoMeleeAttackIfReady();
            }

            void JustDied(Unit* /*who*/)
            {
                me->MonsterYell(SAY_DEATH, 0, 0);

                if (instance)
                    instance->SetData(DATA_RAJH_EVENT, DONE);
            }
        };

        CreatureAI* GetAI(Creature* creature) const
        {
            return new boss_rajhAI(creature);
        }
};

class mob_solar_wind : public CreatureScript
{
public:
    mob_solar_wind() : CreatureScript("mob_solar_wind") { }

    CreatureAI* GetAI(Creature* creature) const
    {
        return new mob_solar_windAI(creature);
    }

    struct mob_solar_windAI : public ScriptedAI
    {
        mob_solar_windAI(Creature* creature) : ScriptedAI(creature)
        {
            m_pInstance = (InstanceScript*)creature->GetInstanceScript();
            Reset();
        }

        InstanceScript* m_pInstance;

        void EnterCombat(Unit* /*who*/)
        {
            DoCast(me, SPELL_SOLAR_FIRE);
        }

        void Reset()
        {
            me->SetReactState(REACT_PASSIVE);
        }

        void JustDied(Unit* /*killer*/)
        {
            // used to despawn corpse immediately
            me->DespawnOrUnsummon();
        }
    };
};

void AddSC_boss_rajh()
{
    new boss_rajh;
    new mob_solar_wind;
}