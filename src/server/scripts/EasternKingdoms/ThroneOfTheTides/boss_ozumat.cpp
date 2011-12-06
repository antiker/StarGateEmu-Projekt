#include "ScriptPCH.h"
#include "throne_of_the_tides.h"

#define GOSSIP_READY "We are ready!"

#define SAY_1 "As I purify these waters, the servants of filth will surely be stirred. Beware!"
#define SAY_2 "Patience guests. The waters are nearly cleansed."
#define SAY_3 "The beast has returned! It must not pollute my waters!"
#define SAY_DEATH "Your kind... cannot be... trusted..."
#define SAY_CLEANSED "My waters are cleansed! Drink in their power!"

Creature* Ozumat;
Creature* Neptulon;

enum Phases
{
    PHASE_NULL = 0, // Used to avoid wrong behaviour
    PHASE_FILTHY_INVADERS_1 = 1, // Starting phase
    PHASE_FILTHY_INVADERS_2 = 2, // Murlocs
    PHASE_FILTHY_INVADERS_3 = 3, // Mindlashers
    PHASE_FILTHY_INVADERS_4 = 4, // Behemont
    PHASE_BEAST_RETURN = 5, // Real phase 2
    PHASE_TIDAL_SURGE = 6, // Real phase 3
};

const Position spawns[] =
{
    {-122.412041f, 947.492188f, 231.579025f, 2.279974f},
    {-118.400780f, 1014.799866f, 230.195724f, 4.366778f},
};

class npc_neptulon : public CreatureScript
{
public:
    npc_neptulon() : CreatureScript("npc_neptulon") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new npc_neptulonAI (pCreature);
    }

    struct npc_neptulonAI : public ScriptedAI
    {
        npc_neptulonAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = c->GetInstanceScript();
            Neptulon = me;
        }

        bool InProgress;
        uint32 phase;
        uint32 summonMurlocTimer;
        uint32 MindlasherTimer;
        std::list<uint64> sumMurlocs;
        std::list<uint64> sumMindlasher;
        std::list<uint64> sumSapper;
        bool sumonslasher;
        uint32 behemontTimer;
        bool summonbehemont;
        bool ozumatSummoned;
        bool flagged;
        uint32 phase2_timer;
        InstanceScript* pInstance;
        uint64 ozumatGUID;
        uint32 deadSappers;
        bool slasherphased;

        void Reset()
        {
            InProgress = false;
            sumSapper.clear();
            sumMindlasher.clear();
            sumMurlocs.clear();
            phase = PHASE_FILTHY_INVADERS_1;
            MindlasherTimer = 20000;
            sumonslasher = false;
            behemontTimer = 30000;
            summonbehemont = false;
            summonMurlocTimer = 8000;
            phase2_timer = 60000;
            ozumatGUID = 0;
            ozumatSummoned = false;
            flagged = false;
            deadSappers = 0;
            slasherphased = false;
        }

        void SummonedCreatureDespawn(Creature* summon)
        {
            switch(summon->GetEntry())
            {
                case NPC_SAPPER:
                    deadSappers += 1;
                    break;
            }
        }

        void DespawnSummons()
        {
            for(std::list<uint64>::iterator itr = sumMurlocs.begin(); itr != sumMurlocs.end(); ++itr)
                if(Creature* cr = Unit::GetCreature(*me,(*itr)))
                    cr->DisappearAndDie();
            for(std::list<uint64>::iterator itr = sumMindlasher.begin(); itr != sumMindlasher.end(); ++itr)
                if(Creature* cr = Unit::GetCreature(*me,(*itr)))
                    cr->DisappearAndDie();
            for(std::list<uint64>::iterator itr = sumSapper.begin(); itr != sumSapper.end(); ++itr)
                if(Creature* cr = Unit::GetCreature(*me,(*itr)))
                    cr->DisappearAndDie();

            Ozumat->DisappearAndDie();
        }

        void JustSummoned(Creature* pSummon)
        {
            switch (pSummon->GetEntry())
            {
                case NPC_DEEP_MURLOC:
                    sumMurlocs.push_back(pSummon->GetGUID());
                    pSummon->AI()->AttackStart(me);
                    break;
                case NPC_MINDLASHER:
                    sumMindlasher.push_back(pSummon->GetGUID());
                    pSummon->AI()->AttackStart(me);
                    break;
                case NPC_BEHEMOTH:
                    pSummon->AI()->AttackStart(me);
                    break;
                case NPC_SAPPER:
                    sumSapper.push_back(pSummon->GetGUID());
                    break;
                case BOSS_OZUMAT:
                    ozumatGUID = pSummon->GetGUID();
                    break;
            }
        }

        void JustDied(Unit* pKiller)
        {
            if(pKiller)
                me->MonsterSay(SAY_DEATH,LANG_UNIVERSAL,NULL);
            DespawnSummons();
        }

        void SummonAdd(uint32 entry, uint32 count)
        {
            if(entry == BOSS_OZUMAT)
            {
                me->SummonCreature(entry,-161.927246f, 1003.904419f, 230.404358f, 5.801692f,TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000);
                return;
            }

            if(entry == NPC_SAPPER)
            {
                me->SummonCreature(entry,-143.599869f, 985.389221f, 230.390076f, 0.024302f,TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                me->SummonCreature(entry,-130.816040f, 968.372253f, 230.172058f, 1.370475f,TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                me->SummonCreature(entry,-140.050064f, 1004.192871f, 229.926407f, 5.370507f,TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
                return;
            }

            for(uint32 x = 0; x<=count; ++x)
               me->SummonCreature(entry,RAND(spawns[0],spawns[1]),TEMPSUMMON_CORPSE_TIMED_DESPAWN, 3000);
        }

        void UpdateAI(const uint32 diff)
        {
            if(!InProgress)
                return;

            if(phase == PHASE_FILTHY_INVADERS_1)
            {
                me->SetOrientation(0.166467f);
                phase = PHASE_FILTHY_INVADERS_2;
                me->MonsterSay(SAY_1,LANG_UNIVERSAL,NULL);
            }

            if(summonMurlocTimer <= diff)
            {
                if(phase == PHASE_FILTHY_INVADERS_2)
                    SummonAdd(NPC_DEEP_MURLOC,6);

                if(sumMurlocs.size() >= 6*3)
                    phase = PHASE_NULL;

                summonMurlocTimer = 5000;
            } else summonMurlocTimer -= diff;

            if(MindlasherTimer <= diff)
            {
                if(phase == PHASE_FILTHY_INVADERS_3)
                {
                    SummonAdd(NPC_MINDLASHER,1);
                }

                if(sumMindlasher.size() >= 3 && !slasherphased)
                {
                    me->MonsterYell(SAY_2,LANG_UNIVERSAL,NULL);
                    phase = PHASE_NULL;
                    slasherphased = true;
                }

                if(phase != PHASE_FILTHY_INVADERS_3 && !sumonslasher)
                {
                    SummonAdd(NPC_MINDLASHER,1);
                    phase = PHASE_FILTHY_INVADERS_3;
                    sumonslasher = true;
                }
                MindlasherTimer = 12000;
            } else MindlasherTimer -= diff;

            if(behemontTimer <= diff)
            {
                if(summonbehemont == false)
                {
                    SummonAdd(NPC_BEHEMOTH,1);
                    summonbehemont = true;
                }
            } else behemontTimer -= diff;

            if(phase2_timer <= diff && phase != PHASE_BEAST_RETURN)
            {
                phase = PHASE_BEAST_RETURN;
                me->MonsterYell(SAY_3,LANG_UNIVERSAL,NULL);
            } else phase2_timer -= diff;

            if(phase == PHASE_BEAST_RETURN)
            {
                if(ozumatSummoned == false)
                {
                    SummonAdd(NPC_SAPPER,3);
                    phase = PHASE_NULL;
                    ozumatSummoned = true;
                }
            }
            if(deadSappers >= 3 && phase != PHASE_TIDAL_SURGE)
                phase = PHASE_TIDAL_SURGE;

            if(phase == PHASE_TIDAL_SURGE)
            {
                if(flagged == false)
                {
                    SummonAdd(BOSS_OZUMAT,1);
                    Ozumat->setFaction(14);
                    if(pInstance)
                        pInstance->DoCastSpellOnPlayers(76133);
                    me->MonsterYell(SAY_CLEANSED,LANG_UNIVERSAL,NULL);
                    flagged = true;
                }
            }
        }
    };

    bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
    {
        pPlayer->PlayerTalkClass->ClearMenus();
        if (uiAction == 1000) //Start battle
        {
            CAST_AI(npc_neptulon::npc_neptulonAI, pCreature->AI())->InProgress = true;
            CAST_AI(npc_neptulon::npc_neptulonAI, pCreature->AI())->DoZoneInCombat();
        }
        return true;
    }

    bool OnGossipHello(Player* pPlayer, Creature* pCreature)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_READY, GOSSIP_SENDER_MAIN, 1000);
        pPlayer->PlayerTalkClass->SendGossipMenu(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        return true;
    }

};

class boss_ozumat : public CreatureScript
{
public:
    boss_ozumat() : CreatureScript("boss_ozumat") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_ozumatAI (pCreature);
    }

    struct boss_ozumatAI : public ScriptedAI
    {
        boss_ozumatAI(Creature *c) : ScriptedAI(c)
        {
            pInstance = c->GetInstanceScript();
            Ozumat = me;
            me->setFaction(14);
        }

        InstanceScript* pInstance;

        void UpdateAI(const uint32 diff)
        {
            if(me->HealthBelowPct(10))
            {
                me->setFaction(35);
                me->SummonGameObject(DUNGEON_MODE(GO_OZUMAT_CHEST_NORMAL,GO_OZUMAT_CHEST_HEROIC),-125.950981f, 983.343201f, 230.335464f, 3.635565f,0,0,0,0,9000000);
                Neptulon->SetVisible(false);
                me->CombatStop();
                if(pInstance)
                    pInstance->DoRemoveAurasDueToSpellOnPlayers(76133);
                me->SetVisible(false);
            }
        }
    };
};

void AddSC_neptulon()
{
    new npc_neptulon();
    new boss_ozumat();
}