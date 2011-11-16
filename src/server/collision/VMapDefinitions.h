/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef _VMAPDEFINITIONS_H
#define _VMAPDEFINITIONS_H
#include <cstring>

#define LIQUID_TILE_SIZE (533.333f / 128.f)

namespace VMAP
{
    const char VMAP_MAGIC[] = "VMAP_3.0";

    // defined in TileAssembler.cpp currently...
    bool readChunk(FILE *rf, char *dest, const char *compare, uint32 len);
}
#endif