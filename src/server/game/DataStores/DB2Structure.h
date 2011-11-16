/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef TRINITY_DB2STRUCTURE_H
#define TRINITY_DB2STRUCTURE_H

#include "Common.h"
#include "DBCEnums.h"
#include "Define.h"
#include "Path.h"
#include "Util.h"
#include "Vehicle.h"

#include <map>
#include <set>
#include <vector>
#include "SharedDefines.h"

// Structures using to access raw DB2 data and required packing to portability
struct ItemEntry
{
   uint32   ID;                                             // 0
   uint32   Class;                                          // 1
   uint32   SubClass;                                       // 2 some items have strange subclasses
   int32    Unk0;                                           // 3
   int32    Material;                                       // 4
   uint32   DisplayId;                                      // 5
   uint32   InventoryType;                                  // 6
   uint32   Sheath;                                         // 7
};

struct ItemSparseEntry
{
};

#endif