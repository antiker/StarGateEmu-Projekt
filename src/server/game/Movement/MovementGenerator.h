/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef TRINITY_MOVEMENTGENERATOR_H
#define TRINITY_MOVEMENTGENERATOR_H

#include "Define.h"
#include <ace/Singleton.h>
#include "ObjectRegistry.h"
#include "FactoryHolder.h"
#include "Common.h"
#include "MotionMaster.h"

class Unit;

class MovementGenerator
{
    public:
        virtual ~MovementGenerator();

        virtual void Initialize(Unit &) = 0;
        virtual void Finalize(Unit &) = 0;

        virtual void Reset(Unit &) = 0;

        virtual bool Update(Unit &, const uint32 &time_diff) = 0;

        virtual MovementGeneratorType GetMovementGeneratorType() = 0;

        virtual void unitSpeedChanged() { }

        virtual bool GetDestination(float& /*x*/, float& /*y*/, float& /*z*/) const { return false; }
};

template<class T, class D>
class MovementGeneratorMedium : public MovementGenerator
{
    public:
        void Initialize(Unit &u)
        {
            //u->AssertIsType<T>();
            (static_cast<D*>(this))->Initialize(*((T*)&u));
        }
        void Finalize(Unit &u)
        {
            //u->AssertIsType<T>();
            (static_cast<D*>(this))->Finalize(*((T*)&u));
        }
        void Reset(Unit &u)
        {
            //u->AssertIsType<T>();
            (static_cast<D*>(this))->Reset(*((T*)&u));
        }
        bool Update(Unit &u, const uint32 &time_diff)
        {
            //u->AssertIsType<T>();
            return (static_cast<D*>(this))->Update(*((T*)&u), time_diff);
        }
    public:
        // will not link if not overridden in the generators
        void Initialize(T &u);
        void Finalize(T &u);
        void Reset(T &u);
        bool Update(T &u, const uint32 &time_diff);
};

struct SelectableMovement : public FactoryHolder<MovementGenerator, MovementGeneratorType>
{
    SelectableMovement(MovementGeneratorType mgt) : FactoryHolder<MovementGenerator, MovementGeneratorType>(mgt) {}
};

template<class REAL_MOVEMENT>
struct MovementGeneratorFactory : public SelectableMovement
{
    MovementGeneratorFactory(MovementGeneratorType mgt) : SelectableMovement(mgt) {}

    MovementGenerator* Create(void *) const;
};

typedef FactoryHolder<MovementGenerator, MovementGeneratorType> MovementGeneratorCreator;
typedef FactoryHolder<MovementGenerator, MovementGeneratorType>::FactoryHolderRegistry MovementGeneratorRegistry;
typedef FactoryHolder<MovementGenerator, MovementGeneratorType>::FactoryHolderRepository MovementGeneratorRepository;
#endif