/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#include "gamePCH.h"
#include "Player.h"
#include "Battleground.h"
#include "BattlegroundBG.h"
#include "Language.h"

BattlegroundBG::BattlegroundBG()
{
    m_StartMessageIds[BG_STARTING_EVENT_FIRST]  = LANG_BG_BG_START_TWO_MINUTES;
    m_StartMessageIds[BG_STARTING_EVENT_SECOND] = LANG_BG_BG_START_ONE_MINUTE;
    m_StartMessageIds[BG_STARTING_EVENT_THIRD]  = LANG_BG_BG_START_HALF_MINUTE;
    m_StartMessageIds[BG_STARTING_EVENT_FOURTH] = LANG_BG_BG_HAS_BEGUN;
}

BattlegroundBG::~BattlegroundBG()
{
}

void BattlegroundBG::Update(uint32 diff)
{
    Battleground::Update(diff);
}

void BattlegroundBG::StartingEventCloseDoors()
{
}

void BattlegroundBG::StartingEventOpenDoors()
{
}

void BattlegroundBG::AddPlayer(Player *plr)
{
    Battleground::AddPlayer(plr);
    //create score and add it to map, default values are set in constructor
    BattlegroundBGScore* sc = new BattlegroundBGScore;

    m_PlayerScores[plr->GetGUID()] = sc;
}

void BattlegroundBG::RemovePlayer(Player* /*plr*/, uint64 /*guid*/)
{
}

void BattlegroundBG::HandleAreaTrigger(Player * /*Source*/, uint32 /*Trigger*/)
{
    // this is wrong way to implement these things. On official it done by gameobject spell cast.
    if (GetStatus() != STATUS_IN_PROGRESS)
        return;
}

void BattlegroundBG::UpdatePlayerScore(Player *Source, uint32 type, uint32 value, bool doAddHonor)
{
    BattlegroundScoreMap::iterator itr = m_PlayerScores.find(Source->GetGUID());
    if (itr == m_PlayerScores.end())                         // player not found...
        return;

    switch(type)
    {
        case SCORE_BASES_ASSAULTED:
            ((BattlegroundBGScore*)itr->second)->BasesAssaulted += value;
            Source->GetAchievementMgr().UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BG_OBJECTIVE_CAPTURE, BG_OBJECTIVE_ASSAULT_BASE);
            break;
        case SCORE_BASES_DEFENDED:
            ((BattlegroundBGScore*)itr->second)->BasesDefended += value;
            Source->GetAchievementMgr().UpdateAchievementCriteria(ACHIEVEMENT_CRITERIA_TYPE_BG_OBJECTIVE_CAPTURE, BG_OBJECTIVE_DEFEND_BASE);
            break;
        default:
            Battleground::UpdatePlayerScore(Source, type, value, doAddHonor);
            break;
    }
}

bool BattlegroundBG::SetupBattleground()
{
    return true;
}

void BattlegroundBG::EndBattleground(uint32 winner)
{
    Battleground::EndBattleground(winner);
}