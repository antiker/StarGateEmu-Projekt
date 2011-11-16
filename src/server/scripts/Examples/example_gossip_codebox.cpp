/*
 * Copyright (C) 2010-2011 Project StarGate
 */

/* ScriptData
SDName: Example_Gossip_Codebox
SD%Complete: 100
SDComment: Show a codebox in gossip option
SDCategory: Script Examples
EndScriptData */

#include "ScriptPCH.h"
#include <cstring>

enum eEnums
{
    SPELL_POLYMORPH         = 12826,
    SPELL_MARK_OF_THE_WILD  = 26990,

    SAY_NOT_INTERESTED      = -1999922,
    SAY_WRONG               = -1999923,
    SAY_CORRECT             = -1999924
};

#define GOSSIP_ITEM_1       "A quiz: what's your name?"
#define GOSSIP_ITEM_2       "I'm not interested"

class example_gossip_codebox : public CreatureScript
{
    public:

        example_gossip_codebox()
            : CreatureScript("example_gossip_codebox")
        {
        }

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            pPlayer->ADD_GOSSIP_ITEM_EXTENDED(0, GOSSIP_ITEM_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1, "", 0, true);
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

            pPlayer->PlayerTalkClass->SendGossipMenu(907, pCreature->GetGUID());

            return true;
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
        {
            pPlayer->PlayerTalkClass->ClearMenus();
            if (uiAction == GOSSIP_ACTION_INFO_DEF+2)
            {
                DoScriptText(SAY_NOT_INTERESTED, pCreature);
                pPlayer->CLOSE_GOSSIP_MENU();
            }

            return true;
        }

        bool OnGossipSelectCode(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction, const char* code)
        {
            pPlayer->PlayerTalkClass->ClearMenus();
            if (uiSender == GOSSIP_SENDER_MAIN)
            {
                switch (uiAction)
                {
                case GOSSIP_ACTION_INFO_DEF+1:
                    if (std::strcmp(code, pPlayer->GetName()) != 0)
                    {
                        DoScriptText(SAY_WRONG, pCreature);
                        pCreature->CastSpell(pPlayer, SPELL_POLYMORPH, true);
                    }
                    else
                    {
                        DoScriptText(SAY_CORRECT, pCreature);
                        pCreature->CastSpell(pPlayer, SPELL_MARK_OF_THE_WILD, true);
                    }
                    pPlayer->CLOSE_GOSSIP_MENU();

                    return true;
                }
            }

            return false;
        }
};

void AddSC_example_gossip_codebox()
{
    new example_gossip_codebox();
}