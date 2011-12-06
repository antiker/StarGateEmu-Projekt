#include "ScriptPCH.h"
#include "blackrock_caverns.h"
 
enum Spells
{
    SPELL_AURA_ACELERATION = 75817,
    H_SPELL_AURA_ACELERATION = 87376,
    SPELL_DARK_COMMAND = 75823,
    H_SPELL_DARK_COMMAND = 93462,
    SPELL_DRAIN_ESSENCE = 75645,
    SPELL_TWILIGHT_EVOLUTION = 75732,
    SPELL_EVOLUTION = 75610,
};
 
enum Yells
{
    SAY_AGGRO = -0000000, 
    SAY_SLAY = -0000000, 
    SAY_DEATH = -0000000, 
    SAY_EVOLUTION = -0000000, 
};
 
 
enum Summons
{
};
 
const Position AngeredSpawnPoint[5]=
{
};
 
class boss_corla : public CreatureScript
{
 
public:
    boss_corla() : CreatureScript("boss_corla") { }
 
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_corlaAI (pCreature);
    }
 
    struct boss_corlaAI : public ScriptedAI
    {
        boss_corlaAI(Creature* c) : ScriptedAI(c)
        {
           m_pInstance = (InstanceScript*)c->GetInstanceScript();
        }
 
        InstanceScript* m_pInstance;

        uint32 uiAuraTimer;
        uint32 uiDarkTimer;

bool aura;
 
        void Reset()
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);

            uiAuraTimer = 0;
            uiDarkTimer = 10000;

aura=false;
 
            m_pInstance->SetData(DATA_CORLA_EVENT, NOT_STARTED);
        }
 
        void JustSummoned(Creature* summoned)
        {
        }

        void EnterCombat(Unit* /*who*/)
        {
            DoScriptText(SAY_AGGRO, me);
            me->MonsterYell("HERETICS! You will suffer for this interruption!",0,0);
            DoZoneInCombat();
            m_pInstance->SetData(DATA_CORLA_EVENT, IN_PROGRESS);
        }
 
        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;
 
 
            if (uiAuraTimer <= diff && aura==false)
            {
                if (IsHeroic())
                   DoCast(me, H_SPELL_AURA_ACELERATION, true);
                else
                   DoCast(me, SPELL_AURA_ACELERATION, true);
                aura = true;
            } else uiAuraTimer -=diff;
 
            if (uiDarkTimer <= diff)
            {
if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                {
                    if (IsHeroic())
                       DoCast(target, H_SPELL_DARK_COMMAND);
                    else
                       DoCast(target, SPELL_DARK_COMMAND);
                }
                uiDarkTimer=20000;
            } else uiDarkTimer -=diff;
  
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
            me->MonsterYell("For the master I'd die a thousand times... A thousan...",0,0);

            m_pInstance->SetData(DATA_CORLA_EVENT, DONE);

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
            me->MonsterYell("There is only one true path of enlightenment! DEATH!",0,0);
            DoScriptText(SAY_SLAY, me);
        }
    };
 
};
 
void AddSC_boss_corla()
{
    new boss_corla();
}