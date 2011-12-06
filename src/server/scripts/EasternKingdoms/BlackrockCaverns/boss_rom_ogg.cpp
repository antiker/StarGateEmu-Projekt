#include "ScriptPCH.h"
#include "blackrock_caverns.h"
 
enum Spells
{
    SPELL_CALL_FOR_HELP = 82137,
    SPELL_CHAINS_OF_WOE = 75539,
    SPELL_WOUNDING_STRIKE = 75571,
    H_SPELL_WOUNDING_STRIKE = 93452,
    SPELL_THE_SKULLCRACKER = 75543,
    H_SPELL_THE_SKULLCRACKER = 93453,
    SPELL_QUAKE = 75272,
    SKULLCRACKER = 95326,
};
 
enum Yells
{
    SAY_AGGRO = -0000000, 
    SAY_SLAY = -0000000, 
    SAY_DEATH = -0000000, 
    SAY_SKULLCRACKER = -0000000, 
};
 
 
enum Summons
{
    NPC_CHAINS_OF_WOE = 40447,
    NPC_ANGERED_EARTH = 50376,
};
 
enum ChainsofwoeSpells
{
    SPELL_CHAINS_OF_WOE_2 = 75441,
};
 
const Position AngeredSpawnPoint[5]=
{
};
 
class boss_romogg_bonecrusher : public CreatureScript
{
 
public:
    boss_romogg_bonecrusher() : CreatureScript("boss_romogg_bonecrusher") { }
 
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_romogg_bonecrusherAI (pCreature);
    }
 
    struct boss_romogg_bonecrusherAI : public ScriptedAI
    {
        boss_romogg_bonecrusherAI(Creature* c) : ScriptedAI(c), summons(me)
        {
           m_pInstance = (InstanceScript*)c->GetInstanceScript();
        }
 
        InstanceScript* m_pInstance;
        SummonList summons;

        uint32 uiHelpTimer;
        uint32 uiWoundingStrikeTimer1;
        uint32 uiWoundingStrikeTimer2;
        uint32 uiQuakeTimer;
        uint32 uiRompeTimer;
 
        bool Chains_of_woe;
        bool Chain1;
        bool Chain2;
        bool help;
        bool rompecraneos;
        bool faserompe;
 
        void Reset()
        {
            me->ApplySpellImmune(0, IMMUNITY_EFFECT, SPELL_EFFECT_KNOCK_BACK, true);
            me->ApplySpellImmune(0, IMMUNITY_MECHANIC, MECHANIC_GRIP, true);
            uiHelpTimer = 0;
            uiWoundingStrikeTimer1 = 13000;
            uiQuakeTimer = 15000;
            uiWoundingStrikeTimer2 = 23000;
            uiRompeTimer=12000;
            if (IsHeroic())
uiRompeTimer= 8000;
 
            help = true;
            Chain1 = true;
            Chain2 = true;
            Chains_of_woe = false;
            rompecraneos = false;
            faserompe = false;

            summons.DespawnAll();
            m_pInstance->SetData(DATA_ROMOGG_BONECRUSHER_EVENT, NOT_STARTED);
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
            DoScriptText(SAY_AGGRO, me);
            me->MonsterYell("Boss Cho'gall not gonna be happy 'bout dis!",0,0);
            DoZoneInCombat();
            m_pInstance->SetData(DATA_ROMOGG_BONECRUSHER_EVENT, IN_PROGRESS);
        }
 
        void UpdateAI(const uint32 diff)
        {
            //Return since we have no target
            if (!UpdateVictim())
                return;
 
 
            if (uiHelpTimer <= diff && help == true)
            {
                DoCast(me->getVictim(), SPELL_CALL_FOR_HELP , true);
                help = false;
            } else uiHelpTimer -=diff;
 
 
            if (uiWoundingStrikeTimer1 <= diff && rompecraneos == false)
            {
                if (IsHeroic())
                  DoCast(me->getVictim(), H_SPELL_WOUNDING_STRIKE, true);
                else
DoCast(me->getVictim(), SPELL_WOUNDING_STRIKE, true);
                uiWoundingStrikeTimer1 = 13000;
            } else uiWoundingStrikeTimer1 -= diff;
 
 
 
            if (uiQuakeTimer <= diff && rompecraneos == false)
            {
                DoCast(me->getVictim(), SPELL_QUAKE, true);
                uiQuakeTimer = 60000;
 
                if (IsHeroic())
                {
Map::PlayerList const& players = me->GetMap()->GetPlayers();
                    if (me->GetMap()->IsDungeon() && !players.isEmpty())
                    {
                      for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                      {
                         Player* pPlayer = itr->getSource();
                         me->SummonCreature(NPC_ANGERED_EARTH, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(),0.0f, TEMPSUMMON_CORPSE_DESPAWN, 0); // 50376
                      }
       }
                }
            } else uiQuakeTimer -= diff;
 
 
 
            if (uiWoundingStrikeTimer2 <= diff && rompecraneos == false)
            {
                if (IsHeroic())
                  DoCast(me->getVictim(), H_SPELL_WOUNDING_STRIKE, true);
                else
                  DoCast(me->getVictim(), SPELL_WOUNDING_STRIKE, true);
                uiWoundingStrikeTimer2 = 23000;
            } else uiWoundingStrikeTimer2 -= diff;
 
 
 
            if (me->GetHealthPct() <= 66 && Chain1 == true)
            {
                Chain1 = false;
                DoCast(SPELL_CHAINS_OF_WOE);
rompecraneos = true;
            }

            if (me->GetHealthPct() <= 33 && Chain2 == true)
            {
                Chain2 = false;
                DoCast(SPELL_CHAINS_OF_WOE);
                rompecraneos = true;
            }

            if (rompecraneos == true)
            {
                if (faserompe == false)
{
                   DoScriptText(SAY_SKULLCRACKER, me);
                   me->MonsterYell("Stand still! Rom'ogg crack your skulls!",0,0);
                  faserompe=true;
                 }

                if (IsHeroic())
                    DoCast(me->getVictim(), H_SPELL_THE_SKULLCRACKER);
                else
                    DoCast(me->getVictim(), SPELL_THE_SKULLCRACKER);
               
                if (uiRompeTimer <= diff)
                {
                    Map::PlayerList const& players = me->GetMap()->GetPlayers();
                    if (me->GetMap()->IsDungeon() && !players.isEmpty())
                    {
                      for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                      {
                            Player* pPlayer = itr->getSource();
                            if (pPlayer && me->IsInRange(pPlayer,0.0f,12.0f,true))
                                 pPlayer->CastSpell(pPlayer,SKULLCRACKER,true);
                      }
       }

                   rompecraneos=false;
                   faserompe=false;
                   
uiRompeTimer=12000;
                   if (IsHeroic())
                     uiRompeTimer=8000;
}
                else uiRompeTimer -= diff;
            }
 
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
            me->MonsterYell("Rom'ogg sorry...",0,0);

            summons.DespawnAll();

            m_pInstance->SetData(DATA_ROMOGG_BONECRUSHER_EVENT, DONE);

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
            me->MonsterYell("Dat's what you get! Noting!",0,0);
            DoScriptText(SAY_SLAY, me);
        }
    };
 
};
 
class mob_chains_of_woe : public CreatureScript
{
public:
    mob_chains_of_woe() : CreatureScript("mob_chains_of_woe") { }
 
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new mob_chains_of_woeAI (pCreature);
    }
 
    struct mob_chains_of_woeAI : public ScriptedAI
    {
        mob_chains_of_woeAI(Creature *c) : ScriptedAI(c) {}
 
        uint32 uiChainsofwoeTimer2;
uint32 uidesaparece;

        bool mobb;
 
        void Reset()
        {
            uiChainsofwoeTimer2 = 10;
            uidesaparece = 20000;
            mobb = true;
        }
 
        void UpdateAI(const uint32 diff)
        {
            if (!UpdateVictim())
                return;
 
            if (uiChainsofwoeTimer2 <= diff && mobb == true)
            {
                uiChainsofwoeTimer2 = 10;
                mobb = false;
Map::PlayerList const& players = me->GetMap()->GetPlayers();
                    if (me->GetMap()->IsDungeon() && !players.isEmpty())
                    {
                      for (Map::PlayerList::const_iterator itr = players.begin(); itr != players.end(); ++itr)
                      {
                            Player* pPlayer = itr->getSource();
                            if (pPlayer && me->IsInRange(pPlayer,0.0f,12.0f,true))
                            {
                                me->CastSpell(pPlayer,55520,true);
pPlayer->CastSpell(pPlayer,SPELL_CHAINS_OF_WOE_2,true);
                                break;
                            }
                      }
       }
            } else uiChainsofwoeTimer2 -= diff;

            if (uidesaparece <= diff)
              me->ForcedDespawn();
            else uidesaparece -= diff;
        }
 
    };
 
};

class spell_terremoto : public SpellScriptLoader
{
    public:
        spell_terremoto() : SpellScriptLoader("spell_terremoto") { }

        class spell_terremoto_AuraScript : public AuraScript
        {
            PrepareAuraScript(spell_terremoto_AuraScript);

            void HandleExtraEffect(AuraEffect const* /*aurEff*/)
            {
GetTarget()->DealDamage(GetTarget(), 9000, NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
            }

            void Register()
            {
                OnEffectPeriodic += AuraEffectPeriodicFn(spell_terremoto_AuraScript::HandleExtraEffect, EFFECT_0, SPELL_AURA_PERIODIC_DAMAGE);
            }
        };

        AuraScript* GetAuraScript() const
        {
            return new spell_terremoto_AuraScript();
        }
};
 
void AddSC_boss_romogg_bonecrusher()
{
    new boss_romogg_bonecrusher();
    new mob_chains_of_woe();
    new spell_terremoto();
}