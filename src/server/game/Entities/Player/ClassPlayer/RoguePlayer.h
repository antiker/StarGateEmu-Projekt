/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef __TRINITY_ROGUEPLAYER_H
#define __TRINITY_ROGUEPLAYER_H

#include "Player.h"

class RoguePlayer: public Player
{
public:
    RoguePlayer(WorldSession * session): Player(session) {}
    virtual uint8 getClass() const { return CLASS_ROGUE; }
};

#endif