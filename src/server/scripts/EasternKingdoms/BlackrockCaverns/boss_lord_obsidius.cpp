#include "ScriptPCH.h"
#include "blackrock_caverns.h"
 
enum Spells
{
    SPELL_STONEBLOW = 76185,
    SPELL_TWILIGHTCORRUPTION = 76188,
    H_SPELL_TWILIGHTCORRUPTION = 93613,
    SPELL_THUNDERCLAP = 76186,
};
 
enum Yells
{
    SAY_AGGRO = -0000000, 
    SAY_SLAY = -0000000, 
    SAY_DEATH = -0000000, 
    SAY_TRANSFORMATION = -0000000, 
};

enum Summons
{
};
 
const Position AngeredSpawnPoint[5]=
{
};
 
class boss_lord_obsidius : public CreatureScript
{
 
public:
    boss_lord_obsidius() : CreatureScript("boss_lord_obsidius") { }
 
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_lord_obsidiusAI (pCreature);
    }
 
    struct boss_lord_obsidiusAI : public ScriptedAI
    {
        boss_lord_obsidiusAI(Creature* c) : ScriptedAI(c), summons(me)
        {
           m_pInstance = (InstanceScript*)c->GetInstanceScript();
        }
 
        InstanceScript* m_pInstance;

        SummonList summons;
        
        uint32 uiStoneBlow;
        uint32 uiTC;
        uint32 uiThunderClap;

        void Reset()
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);

            uiStoneBlow = 10000;
            uiTC = 8000;
            uiThunderClap = 5000;

            summons.DespawnAll();
            
            m_pInstance->SetData(DATA_ASCENDANT_LORD_OBSIDIUS_EVENT, NOT_STARTED);
        }
 
        void JustSummoned(Creature* summoned)
        {
                Unit* target = NULL;
                target = SelectTarget(SELECT_TARGET_RANDOM); // Wave adds

                summoned->AI()->AttackStart(target); // CAN be NULL
                DoZoneInCombat(summoned);

                summons.Summon(summoned);
        }

        void EnterCombat(Unit* /*who*/)
        {
            if (IsHeroic())
            {
               me->SummonCreature(40817,336.86,584.70,66,4.5,TEMPSUMMON_CORPSE_DESPAWN);
               me->SummonCreature(40817,333.47,527.16,66,1.64,TEMPSUMMON_CORPSE_DESPAWN);
               me->SummonCreature(40817,360.21,561.88,66,3.1,TEMPSUMMON_CORPSE_DESPAWN);
            }
            else
            {
               me->SummonCreature(40817,336.86,584.70,66,4.5,TEMPSUMMON_CORPSE_DESPAWN);
               me->SummonCreature(40817,333.47,527.16,66,1.64,TEMPSUMMON_CORPSE_DESPAWN);
            }
            DoScriptText(SAY_AGGRO, me);
            me->MonsterYell("You come seeking answers? Then have them! Look upon your answer to living!",0,0);
            DoZoneInCombat();
            m_pInstance->SetData(DATA_ASCENDANT_LORD_OBSIDIUS_EVENT, IN_PROGRESS);
        }
 
        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;
 
            if (uiStoneBlow <= diff)
            {
if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST))
                {
                    DoCast(target, SPELL_STONEBLOW);
                }
                uiStoneBlow=10000;
            } else uiStoneBlow -=diff;

            if (uiTC <= diff)
            {
if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM))
                {
                    if (IsHeroic())
                      DoCast(target, H_SPELL_TWILIGHTCORRUPTION);
                    else
                      DoCast(target, SPELL_TWILIGHTCORRUPTION);
                }
                uiTC=10000;
            } else uiTC -=diff;

            if (uiThunderClap <= diff && IsHeroic())
            {
if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST))
                {
                    DoCast(target, SPELL_THUNDERCLAP);
                }
                uiThunderClap= 6000;
            } else uiThunderClap -=diff;
  
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
            summons.DespawnAll();
            
            DoScriptText(SAY_DEATH, me);
            me->MonsterYell("I cannot be destroyed... Only... de... layed...",0,0);

            m_pInstance->SetData(DATA_ASCENDANT_LORD_OBSIDIUS_EVENT, DONE);

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
            me->MonsterYell("Your kind has no place in the master's world.",0,0);
            DoScriptText(SAY_SLAY, me);
        }
    };
 
};

class npc_shade_obsidius : public CreatureScript
{
    public:
        npc_shade_obsidius() : CreatureScript("npc_shade_obsidius") { }

        CreatureAI* GetAI(Creature* creature) const
        {
            return new npc_shade_obsidiusAI(creature);
        }

        struct npc_shade_obsidiusAI : public ScriptedAI
        {
            npc_shade_obsidiusAI(Creature* creature) : ScriptedAI(creature) {}

            uint32 uiVeilTimer;
            
            void Reset()
            {
                uiVeilTimer=5000;
                me->AddAura(76167, me); // Aura Twitchy
                me->AddAura(76164, me); // Shadow of obsidius
                DoCast(me, 76190); // Crepuscular Veil
            }

            void UpdateAI(const uint32 diff)
            {
              //Return since we have no target
              if (!UpdateVictim())
                return;
              if (uiVeilTimer <= diff)
              {
if (Unit* target = SelectTarget(SELECT_TARGET_NEAREST))
                {
                    DoCast(target, 76189);
                }
                uiVeilTimer = 4000;
               } else uiVeilTimer -=diff;
            }
        };
};

void AddSC_boss_lord_obsidius()
{
    new boss_lord_obsidius();
    new npc_shade_obsidius();
}