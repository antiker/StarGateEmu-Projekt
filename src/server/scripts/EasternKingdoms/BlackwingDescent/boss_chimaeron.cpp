/*
 * Copyright (C) 2010-2011 Project StarGate
 * Copyright (C) 2011 MigCore <http://wow-mig.ru/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "ScriptPCH.h"
#include "blackwing_descent.h"

class boss_chimaeron : public CreatureScript
{
public:
    boss_chimaeron() : CreatureScript("boss_chimaeron") { }

    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_chimaeronAI (pCreature);
    }

    struct boss_chimaeronAI : public BossAI
    {
        boss_chimaeronAI(Creature* pCreature) : BossAI(pCreature,DATA_CHIMAERON)
        {
        }

        void Reset() { }

        void EnterCombat(Unit* /*who*/) {}

        void JustDied(Unit* /*Killer*/)
        {
    		_JustDied();
			if (instance)
            instance->SetData(DATA_CHIMAERON, DONE);
        }

        void UpdateAI(const uint32 Diff)
        {
            if (!UpdateVictim())
                return;

            DoMeleeAttackIfReady();
        }
    };
};

void AddSC_boss_chimaeron()
{
    new boss_chimaeron();
}