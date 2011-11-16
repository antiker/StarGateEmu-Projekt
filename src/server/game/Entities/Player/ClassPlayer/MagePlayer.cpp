/*
 * Copyright (C) 2010-2011 Project StarGate
 */

#include "gamePCH.h"
#include "MagePlayer.h"
#include "ScriptPCH.h"

class player_mage_scripts : public PlayerScript
{
public:
    player_mage_scripts() : PlayerScript("player_mage_scripts") {}

    void OnSpellCastWithProto(Player* player, SpellEntry const *spellProto)
    {
        if (player->getClass() == CLASS_MAGE && spellProto->Id != 7268 && spellProto->Id != 5143 && !player->HasAura(79683))
        {
            if (SpellEffectEntry const* spellEffect = spellProto->GetSpellEffect(EFFECT_0))
            {
                if (spellEffect->Effect == SPELL_EFFECT_SCHOOL_DAMAGE)
                {
                    uint32 Chance = urand(1, 5); // Every number has %20 chance
                    if (player->HasSpell(5143) && (Chance == 1 || Chance == 2)) // 40% Chance
                        player->CastSpell(player, 79683, true);
                }
            }
        }
    }
    void OnAura(Player* player, SpellEntry const *spellProto)
    {
    }
};

void AddSC_player_mage_scripts()
{
    new player_mage_scripts;
}