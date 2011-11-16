/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef TRINITY_RANDOMMOTIONGENERATOR_H
#define TRINITY_RANDOMMOTIONGENERATOR_H

#include "MovementGenerator.h"
#include "DestinationHolder.h"
#include "Traveller.h"

template<class T>
class RandomMovementGenerator
: public MovementGeneratorMedium< T, RandomMovementGenerator<T> >
{
    public:
        // Wander dist is related on db spawn dist. So what if we wanna set eandom movement on summoned creature?!
        RandomMovementGenerator(float spawn_dist = 0.0f) : i_nextMoveTime(0), wander_distance(spawn_dist) {}

        void _setRandomLocation(T &);
        void Initialize(T &);
        void Finalize(T &);
        void Reset(T &);
        bool Update(T &, const uint32 &);
        bool GetDestination(float &x, float &y, float &z) const;
        void UpdateMapPosition(uint32 mapid, float &x , float &y, float &z)
        {
            i_destinationHolder.GetLocationNow(mapid, x, y, z);
        }
        MovementGeneratorType GetMovementGeneratorType() { return RANDOM_MOTION_TYPE; }
    private:
        TimeTrackerSmall i_nextMoveTime;

        DestinationHolder< Traveller<T> > i_destinationHolder;
        float wander_distance;
        uint32 i_nextMove;
};
#endif