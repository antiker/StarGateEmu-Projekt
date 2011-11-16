/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef TRINITYCORE_WORLDPACKET_H
#define TRINITYCORE_WORLDPACKET_H

#include "Common.h"
#include "ByteBuffer.h"

class WorldPacket : public ByteBuffer
{
    public:
                                                            // just container for later use
        WorldPacket()                                       : ByteBuffer(0), m_opcode(0)
        {
        }
        explicit WorldPacket(uint32 opcode, size_t res=200, bool hack = false) : ByteBuffer(res), m_opcode(opcode)
        {
            // This is a hack fix.
            // The client will not 'eat' certain opcodes when they're sent under normal circumstances.
            // This is due to the new redirection system implemented by Blizzard in Cataclysm.
            // Another solution to get them handled would be to patch the client even heavier than we already do.
            // In this case, I choose to spread hacks in our code, rather than in Blizzard's
            // - Dvlpr
            if (hack)
            {
                m_opcode = SMSG_MULTIPLE_PACKETS;
                *this << uint16(opcode);
            }
        }
                                                            // copy constructor
        WorldPacket(const WorldPacket &packet)              : ByteBuffer(packet), m_opcode(packet.m_opcode)
        {
        }

        void Initialize(uint32 opcode, size_t newres=200, bool hack = false)
        {
            clear();
            _storage.reserve(newres);

            if (hack)
            {
                m_opcode = SMSG_MULTIPLE_PACKETS;
                *this << uint16(opcode);
            }
            else m_opcode = opcode;
        }

        uint32 GetOpcode() const { return m_opcode; }
        void SetOpcode(uint32 opcode) { m_opcode = opcode; }

    protected:

        uint32 m_opcode;
};
#endif