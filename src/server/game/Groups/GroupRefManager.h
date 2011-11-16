/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef _GROUPREFMANAGER
#define _GROUPREFMANAGER

#include "RefManager.h"

class Group;
class Player;
class GroupReference;

class GroupRefManager : public RefManager<Group, Player>
{
    public:
        GroupReference* getFirst() { return ((GroupReference*) RefManager<Group, Player>::getFirst()); }
};
#endif