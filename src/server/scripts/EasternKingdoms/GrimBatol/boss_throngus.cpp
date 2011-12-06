#include "ScriptPCH.h"
#include"ScriptedCreature.h"
#include"grim_batol.h"

#define SAY_AGGRO "Ihr kommt nicht durch die Abwehr!"
#define SAY_AGGRO1 "Ihr seid noch nicht durch die Abwehr!"
#define SAY_AGGRO2 "Throngus benutzt deine Leiche irgentwann auf einen anderen Körper..."
#define SAY_AGGRO3 "Oh, dieser werde Schmerz!"
#define SAY_DIED "Tod... Gute Wahl, nicht die beste wahl aber vieleicht besser als ein fehlschlag im leben!"

enum Spells
{
SPELL_BOUCLIER = 90830, // Bouclier incendiaire
SPELL_FLECHE = 45101, // Flèche enflammée
SPELL_PHALANGE = 74908, // Phalange individuelle
SPELL_ARDENTE = 90764, // Flammes ardentes
SPELL_ROSSER = 47480, // Rosser
SPELL_LAME = 74981, // Double-lames
SPELL_RUGIS = 74976, // Rugissement désorientant
SPELL_GERBE = 90754, // Gerbe de lave
SPELL_ENCOMBRE = 75007, // Encombré
SPELL_HEURT = 75056, // Heurt d’empalement
};

enum Events
{
EVENT_BOUCLIER,
EVENT_FLECHE,
EVENT_PHALANGE,
EVENT_ARDENTE,
EVENT_ROSSER,
EVENT_LAME,
EVENT_RUGIS,
EVENT_GERBE,
EVENT_ENCOMBRE,
EVENT_HEURT,
};

class boss_throngus: public CreatureScript
{
public:
 boss_throngus() : CreatureScript("boss_throngus") { }

 struct boss_throngusAI : public ScriptedAI
    {
        boss_throngusAI(Creature *c) : ScriptedAI(c) {}

EventMap events;

void EnterCombat(Unit* /*who*/)
        {
me->MonsterYell(SAY_AGGRO, LANG_UNIVERSAL, NULL);
        }

void JustDied(Unit* /*killer*/)
        {
me->MonsterYell(SAY_DIED, LANG_UNIVERSAL, NULL);
        }

void Reset()
{
// Techniques de bouclier
events.ScheduleEvent(EVENT_BOUCLIER, 5 *IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_FLECHE, 8 *IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_PHALANGE, 12 *IN_MILLISECONDS);
// Techniques à l’épée
events.ScheduleEvent(EVENT_ARDENTE, 12 *IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_ROSSER, 30 *IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_LAME, 19 *IN_MILLISECONDS);
events.ScheduleEvent(EVENT_RUGIS, 30 *IN_MILLISECONDS);
// Techniques de masse
            events.ScheduleEvent(EVENT_GERBE, 10 *IN_MILLISECONDS);
            events.ScheduleEvent(EVENT_ENCOMBRE, 35 *IN_MILLISECONDS);
events.ScheduleEvent(EVENT_HEURT, 6 *IN_MILLISECONDS);
}

void UpdateAI(const uint32 diff)
        {
                if (!UpdateVictim())
                    return;

events.Update(diff);

while (uint32 eventId = events.ExecuteEvent())
{
switch(eventId)
{

case EVENT_FLECHE:
DoCast(me->getVictim(), SPELL_FLECHE);
events.ScheduleEvent(EVENT_FLECHE, 8 *IN_MILLISECONDS);
return;

if(!HealthAbovePct(90))
{
me->MonsterYell(SAY_AGGRO1, LANG_UNIVERSAL, NULL);
case EVENT_GERBE:
DoCast(me, SPELL_GERBE);
events.ScheduleEvent(EVENT_GERBE, 10 *IN_MILLISECONDS);
return;
case EVENT_ENCOMBRE:
DoCast(me, SPELL_ENCOMBRE);
events.ScheduleEvent(EVENT_ENCOMBRE, 35 *IN_MILLISECONDS);
return;
case EVENT_HEURT:
DoCast(me, SPELL_HEURT);
events.ScheduleEvent(EVENT_HEURT, 6 *IN_MILLISECONDS);
return;
}

if(!HealthAbovePct(50))
{
me->MonsterYell(SAY_AGGRO2, LANG_UNIVERSAL, NULL);
case EVENT_ARDENTE:
DoCast(me, SPELL_ARDENTE);
events.ScheduleEvent(EVENT_ARDENTE, 12 *IN_MILLISECONDS);
return;
case EVENT_ROSSER:
DoCast(me, SPELL_ROSSER);
events.ScheduleEvent(EVENT_ROSSER, 30 *IN_MILLISECONDS);
return;
case EVENT_LAME:
DoCast(me, SPELL_LAME);
events.ScheduleEvent(EVENT_LAME, 19 *IN_MILLISECONDS);
return;
case EVENT_RUGIS:
DoCast(me, SPELL_RUGIS);
events.ScheduleEvent(EVENT_RUGIS, 30 *IN_MILLISECONDS);
return;
}

if(!HealthAbovePct(20))
{
me->MonsterYell(SAY_AGGRO3, LANG_UNIVERSAL, NULL);
case EVENT_BOUCLIER:
DoCast(me, SPELL_BOUCLIER);
events.ScheduleEvent(EVENT_BOUCLIER, 5 *IN_MILLISECONDS);
return;
case EVENT_PHALANGE:
DoCast(me, SPELL_PHALANGE);
events.ScheduleEvent(EVENT_PHALANGE, 12 *IN_MILLISECONDS);
return;
}
}
}
DoMeleeAttackIfReady();

}
};
    CreatureAI* GetAI(Creature* pCreature) const
    {
        return new boss_throngusAI (pCreature);
    }

};

void AddSC_boss_throngus()
{
    new boss_throngus();
}