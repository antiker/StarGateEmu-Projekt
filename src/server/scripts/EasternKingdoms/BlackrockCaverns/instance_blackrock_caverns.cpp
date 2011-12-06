#include "ScriptPCH.h"
#include "blackrock_caverns.h"

#define ENCOUNTERS 5

#define GO_PORTA1 402092
#define GO_PORTA2 315000
#define GO_PORTA3 315001
#define GO_PORTA4 315002

/*Boss Encounters
Rom'Ogg Bonecrusher
Corla, Herald of Twilight
Karsh Steelbender
Beauty
Ascendant Lord Obsidius
*/

class instance_blackrock_caverns : public InstanceMapScript
{
public:
    instance_blackrock_caverns() : InstanceMapScript("instance_blackrock_caverns", 645) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const
    {
        return new instance_blackrock_cavernsInstanceMapScript(map);
    }

    struct instance_blackrock_cavernsInstanceMapScript : public InstanceScript
    {
        instance_blackrock_cavernsInstanceMapScript(InstanceMap* map) : InstanceScript(map) { }

        uint32 uiEncounter[ENCOUNTERS];

        uint64 uiRomoggBonecrusher;
        uint64 uiCorla;
        uint64 uiKarshSteelbender;
        uint64 uiBeauty;
        uint64 uiAscendantLordObsidius;

        uint64 porta1GUID;
        uint64 porta2GUID;
        uint64 porta3GUID;
        uint64 porta4GUID;

        void Initialize()
        {
             uiRomoggBonecrusher = 0;
             uiCorla = 0;
             uiKarshSteelbender = 0;
             uiBeauty = 0;
             uiAscendantLordObsidius = 0;

             porta1GUID = 0;
             porta2GUID = 0;
             porta3GUID = 0;
             porta4GUID = 0;

             for(uint8 i = 0 ; i < ENCOUNTERS; ++i)
                 uiEncounter[i] = NOT_STARTED;
        }

        bool IsEncounterInProgress() const
        {
            for(uint8 i = 0; i < ENCOUNTERS; ++i)
            {
                if (uiEncounter[i] == NOT_STARTED)
                    return true;
            }
            return false;
        }

        void OnCreatureCreate(Creature* pCreature, bool)
        {
            switch(pCreature->GetEntry())
            {
                case BOSS_ROMOGG_BONECRUSHER:
                    uiRomoggBonecrusher = pCreature->GetGUID();
                    break;
                case BOSS_CORLA:
                    uiCorla = pCreature->GetGUID();
                    break;
                case BOSS_KARSH_STEELBENDER:
                    uiKarshSteelbender = pCreature->GetGUID();
                    break;
                case BOSS_BEAUTY:
                    uiBeauty = pCreature->GetGUID();
                    break;
                case BOSS_ASCENDANT_LORD_OBSIDIUS:
                    uiAscendantLordObsidius = pCreature->GetGUID();
                    break;
            }
        }

        void OnGameObjectCreate(GameObject* pGo, bool /*add*/)
        {
            switch(pGo->GetEntry())
            {
            case GO_PORTA1:
                {
                porta1GUID = pGo->GetGUID();
                if (GetData(DATA_ROMOGG_BONECRUSHER_EVENT) == DONE)
                    HandleGameObject(porta1GUID, true, pGo);
                break;
                }
            case GO_PORTA2:
                {
                porta2GUID = pGo->GetGUID();
                if (GetData(DATA_CORLA_EVENT) == DONE)
                    HandleGameObject(porta2GUID, true, pGo);
                break;
                }
            case GO_PORTA3:
                {
                porta3GUID = pGo->GetGUID();
                if (GetData(DATA_KARSH_STEELBENDER_EVENT) == DONE)
                    HandleGameObject(porta3GUID, true, pGo);
                break;
                }
            case GO_PORTA4:
                {
                porta4GUID = pGo->GetGUID();
                if (GetData(DATA_BEAUTY_EVENT) == DONE)
                    HandleGameObject(porta4GUID, true, pGo);
                break;
                }
            }
        }

        uint64 getData64(uint32 identifier)
        {
            switch(identifier)
            {
                case DATA_ROMOGG_BONECRUSHER:
                    return uiRomoggBonecrusher;
                case DATA_CORLA:
                    return uiCorla;
                case DATA_KARSH_STEELBENDER:
                    return uiKarshSteelbender;
                case DATA_BEAUTY:
                    return uiBeauty;
                case DATA_ASCENDANT_LORD_OBSIDIUS:
                    return uiAscendantLordObsidius;
            }
            return 0;
        }

        void SetData(uint32 type, uint32 data)
        {
            switch(type)
            {
                case DATA_ROMOGG_BONECRUSHER_EVENT:
                    uiEncounter[0] = data;
                    if (data == DONE)
                        HandleGameObject(porta1GUID, true);
                    break;
                case DATA_CORLA_EVENT:
                    uiEncounter[1] = data;
                    if (data == DONE)
                        HandleGameObject(porta2GUID, true);
                    break;
                case DATA_KARSH_STEELBENDER_EVENT:
                    uiEncounter[2] = data;
                    if (data == DONE)
                        HandleGameObject(porta3GUID, true);
                    break;
                case DATA_BEAUTY_EVENT:
                    uiEncounter[3] = data;
                    if (data == DONE)
                        HandleGameObject(porta4GUID, true);
                    break;
                case DATA_ASCENDANT_LORD_OBSIDIUS_EVENT:
                    uiEncounter[4] = data;
                    break;
            }
            if (data == DONE)
                SaveToDB();
        }

        uint32 GetData(uint32 type)
        {
            switch(type)
            {
                case DATA_ROMOGG_BONECRUSHER_EVENT:
                    return uiEncounter[0];
                case DATA_CORLA_EVENT:
                    return uiEncounter[1];
                case DATA_KARSH_STEELBENDER_EVENT:
                    return uiEncounter[2];
                case DATA_BEAUTY_EVENT:
                    return uiEncounter[3];
                case DATA_ASCENDANT_LORD_OBSIDIUS_EVENT:
                    return uiEncounter[4];
            }
            return 0;
        }

        std::string GetSaveData()
        {
            OUT_SAVE_INST_DATA;

            std::string str_data;
            std::ostringstream saveStream;
            saveStream << "B C" << " " << uiEncounter[0] << " " << uiEncounter[1] << " " << uiEncounter[2] << " " << uiEncounter[3] << " " << uiEncounter[4];
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

            char dataHead1, dataHead2;
            uint16 data0, data1, data2, data3, data4;

            std::istringstream loadStream(in);
            loadStream >> dataHead1 >> dataHead2 >> data0 >> data1 >> data2 >> data3 >> data4;

            if (dataHead1 == 'B' && dataHead2 == 'C')
            {
                uiEncounter[0] = data0;
                uiEncounter[1] = data1;
                uiEncounter[2] = data2;
                uiEncounter[3] = data3;
                uiEncounter[4] = data4;

                for(uint8 i=0; i < ENCOUNTERS; ++i)
                    if (uiEncounter[i] == IN_PROGRESS)
                        uiEncounter[i] = NOT_STARTED;
            }
            else OUT_LOAD_INST_DATA_FAIL;

            OUT_LOAD_INST_DATA_COMPLETE;
        }
    };
};

void AddSC_instance_blackrock_caverns()
{
    new instance_blackrock_caverns();
}