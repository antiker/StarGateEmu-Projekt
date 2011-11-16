/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef _VMAPFACTORY_H
#define _VMAPFACTORY_H

#include "IVMapManager.h"

/**
This is the access point to the VMapManager.
*/

namespace VMAP
{
    //===========================================================

    class VMapFactory
    {
        public:
            static IVMapManager* createOrGetVMapManager();
            static void clear();

            static void preventSpellsFromBeingTestedForLoS(const char* pSpellIdString);
            static bool checkSpellForLoS(unsigned int pSpellId);
    };
}
#endif