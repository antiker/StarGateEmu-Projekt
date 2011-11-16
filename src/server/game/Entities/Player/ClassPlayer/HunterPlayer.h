/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef __TRINITY_HUNTERPLAYER_H
#define __TRINITY_HUNTERPLAYER_H

#include "Player.h"

class HunterPlayer: public Player
{
public:
    HunterPlayer(WorldSession * session): Player(session) {}
    virtual uint8 getClass() const { return CLASS_HUNTER; }
};

#endif