/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#ifndef TRINITYCORE_DYNAMICOBJECT_H
#define TRINITYCORE_DYNAMICOBJECT_H

#include "Object.h"

class Unit;
class Aura;
struct SpellEntry;

class DynamicObject : public WorldObject, public GridObject<DynamicObject>
{
    public:
        explicit DynamicObject();
        ~DynamicObject();

        void AddToWorld();
        void RemoveFromWorld();

        bool Create(uint32 guidlow, Unit *caster, uint32 spellId, const Position &pos, float radius, bool active);
        void Update(uint32 p_time);
        void Remove();
        void SetDuration(int32 newDuration);
        int32 GetDuration() const;
        void Delay(int32 delaytime);
        void SetAura(Aura * aura);
        void RemoveAura();
        void SetCasterViewpoint();
        void RemoveCasterViewpoint();
        Unit * GetCaster() const { return m_caster; }
        void BindToCaster();
        void UnbindFromCaster();
        uint32 GetSpellId() const {  return GetUInt32Value(DYNAMICOBJECT_SPELLID); }
        uint64 GetCasterGUID() const { return GetUInt64Value(DYNAMICOBJECT_CASTER); }
        float GetRadius() const { return GetFloatValue(DYNAMICOBJECT_RADIUS); }

        void Say(int32 textId, uint32 language, uint64 TargetGuid) { MonsterSay(textId, language, TargetGuid); }
        void Yell(int32 textId, uint32 language, uint64 TargetGuid) { MonsterYell(textId, language, TargetGuid); }
        void TextEmote(int32 textId, uint64 TargetGuid) { MonsterTextEmote(textId, TargetGuid); }
        void Whisper(int32 textId, uint64 receiver) { MonsterWhisper(textId, receiver); }
        void YellToZone(int32 textId, uint32 language, uint64 TargetGuid) { MonsterYellToZone(textId, language, TargetGuid); }

    protected:
        int32 m_duration; // for non-aura dynobjects
        Aura * m_aura;
        Unit * m_caster;
        bool m_isViewpoint;
};
#endif