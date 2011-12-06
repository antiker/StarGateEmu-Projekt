#include "ScriptPCH.h"
#include "blackrock_caverns.h"
 
enum Spells
{
    SPELL_CARGA_RABIOSA = 76030,
    H_SPELL_CARGA_RABIOSA = 93580,
    SPELL_ROMPELLAMAS = 76032,
    H_SPELL_ROMPELLAMAS = 93583,
    SPELL_RUGIDO_ATERRORIZADOR = 76028,
    H_SPELL_RUGIDO_ATERRORIZADOR = 93586,
    SPELL_FLEMADEMAGMA = 76031,
    SPELL_RABIA = 82395,
};
 
enum Yells
{
};
 
enum Summons
{
};
 
const Position AngeredSpawnPoint[5]=
{
};
 
class boss_bella : public CreatureScript
{
 
public:
    boss_bella() : CreatureScript("boss_bella") { }
 
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_bellaAI (pCreature);
    }
 
    struct boss_bellaAI : public ScriptedAI
    {
        boss_bellaAI(Creature* c) : ScriptedAI(c)
        {
           m_pInstance = (InstanceScript*)c->GetInstanceScript();
        }
 
        InstanceScript* m_pInstance;

        uint32 uicargatimer;
        uint32 uirompetimer;
        uint32 uirugidotimer;
        uint32 uiflematimer;
        uint32 uirabiatimer;

        bool rabia;

        void Reset()
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);

            uicargatimer = 10000;
            uirompetimer = 5000;
            uirugidotimer = 15000;
            uiflematimer = 8000;
            uirabiatimer = 450000;

            rabia = false;

            m_pInstance->SetData(DATA_BEAUTY_EVENT, NOT_STARTED);
        }
 
        void JustSummoned(Creature* summoned)
        {
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoZoneInCombat();
            m_pInstance->SetData(DATA_BEAUTY_EVENT, IN_PROGRESS);
        }
 
        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;
 
            if (uicargatimer <= diff)
            {
if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM,0,15.0f))
                {
                    if (IsHeroic())
                        DoCast(target, H_SPELL_CARGA_RABIOSA);
                    else
                        DoCast(target, SPELL_CARGA_RABIOSA);
                }
                uicargatimer = 30000;
            } else uicargatimer -=diff;

            if (uirompetimer <= diff)
            {
if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                {
                    if (IsHeroic())
                        DoCast(target, H_SPELL_ROMPELLAMAS);
                    else
                        DoCast(target, SPELL_ROMPELLAMAS);
                }
                uirompetimer = 30000;
            } else uirompetimer -=diff;
 
            if (uirugidotimer <= diff)
            {
if (Unit* target = SelectTarget(SELECT_TARGET_TOPAGGRO))
                {
                    if (IsHeroic())
                        DoCast(target, H_SPELL_RUGIDO_ATERRORIZADOR);
                    else
                        DoCast(target, SPELL_RUGIDO_ATERRORIZADOR);
                }
                uirugidotimer = 30000;
            } else uirugidotimer -=diff;

            if (uiflematimer <= diff)
            {
if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                {
                    DoCast(target, SPELL_FLEMADEMAGMA);
                }
                uiflematimer = 10000;
            } else uiflematimer -=diff;
 
            if (uirabiatimer <= diff & rabia==false)
            {
                DoCast(me, SPELL_RABIA);
                rabia = true;
            } else uirabiatimer -=diff;

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
            m_pInstance->SetData(DATA_BEAUTY_EVENT, DONE);

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
        }
    };
 
};
 
void AddSC_boss_bella()
{
    new boss_bella();
}