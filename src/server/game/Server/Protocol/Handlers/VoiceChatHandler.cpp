/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#include "gamePCH.h"
#include "Common.h"
#include "WorldPacket.h"
#include "WorldSession.h"
#include "Opcodes.h"
#include "Log.h"

void WorldSession::HandleVoiceSessionEnableOpcode(WorldPacket & recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_VOICE_SESSION_ENABLE");
    // uint8 isVoiceEnabled, uint8 isMicrophoneEnabled
    recv_data.read_skip<uint8>();
    recv_data.read_skip<uint8>();
    recv_data.hexlike();
}

void WorldSession::HandleChannelVoiceOnOpcode(WorldPacket & recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_CHANNEL_VOICE_ON");
    // Enable Voice button in channel context menu
    recv_data.hexlike();
}

void WorldSession::HandleSetActiveVoiceChannel(WorldPacket & recv_data)
{
    sLog->outDebug(LOG_FILTER_NETWORKIO, "WORLD: CMSG_SET_ACTIVE_VOICE_CHANNEL");
    recv_data.read_skip<uint32>();
    recv_data.read_skip<char*>();
    recv_data.hexlike();
}