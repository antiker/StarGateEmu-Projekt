/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef __TRINITY_SHAMANPLAYER_H
#define __TRINITY_SHAMANPLAYER_H

#include "Player.h"

class ShamanPlayer: public Player
{
public:
    ShamanPlayer(WorldSession * session): Player(session) {}
    virtual uint8 getClass() const { return CLASS_SHAMAN; }
};

#endif