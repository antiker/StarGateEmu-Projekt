/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef TRINITY_CONFUSEDGENERATOR_H
#define TRINITY_CONFUSEDGENERATOR_H

#include "MovementGenerator.h"
#include "DestinationHolder.h"
#include "Traveller.h"

#define MAX_CONF_WAYPOINTS 24

template<class T>
class ConfusedMovementGenerator
: public MovementGeneratorMedium< T, ConfusedMovementGenerator<T> >
{
    public:
        explicit ConfusedMovementGenerator() : i_nextMoveTime(0) {}

        void Initialize(T &);
        void Finalize(T &);
        void Reset(T &);
        bool Update(T &, const uint32 &);

        bool GetDestination(float &x, float &y, float &z) const
        {
            if (i_destinationHolder.HasArrived()) return false;
            i_destinationHolder.GetDestination(x, y, z);
            return true;
        }

        MovementGeneratorType GetMovementGeneratorType() { return CONFUSED_MOTION_TYPE; }
    private:
        void _InitSpecific(T &, bool &, bool &);
        TimeTracker i_nextMoveTime;
        float i_waypoints[MAX_CONF_WAYPOINTS+1][3];
        DestinationHolder< Traveller<T> > i_destinationHolder;
        uint32 i_nextMove;
};
#endif