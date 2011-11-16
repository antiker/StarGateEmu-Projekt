/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef __TRINITY_DKPLAYER_H
#define __TRINITY_DKPLAYER_H

#include "Player.h"

class DKPlayer: public Player
{
public:
    DKPlayer(WorldSession * session): Player(session) {}
    virtual uint8 getClass() const { return CLASS_DEATH_KNIGHT; }
};

#endif