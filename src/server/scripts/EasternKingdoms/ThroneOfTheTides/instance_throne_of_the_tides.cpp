#include "ScriptPCH.h"
#include "throne_of_the_tides.h"

enum Factions
{
    FACTION_FRIENDLY = 35
};

class instance_throne_of_the_tides : public InstanceMapScript
{
    public:
        instance_throne_of_the_tides() : InstanceMapScript("instance_throne_of_the_tides", 643) { }

        InstanceScript* GetInstanceScript(InstanceMap* map) const
        {
            return new instance_throne_of_the_tides_InstanceMapScript(map);
        }

        struct instance_throne_of_the_tides_InstanceMapScript : public InstanceScript
        {
            instance_throne_of_the_tides_InstanceMapScript(Map* map) : InstanceScript(map)
            {
                SetBossNumber(MAX_ENCOUNTER);
            }

            uint64 uiLadyNazjar;
            uint64 uiCommanderUlthok;
            uint64 uiErunakStonespeaker;
            uint64 uiMindbenderGhursha;
            uint64 uiOzumat;
            uint64 uiNeptulon;

            uint64 uiLadyNazjarDoor;
            uint64 uiCommanderUlthokDoor;
            uint64 uiErunakStonespeakerDoor;
            uint64 uiOzumatDoor;

            uint32 m_auiEncounter[MAX_ENCOUNTER];

            std::string str_data;

            void Initialize()
            {
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                   m_auiEncounter[i] = NOT_STARTED;

                uiLadyNazjar = 0;
                uiCommanderUlthok = 0;
                uiErunakStonespeaker = 0;
                uiMindbenderGhursha = 0;
                uiOzumat = 0;
                uiNeptulon = 0;

                uiLadyNazjarDoor = 0;
                uiCommanderUlthokDoor = 0;
                uiErunakStonespeakerDoor = 0;
                uiOzumatDoor = 0;
            }

            bool IsEncounterInProgress() const
            {
                for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                    if (m_auiEncounter[i] == IN_PROGRESS) return true;

                return false;
            }

            void OnCreatureCreate(Creature* creature)
            {
                Map::PlayerList const &players = instance->GetPlayers();
                uint32 TeamInInstance = 0;

                if (!players.isEmpty())
                {
                    if (Player* pPlayer = players.begin()->getSource())
                        TeamInInstance = pPlayer->GetTeam();
                }
                switch(creature->GetEntry())
                {
                    case BOSS_LADY_NAZJAR: uiLadyNazjar = creature->GetGUID(); break;
                    case BOSS_COMMANDER_ULTHOK: uiCommanderUlthok = creature->GetGUID(); break;
                    case BOSS_ERUNAK_STONESPEAKER: uiErunakStonespeaker = creature->GetGUID(); break;
                    case BOSS_MINDBENDER_GHURSHA: uiMindbenderGhursha = creature->GetGUID(); break;
                    case BOSS_OZUMAT: uiOzumat = creature->GetGUID(); break;
                    case BOSS_NEPTULON: uiNeptulon = creature->GetGUID(); break;
                    case 50272:
                    {
                        if (ServerAllowsTwoSideGroups())
                            creature->setFaction(FACTION_FRIENDLY);
                        if (TeamInInstance == ALLIANCE)
                            creature->UpdateEntry(50270, ALLIANCE);
                        break;
                    }
                }
            }

            void OnGameObjectCreate(GameObject* go)
            {
                switch(go->GetEntry())
                {
                    case GO_LADY_NAZJAR_DOOR:
                        uiLadyNazjarDoor = go->GetGUID();
                        if (m_auiEncounter[0] == DONE) HandleGameObject(0, true, go);
                        if (m_auiEncounter[0] == IN_PROGRESS) HandleGameObject(0, false, go);
                        break;
                    case GO_COMMANDER_ULTHOK_DOOR:
                        uiCommanderUlthokDoor = go->GetGUID();
                        if (m_auiEncounter[0] == DONE) HandleGameObject(0, false, go);
                        if (m_auiEncounter[1] == DONE) HandleGameObject(0, true, go);
                        break;
                    case GO_ERUNAK_STONESPEAKER_DOOR:
                        uiOzumatDoor = go->GetGUID();
                        if (m_auiEncounter[1] == DONE) HandleGameObject(0, true, go);
                        if (m_auiEncounter[2] == IN_PROGRESS) HandleGameObject(0, false, go);
                        if (m_auiEncounter[2] == DONE) HandleGameObject(0, true, go);
                        break;
                    case GO_OZUMAT_DOOR:
                        uiErunakStonespeakerDoor = go->GetGUID();
                        if (m_auiEncounter[2] == DONE) HandleGameObject(0, true, go);
                        if (m_auiEncounter[3] == IN_PROGRESS) HandleGameObject(0, false, go);
                        if (m_auiEncounter[3] == DONE) HandleGameObject(0, true, go);
                        break;
                }
            }

            void SetData(uint32 type, uint32 data)
            {
                switch(type)
                {
                    case DATA_LADY_NAZJAR_EVENT:
                        m_auiEncounter[0] = data;
                        break;
                    case DATA_COMMANDER_ULTHOK_EVENT:
                        m_auiEncounter[1] = data;
                        break;
                    case DATA_ERUNAK_STONESPEAKER_EVENT:
                        m_auiEncounter[2] = data;
                        break;
                    case DATA_OZUMAT_EVENT:
                        m_auiEncounter[3] = data;
                        break;
                }

                if (data == DONE)
                    SaveToDB();
            }

            uint32 GetData(uint32 type)
            {
                switch(type)
                {
                    case DATA_LADY_NAZJAR_EVENT: return m_auiEncounter[0];
                    case DATA_COMMANDER_ULTHOK_EVENT: return m_auiEncounter[1];
                    case DATA_ERUNAK_STONESPEAKER_EVENT: return m_auiEncounter[2];
                    case DATA_OZUMAT_EVENT: return m_auiEncounter[3];
                }
                return 0;
            }

            uint64 GetData64(uint32 identifier)
            {
                switch(identifier)
                {
                    case DATA_LADY_NAZJAR: return uiLadyNazjar;
                    case DATA_COMMANDER_ULTHOK: return uiCommanderUlthok;
                    case DATA_ERUNAK_STONESPEAKER: return uiErunakStonespeaker;
                    case BOSS_MINDBENDER_GHURSHA: return uiMindbenderGhursha;
                    case DATA_OZUMAT: return uiOzumat;
                    case DATA_NEPTULON: return uiNeptulon;
                }

                return 0;
            }

            std::string GetSaveData()
            {
                OUT_SAVE_INST_DATA;

                std::ostringstream saveStream;
                saveStream << "T o t T " << m_auiEncounter[0] << " " << m_auiEncounter[1] << " "
                    << m_auiEncounter[2] << " " << m_auiEncounter[3];

                str_data = saveStream.str();

                OUT_SAVE_INST_DATA_COMPLETE;
                return str_data;
            }

            void Load(const char* in)
            {
                if (!in)
                {
                    OUT_LOAD_INST_DATA_FAIL;
                    return;
                }

                OUT_LOAD_INST_DATA(in);

                char dataHead1, dataHead2, dataHead3, dataHead4;
                uint16 data0, data1, data2, data3;

                std::istringstream loadStream(in);
                loadStream >> dataHead1 >> dataHead2 >> dataHead3 >> dataHead4 >> data0 >> data1 >> data2 >> data3;

                if (dataHead1 == 'T' && dataHead2 == 'o' && dataHead3 == 't' && dataHead4 == 'T')
                {
                    m_auiEncounter[0] = data0;
                    m_auiEncounter[1] = data1;
                    m_auiEncounter[2] = data2;
                    m_auiEncounter[3] = data3;

                    for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                        if (m_auiEncounter[i] == IN_PROGRESS)
                            m_auiEncounter[i] = NOT_STARTED;

                    if(m_auiEncounter[0] == DONE && m_auiEncounter[1] == NOT_STARTED)
                    {
                        if(Creature* summoner = instance->GetCreature(uiNeptulon))
                            summoner->SummonCreature(BOSS_COMMANDER_ULTHOK, 59.185f, 802.251f, 805.730f, 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 60480000);
                    }
                } else OUT_LOAD_INST_DATA_FAIL;

                OUT_LOAD_INST_DATA_COMPLETE;
            }
        };
};

void AddSC_instance_throne_of_the_tides()
{
    new instance_throne_of_the_tides();
}