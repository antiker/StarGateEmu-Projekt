/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#include "gamePCH.h"
#include "Opcodes.h"
#include "WorldSession.h"
#include "WorldPacket.h"

void WorldSession::SendAuthResponse(uint8 code, bool shortForm, uint32 queuePos)
{
    WorldPacket packet(SMSG_AUTH_RESPONSE, 1 + 4 + 1 + 4 + 2 + 1 + (shortForm ? 0 : (4 + 1)));
    packet << uint8(code);
    packet << uint32(0);                                        // BillingTimeRemaining
    packet << uint8(0);                                         // BillingPlanFlags
    packet << uint32(0);                                        // BillingTimeRested
    packet << uint8(Expansion());                               // payed expansion
    packet << uint8(Expansion());                               // server expansion

    if (!shortForm)
    {
        packet << uint32(queuePos);                             // Queue position
        packet << uint8(0);                                     // Unk 3.3.0
    }

    SendPacket(&packet);
}

void WorldSession::SendClientCacheVersion(uint32 version)
{
    WorldPacket data(SMSG_CLIENTCACHE_VERSION, 4);
    data << uint32(version);
    SendPacket(&data);
}