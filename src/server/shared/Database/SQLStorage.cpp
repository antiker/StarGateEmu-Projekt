/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#include "SQLStorage.h"
#include "SQLStorageImpl.h"

const char CreatureInfosrcfmt[]="iiiiiiiiiisssiiiiiiifffiffiifiiiiiiiiiiffiiiiiiiiiiiiiiiiiiiiiiiisiifffliiiiiiiliiisi";
const char CreatureInfodstfmt[]="iiiiiiiiiisssibbiiiifffiffiifiiiiiiiiiiffiiiiiiiiiiiiiiiiiiiiiiiisiifffliiiiiiiliiiii";
const char CreatureDataAddonInfofmt[]="iiiiiis";
const char CreatureModelfmt[]="iffbi";
const char CreatureInfoAddonInfofmt[]="iiiiiis";
const char EquipmentInfofmt[]="iiii";
const char GameObjectInfosrcfmt[]="iiissssiifiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiissi";
const char GameObjectInfodstfmt[]="iiissssiifiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiisii";
const char ItemPrototypesrcfmt[]="iiiisiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiifiiifiiiiiifiiiiiifiiiiiifiiiiiifiiiisiiiiiiiiiiiiiiiiiiiiiiiiifiiisiiiii";
const char ItemPrototypedstfmt[]="iiiisiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiifiiifiiiiiifiiiiiifiiiiiifiiiiiifiiiisiiiiiiiiiiiiiiiiiiiiiiiiifiiiiiiiii";
const char PageTextfmt[]="isii";
const char InstanceTemplatesrcfmt[]="iiffffsb";
const char InstanceTemplatedstfmt[]="iiffffib";

SQLStorage sCreatureStorage(CreatureInfosrcfmt, CreatureInfodstfmt, "entry", "creature_template");
SQLStorage sCreatureDataAddonStorage(CreatureDataAddonInfofmt, "guid", "creature_addon");
SQLStorage sCreatureModelStorage(CreatureModelfmt, "modelid", "creature_model_info");
SQLStorage sCreatureInfoAddonStorage(CreatureInfoAddonInfofmt, "entry", "creature_template_addon");
SQLStorage sEquipmentStorage(EquipmentInfofmt, "entry", "creature_equip_template");
SQLStorage sGOStorage(GameObjectInfosrcfmt, GameObjectInfodstfmt, "entry", "gameobject_template");
SQLStorage sItemStorage(ItemPrototypesrcfmt, ItemPrototypedstfmt, "entry", "item_template");
SQLStorage sPageTextStore(PageTextfmt, "entry", "page_text");
SQLStorage sInstanceTemplate(InstanceTemplatesrcfmt, InstanceTemplatedstfmt, "map", "instance_template");

void SQLStorage::Free ()
{
    uint32 offset=0;
    for (uint32 x=0; x<iNumFields; x++)
        if (dst_format[x]==FT_STRING)
        {
            for (uint32 y=0; y<MaxEntry; y++)
                if (pIndex[y])
                    delete [] *(char**)((char*)(pIndex[y])+offset);

            offset += sizeof(char*);
        }
        else if (dst_format[x]==FT_LOGIC)
            offset += sizeof(bool);
        else if (dst_format[x]==FT_BYTE)
            offset += sizeof(char);
        else
            offset += 4;

    delete [] pIndex;
    delete [] data;
}

void SQLStorage::Load()
{
    SQLStorageLoader loader;
    loader.Load(*this);
}