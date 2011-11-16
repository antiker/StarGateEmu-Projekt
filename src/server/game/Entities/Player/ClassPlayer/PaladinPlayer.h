/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef __TRINITY_PALADINPLAYER_H
#define __TRINITY_PALADINPLAYER_H

#include "Player.h"

class PaladinPlayer: public Player
{
public:
    PaladinPlayer(WorldSession * session): Player(session) {}
    virtual uint8 getClass() const { return CLASS_PALADIN; }
};

#endif