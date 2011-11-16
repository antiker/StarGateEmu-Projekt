/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef TRINITY_TARGETEDMOVEMENTGENERATOR_H
#define TRINITY_TARGETEDMOVEMENTGENERATOR_H

#include "MovementGenerator.h"
#include "DestinationHolder.h"
#include "Traveller.h"
#include "FollowerReference.h"

class TargetedMovementGeneratorBase
{
    public:
        TargetedMovementGeneratorBase(Unit &target) { i_target.link(&target, this); }
        void stopFollowing() { }
    protected:
        FollowerReference i_target;
};

template<class T>
class TargetedMovementGenerator
: public MovementGeneratorMedium< T, TargetedMovementGenerator<T> >, public TargetedMovementGeneratorBase
{
    public:
        TargetedMovementGenerator(Unit &target, float offset = 0, float angle = 0);
        ~TargetedMovementGenerator() {}

        void Initialize(T &);
        void Finalize(T &);
        void Reset(T &);
        bool Update(T &, const uint32 &);
        MovementGeneratorType GetMovementGeneratorType() { return TARGETED_MOTION_TYPE; }

        void MovementInform(T &);

        Unit* GetTarget() const;

        bool GetDestination(float &x, float &y, float &z) const
        {
            if (i_destinationHolder.HasArrived() || !i_destinationHolder.HasDestination()) return false;
            i_destinationHolder.GetDestination(x, y, z);
            return true;
        }

        void unitSpeedChanged() { i_recalculateTravel=true; }
    private:

        bool _setTargetLocation(T &);

        float i_offset;
        float i_angle;
        DestinationHolder< Traveller<T> > i_destinationHolder;
        bool i_recalculateTravel;
        float i_targetX, i_targetY, i_targetZ;
};
#endif