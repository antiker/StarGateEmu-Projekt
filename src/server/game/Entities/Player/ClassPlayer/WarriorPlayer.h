/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef __TRINITY_WARRIORPLAYER_H
#define __TRINITY_WARRIORPLAYER_H

#include "Player.h"

class WarriorPlayer: public Player
{
public:
    WarriorPlayer(WorldSession * session): Player(session) {}
    virtual uint8 getClass() const { return CLASS_WARRIOR; }
};

#endif