/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#include "gamePCH.h"
#include "zlib.h"
#include "AddonHandler.h"
#include "DatabaseEnv.h"
#include "Opcodes.h"
#include "Log.h"

AddonHandler::AddonHandler()
{
}

AddonHandler::~AddonHandler()
{
}

bool AddonHandler::BuildAddonPacket(WorldPacket *Source, WorldPacket *Target)
{
    WorldPacket data(SMSG_ADDON_INFO);
    data << uint8(0x0C);
    data << uint8(0xC7);
    data << uint8(0x34);
    data << uint8(0xC6);
    for(int i = 0; i < 6; i++)
        data << uint8(0x00);
    data << uint8(0x02);
    data << uint8(0x02);
    return true;
}