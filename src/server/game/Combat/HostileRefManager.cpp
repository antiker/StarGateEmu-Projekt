/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#include "gamePCH.h"
#include "HostileRefManager.h"
#include "ThreatManager.h"
#include "Unit.h"
#include "DBCStructure.h"
#include "SpellMgr.h"

HostileRefManager::~HostileRefManager()
{
    deleteReferences();
}

//=================================================
// send threat to all my hateres for the pVictim
// The pVictim is hated than by them as well
// use for buffs and healing threat functionality

void HostileRefManager::threatAssist(Unit *pVictim, float fThreat, SpellEntry const *pThreatSpell, bool pSingleTarget)
{
    HostileReference* ref;

    float size = pSingleTarget ? 1.0f : getSize();            // if pSingleTarget do not divide threat
    ref = getFirst();
    while (ref != NULL)
    {
        float threat = ThreatCalcHelper::calcThreat(pVictim, iOwner, fThreat, (pThreatSpell ? GetSpellSchoolMask(pThreatSpell) : SPELL_SCHOOL_MASK_NORMAL), pThreatSpell);
        if (pVictim == getOwner())
            ref->addThreat(threat / size);          // It is faster to modify the threat durectly if possible
        else
            ref->getSource()->addThreat(pVictim, threat / size);
        ref = ref->next();
    }
}

//=================================================

void HostileRefManager::addTempThreat(float fThreat, bool apply)
{
    HostileReference* ref = getFirst();

    while (ref != NULL)
    {
        if (apply)
        {
            if (ref->getTempThreatModifier() == 0.0f)
                ref->addTempThreat(fThreat);
        }
        else
            ref->resetTempThreat();

        ref = ref->next();
    }
}

//=================================================

void HostileRefManager::addThreatPercent(int32 iPercent)
{
    HostileReference* ref;

    ref = getFirst();
    while (ref != NULL)
    {
        ref->addThreatPercent(iPercent);
        ref = ref->next();
    }
}

//=================================================
// The online / offline status is given to the method. The calculation has to be done before

void HostileRefManager::setOnlineOfflineState(bool bIsOnline)
{
    HostileReference* ref;

    ref = getFirst();
    while (ref != NULL)
    {
        ref->setOnlineOfflineState(bIsOnline);
        ref = ref->next();
    }
}

//=================================================
// The online / offline status is calculated and set

void HostileRefManager::updateThreatTables()
{
    HostileReference* ref = getFirst();
    while (ref)
    {
        ref->updateOnlineStatus();
        ref = ref->next();
    }
}

//=================================================
// The references are not needed anymore
// tell the source to remove them from the list and free the mem

void HostileRefManager::deleteReferences()
{
    HostileReference* ref = getFirst();
    while (ref)
    {
        HostileReference* nextRef = ref->next();
        ref->removeReference();
        delete ref;
        ref = nextRef;
    }
}

//=================================================
// delete one reference, defined by faction

void HostileRefManager::deleteReferencesForFaction(uint32 faction)
{
    HostileReference* ref = getFirst();
    while (ref)
    {
        HostileReference* nextRef = ref->next();
        if (ref->getSource()->getOwner()->getFactionTemplateEntry()->faction == faction)
        {
            ref->removeReference();
            delete ref;
        }
        ref = nextRef;
    }
}

//=================================================
// delete one reference, defined by Unit

void HostileRefManager::deleteReference(Unit *pCreature)
{
    HostileReference* ref = getFirst();
    while (ref)
    {
        HostileReference* nextRef = ref->next();
        if (ref->getSource()->getOwner() == pCreature)
        {
            ref->removeReference();
            delete ref;
            break;
        }
        ref = nextRef;
    }
}

//=================================================
// set state for one reference, defined by Unit

void HostileRefManager::setOnlineOfflineState(Unit *pCreature, bool bIsOnline)
{
    HostileReference* ref = getFirst();
    while (ref)
    {
        HostileReference* nextRef = ref->next();
        if (ref->getSource()->getOwner() == pCreature)
        {
            ref->setOnlineOfflineState(bIsOnline);
            break;
        }
        ref = nextRef;
    }
}

//=================================================

void HostileRefManager::UpdateVisibility()
{
    HostileReference* ref = getFirst();
    while (ref)
    {
        HostileReference* nextRef = ref->next();
        if (!ref->getSource()->getOwner()->canSeeOrDetect(getOwner()))
        {
            HostileReference* nextRef = ref->next();
            ref->removeReference();
            delete ref;
        }
        ref = nextRef;
    }
}