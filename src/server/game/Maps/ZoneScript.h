/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef ZONE_SCRIPT_H_
#define ZONE_SCRIPT_H_

#include "Common.h"
#include "Creature.h"

//struct CreatureData;
class Creature;
class GameObject;

class ZoneScript
{
    public:
        ZoneScript() {}
        virtual ~ZoneScript() {}

        virtual uint32 GetCreatureEntry(uint32 /*guidlow*/, const CreatureData *data) { return data->id; }
        virtual uint32 GetGameObjectEntry(uint32 /*guidlow*/, uint32 entry) { return entry; }

        virtual void OnCreatureCreate(Creature *, bool /*add*/) {}
        virtual void OnGameObjectCreate(GameObject * /*go*/, bool /*add*/) {}

        virtual void OnCreatureDeath(Creature* /*creature*/) {}

        //All-purpose data storage 64 bit
        virtual uint64 GetData64(uint32 /*DataId*/) { return 0; }
        virtual void SetData64(uint32 /*DataId*/, uint64 /*Value*/) {}

        //All-purpose data storage 32 bit
        virtual uint32 GetData(uint32 /*DataId*/) { return 0; }
        virtual void SetData(uint32 /*DataId*/, uint32 /*Value*/) {}

        virtual void ProcessEvent(GameObject * /*obj*/, uint32 /*eventId*/) {}
        virtual void ProcessEvent(Unit* /*unit*/, uint32 /*eventId*/) {}
};

#endif