/*
 * Copyright (C) 2010-2011 Project StarGate
 */

/// \addtogroup world
/// @{
/// \file

#ifndef __WEATHERMGR_H
#define __WEATHERMGR_H

#include "Common.h"
#include "SharedDefines.h"
#include "Timer.h"
#include "Weather.h"
#include <ace/Singleton.h>

class WeatherMgr
{
    friend class ACE_Singleton<WeatherMgr, ACE_Null_Mutex>;
    WeatherMgr() {}
    ~WeatherMgr();

    public:

        void LoadWeatherData();

        Weather* FindWeather(uint32 id) const;
        Weather* AddWeather(uint32 zone_id);
        void RemoveWeather(uint32 zone_id);

        WeatherData const* GetWeatherChances(uint32 zone_id) const
        {
            WeatherZoneMap::const_iterator itr = mWeatherZoneMap.find(zone_id);
            if (itr != mWeatherZoneMap.end())
                return &itr->second;
            else
                return NULL;
        }

        void Update(uint32 diff);

        typedef UNORDERED_MAP<uint32, Weather*> WeatherMap;
        typedef UNORDERED_MAP<uint32, WeatherData> WeatherZoneMap;

    private:

        WeatherMap m_weathers;
        WeatherZoneMap mWeatherZoneMap;
};

#define sWeatherMgr ACE_Singleton<WeatherMgr, ACE_Null_Mutex>::instance()

#endif