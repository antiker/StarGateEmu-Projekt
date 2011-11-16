/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef _ITEM_ENCHANTMENT_MGR_H
#define _ITEM_ENCHANTMENT_MGR_H

#include "Common.h"

void LoadRandomEnchantmentsTable();
uint32 GetItemEnchantMod(int32 entry);
uint32 GenerateEnchSuffixFactor(uint32 item_id);
#endif