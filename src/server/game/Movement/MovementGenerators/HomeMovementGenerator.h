/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef TRINITY_HOMEMOVEMENTGENERATOR_H
#define TRINITY_HOMEMOVEMENTGENERATOR_H

#include "MovementGenerator.h"
#include "DestinationHolder.h"
#include "Traveller.h"

class Creature;

template < class T >
class HomeMovementGenerator;

template <>
class HomeMovementGenerator<Creature>
: public MovementGeneratorMedium< Creature, HomeMovementGenerator<Creature> >
{
    public:

        HomeMovementGenerator() {}
        ~HomeMovementGenerator() {}

        void Initialize(Creature &);
        void Finalize(Creature &);
        void Reset(Creature &);
        bool Update(Creature &, const uint32 &);
        void modifyTravelTime(uint32 travel_time) { i_travel_timer = travel_time; }
        MovementGeneratorType GetMovementGeneratorType() { return HOME_MOTION_TYPE; }

        bool GetDestination(float& x, float& y, float& z) const { i_destinationHolder.GetDestination(x, y, z); return true; }

    private:
        void _setTargetLocation(Creature &);
        DestinationHolder< Traveller<Creature> > i_destinationHolder;

        float ori;
        uint32 i_travel_timer;
};
#endif