/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef TRINITY_DB2STORES_H
#define TRINITY_DB2STORES_H

#include "Common.h"
#include "DB2Store.h"
#include "DB2Structure.h"

#include <list>

extern DB2Storage <ItemEntry> sItemStore;

void LoadDB2Stores(const std::string& dataPath);

#endif