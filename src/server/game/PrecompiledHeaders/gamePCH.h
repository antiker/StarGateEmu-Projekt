/*
 * Copyright (C) 2010-2011 Project StarGate
 */

//add here most rarely modified headers to speed up debug build compilation
#ifndef _GAMEPCH_H
#define _GAMEPCH_H
#ifdef TRINITY_COREPCH
#include "WorldSocket.h"        // must be first to make ACE happy with ACE includes in it

#include "Common.h"

#include "MapManager.h"
#include "Log.h"
#include "ObjectAccessor.h"
#include "ObjectDefines.h"
#include "SQLStorage.h"
#include "Opcodes.h"
#include "SharedDefines.h"
#include "ObjectMgr.h"
#include "Util.h"

#endif /* TRINITY_COREPCH */
#endif  /* _GAMEPCH_H */