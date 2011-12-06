#include "ScriptPCH.h"
#include "blackrock_caverns.h"
 
enum Spells
{
    SPELL_RAJAR = 15284,
};
 
enum Yells
{
    SAY_AGGRO = -0000000, // Bodies to test my armaments upon!
    SAY_SLAY = -0000000, // We number in the millions! Your efforts are wasted...
    SAY_DEATH = -0000000, // Merely an impurity in the compound...
    SAY_EVOLUTION = -0000000, // Feel the burn!
};
 
enum Summons
{
};
 
const Position AngeredSpawnPoint[5]=
{
};
 
class boss_karsh : public CreatureScript
{
 
public:
    boss_karsh() : CreatureScript("boss_karsh") { }
 
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_karshAI (pCreature);
    }
 
    struct boss_karshAI : public ScriptedAI
    {
        boss_karshAI(Creature* c) : ScriptedAI(c)
        {
           m_pInstance = (InstanceScript*)c->GetInstanceScript();
        }
 
        InstanceScript* m_pInstance;

        uint32 uiRajarTimer;

        void Reset()
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);

            uiRajarTimer = 10000;

            m_pInstance->SetData(DATA_KARSH_STEELBENDER_EVENT, NOT_STARTED);
        }
 
        void JustSummoned(Creature* summoned)
        {
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoScriptText(SAY_AGGRO, me);
            me->MonsterYell("Bodies to test my armaments upon!",0,0);
            DoZoneInCombat();
            m_pInstance->SetData(DATA_KARSH_STEELBENDER_EVENT, IN_PROGRESS);
        }
 
        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;
 
            if (uiRajarTimer <= diff)
            {
if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                {
                    DoCast(target, SPELL_RAJAR);
                }
                uiRajarTimer=10000;
            } else uiRajarTimer -=diff;
  
            DoMeleeAttackIfReady();

            if (me->GetDistance(me->GetHomePosition()) > 60.0f)
            {
                //Not blizzlike, hack to avoid an exploit
                EnterEvadeMode();
                return;
            }
        }
 
        void JustDied(Unit* /*killer*/)
        {
            DoScriptText(SAY_DEATH, me);
            me->MonsterYell("Merely an impurity in the compound...",0,0);

            m_pInstance->SetData(DATA_KARSH_STEELBENDER_EVENT, DONE);

            if (IsHeroic())
            {
             Map::PlayerList const& players = me->GetMap()->GetPlayers();
             if (me->GetMap()->IsDungeon() && !players.isEmpty())
             {
                 for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                 {
                            Player* pPlayer = itr->getSource();
                            if (pPlayer)
                            {
                                pPlayer->ModifyCurrency(395,7500);
                            }
  }
             }
            }
        }
 
        void KilledUnit(Unit * victim)
        {
            if (victim == me)
                return;
            me->MonsterYell("We number in the millions! Your efforts are wasted...",0,0);
            DoScriptText(SAY_SLAY, me);
        }
    };
 
};
 
void AddSC_boss_karsh()
{
    new boss_karsh();
}