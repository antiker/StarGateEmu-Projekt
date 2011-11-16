/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef __TRINITY_DRUIDPLAYER_H
#define __TRINITY_DRUIDPLAYER_H

#include "Player.h"

class DruidPlayer: public Player
{
public:
    DruidPlayer(WorldSession * session): Player(session) {}
    virtual uint8 getClass() const { return CLASS_DRUID; }
};

#endif