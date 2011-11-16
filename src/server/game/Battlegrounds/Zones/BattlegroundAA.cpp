/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#include "gamePCH.h"
#include "Battleground.h"
#include "BattlegroundAA.h"
#include "Language.h"
#include "Player.h"

BattlegroundAA::BattlegroundAA()
{
    m_StartDelayTimes[BG_STARTING_EVENT_FIRST]  = BG_START_DELAY_1M;
    m_StartDelayTimes[BG_STARTING_EVENT_SECOND] = BG_START_DELAY_30S;
    m_StartDelayTimes[BG_STARTING_EVENT_THIRD]  = BG_START_DELAY_15S;
    m_StartDelayTimes[BG_STARTING_EVENT_FOURTH] = BG_START_DELAY_NONE;
    //we must set messageIds
    m_StartMessageIds[BG_STARTING_EVENT_FIRST]  = LANG_ARENA_ONE_MINUTE;
    m_StartMessageIds[BG_STARTING_EVENT_SECOND] = LANG_ARENA_THIRTY_SECONDS;
    m_StartMessageIds[BG_STARTING_EVENT_THIRD]  = LANG_ARENA_FIFTEEN_SECONDS;
    m_StartMessageIds[BG_STARTING_EVENT_FOURTH] = LANG_ARENA_HAS_BEGUN;
}

BattlegroundAA::~BattlegroundAA()
{
}

void BattlegroundAA::Update(uint32 diff)
{
    Battleground::Update(diff);
}

void BattlegroundAA::StartingEventCloseDoors()
{
}

void BattlegroundAA::StartingEventOpenDoors()
{
}

void BattlegroundAA::AddPlayer(Player *plr)
{
    Battleground::AddPlayer(plr);
    //create score and add it to map, default values are set in constructor
    BattlegroundAAScore* sc = new BattlegroundAAScore;

    m_PlayerScores[plr->GetGUID()] = sc;
}

void BattlegroundAA::RemovePlayer(Player * /*plr*/, uint64 /*guid*/)
{
}

void BattlegroundAA::HandleKillPlayer(Player* player, Player* killer)
{
    Battleground::HandleKillPlayer(player, killer);
}

void BattlegroundAA::HandleAreaTrigger(Player * /*Source*/, uint32 /*Trigger*/)
{
}

bool BattlegroundAA::SetupBattleground()
{
    return true;
}