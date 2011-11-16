/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef TRINITY_WAYPOINTMANAGER_H
#define TRINITY_WAYPOINTMANAGER_H

#include <ace/Singleton.h>
#include <ace/Null_Mutex.h>
#include <vector>

struct WaypointData
{
    uint32 id;
    float x, y, z;
    bool run;
    uint32 delay;
    uint32 event_id;
    uint8 event_chance;
};

typedef std::vector<WaypointData*> WaypointPath;
typedef UNORDERED_MAP<uint32, WaypointPath> WaypointPathContainer;

class WaypointMgr
{
        friend class ACE_Singleton<WaypointMgr, ACE_Null_Mutex>;

    public:
        // Attempts to reload a single path from database
        void ReloadPath(uint32 id);

        // Loads all paths from database, should only run on startup
        void Load();

        // Returns the path from a given id
        WaypointPath const* GetPath(uint32 id) const
        {
            WaypointPathContainer::const_iterator itr = _waypointStore.find(id);
            if (itr != _waypointStore.end())
                return &itr->second;

            return NULL;
        }

    private:
        // Only allow instantiation from ACE_Singleton
        WaypointMgr();
        ~WaypointMgr();

        WaypointPathContainer _waypointStore;
};

#define sWaypointMgr ACE_Singleton<WaypointMgr, ACE_Null_Mutex>::instance()

#endif