/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: instance_gundrak
SD%Complete: 0
SDComment:
SDCategory: Gundrak
EndScriptData */

#include "precompiled.h"
#include "gundrak.h"

bool GOHello_go_gundrak_altar(Player* pPlayer, GameObject* pGo)
{
    ScriptedInstance* pInstance = (ScriptedInstance*)pGo->GetInstanceData();

    if (!pInstance)
        return false;

    switch(pGo->GetEntry())
    {
        case GO_ALTAR_OF_SLADRAN:  pInstance->SetData(TYPE_SLADRAN, SPECIAL);  break;
        case GO_ALTAR_OF_MOORABI:  pInstance->SetData(TYPE_MOORABI, SPECIAL);  break;
        case GO_ALTAR_OF_COLOSSUS: pInstance->SetData(TYPE_COLOSSUS, SPECIAL); break;
    }

    pGo->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
    return true;
}

struct MANGOS_DLL_DECL instance_gundrak : public ScriptedInstance
{
	instance_gundrak(Map* pMap) : ScriptedInstance(pMap) {Initialize();};

    uint32 m_auiEncounter[MAX_ENCOUNTER];
    std::string strInstData;

    uint64 m_uiEckDoorGUID;
    uint64 m_uiEckUnderwaterDoorGUID;
    uint64 m_uiGaldarahDoorGUID;
    uint64 m_uiExitDoorLeftGUID;
    uint64 m_uiExitDoorRightGUID;
    uint64 m_uiSnakeKeyGUID;
    uint64 m_uiMammothKeyGUID;
    uint64 m_uiTrollKeyGUID;
    uint64 m_uiRhinoKeyGUID;
    uint64 m_uiAltarOfSladranGUID;
    uint64 m_uiAltarOfMoorabiGUID;
    uint64 m_uiAltarOfColossusGUID;
	uint64 m_uiBridgeGUID;
    uint64 m_uiCollisionGUID;

    uint64 m_uiSladranGUID;
    uint64 m_uiElementalGUID;
    uint64 m_uiColossusGUID;
	uint64 m_uiMoorabiGUID;
	uint64 m_uiEckGUID;
	uint64 m_uiGaldarahGUID;

	bool m_bBridgeActivated;

    void Initialize()
    {
        memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

		m_uiEckDoorGUID				= 0;	
		m_uiEckUnderwaterDoorGUID	= 0;
		m_uiGaldarahDoorGUID		= 0;
		m_uiExitDoorLeftGUID		= 0;
		m_uiExitDoorRightGUID		= 0;
		m_uiSnakeKeyGUID			= 0;
		m_uiMammothKeyGUID			= 0;
		m_uiTrollKeyGUID			= 0;
		m_uiRhinoKeyGUID			= 0;
		m_uiAltarOfSladranGUID		= 0;
		m_uiAltarOfMoorabiGUID		= 0;
		m_uiAltarOfColossusGUID		= 0;
		uint64 m_uiBridgeGUID		= 0;
		m_uiCollisionGUID			= 0;

		m_uiSladranGUID				= 0;
		m_uiElementalGUID			= 0;
		m_uiColossusGUID			= 0;
		m_uiMoorabiGUID				= 0;
		m_uiEckGUID					= 0;
		m_uiGaldarahGUID			= 0;

		bool m_bBridgeActivated		= false;

    }

	void OnCreatureCreate(Creature* pCreature)
	{
		switch(pCreature->GetEntry())
		{
			case NPC_SLADRAN:   m_uiSladranGUID   = pCreature->GetGUID(); break;
			case NPC_ELEMENTAL: m_uiElementalGUID = pCreature->GetGUID(); break;
			case NPC_COLOSSUS:  m_uiColossusGUID  = pCreature->GetGUID(); break;
			case NPC_MOORABI: m_uiMoorabiGUID = pCreature->GetGUID(); break;
			case NPC_ECK: m_uiEckGUID = pCreature->GetGUID(); break;
			case NPC_GALDARAH: m_uiGaldarahGUID = pCreature->GetGUID(); break;
		}
	}

	void OnObjectCreate(GameObject* pGo)
	{
		switch(pGo->GetEntry())
		{
			case GO_ECK_DOOR:
				m_uiEckDoorGUID = pGo->GetGUID();
				if (m_auiEncounter[TYPE_MOORABI] == DONE && !instance->IsRegularDifficulty())
					DoUseDoorOrButton(m_uiEckDoorGUID);
				break;
			case GO_ECK_UNDERWATER_DOOR:
				m_uiEckUnderwaterDoorGUID = pGo->GetGUID();
				if (m_auiEncounter[TYPE_ECK] == DONE)
					DoUseDoorOrButton(m_uiEckUnderwaterDoorGUID);
				break;
			case GO_GALDARAH_DOOR:
				m_uiGaldarahDoorGUID = pGo->GetGUID();
				DoUseDoorOrButton(m_uiGaldarahDoorGUID);
				break;
			case GO_EXIT_DOOR_L:
				m_uiExitDoorLeftGUID = pGo->GetGUID();
				if (m_auiEncounter[TYPE_GALDARAH] == DONE)
					DoUseDoorOrButton(m_uiExitDoorLeftGUID);
				break;
			case GO_EXIT_DOOR_R:
				m_uiExitDoorRightGUID = pGo->GetGUID();
				if (m_auiEncounter[TYPE_GALDARAH] == DONE)
					DoUseDoorOrButton(m_uiExitDoorRightGUID);
				break;
			case GO_ALTAR_OF_SLADRAN:
				m_uiAltarOfSladranGUID = pGo->GetGUID();
				if (m_auiEncounter[TYPE_SLADRAN] == DONE)
					pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
				break;
			case GO_ALTAR_OF_MOORABI:
				m_uiAltarOfMoorabiGUID = pGo->GetGUID();
				if (m_auiEncounter[TYPE_MOORABI] == DONE)
					pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
				break;
			case GO_ALTAR_OF_COLOSSUS:
				m_uiAltarOfColossusGUID = pGo->GetGUID();
				if (m_auiEncounter[TYPE_COLOSSUS] == DONE)
					pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
					break;
			case GO_SNAKE_KEY:
				m_uiSnakeKeyGUID = pGo->GetGUID();
				if (m_auiEncounter[TYPE_SLADRAN] == SPECIAL)
					DoUseDoorOrButton(m_uiSnakeKeyGUID);
				break;
			case GO_TROLL_KEY:
				m_uiTrollKeyGUID = pGo->GetGUID();
				if (m_auiEncounter[TYPE_COLOSSUS] == SPECIAL)
					DoUseDoorOrButton(m_uiTrollKeyGUID);
				break;
			case GO_MAMMOTH_KEY:
				m_uiMammothKeyGUID = pGo->GetGUID();
				if (m_auiEncounter[TYPE_MOORABI] == SPECIAL)
					DoUseDoorOrButton(m_uiMammothKeyGUID);
				break;
			case GO_RHINO_KEY:
				m_uiRhinoKeyGUID = pGo->GetGUID();
				if (m_auiEncounter[TYPE_ECK] == DONE || !instance->IsRegularDifficulty())
					DoUseDoorOrButton(m_uiRhinoKeyGUID);
				break;
			case GO_BRIDGE: 
				m_uiBridgeGUID = pGo->GetGUID();
				break;
			case GO_COLLISION:
				m_uiCollisionGUID = pGo->GetGUID();
				break;
		}
	}

	void SetData(uint32 uiType, uint32 uiData)
	{
		debug_log("SD2: Instance Gundrak: SetData received for type %u with data %u",uiType,uiData);

		switch(uiType)
		{
			case TYPE_SLADRAN:
				m_auiEncounter[TYPE_SLADRAN] = uiData;
				if (uiData == DONE)
					if (GameObject* pGo = instance->GetGameObject(m_uiAltarOfSladranGUID))
						pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
				if (uiData == SPECIAL)
					DoUseDoorOrButton(m_uiSnakeKeyGUID);
			break;
			case TYPE_MOORABI:
				m_auiEncounter[TYPE_MOORABI] = uiData;
				if (uiData == DONE)
				{
					if (!instance->IsRegularDifficulty())
						DoUseDoorOrButton(m_uiEckDoorGUID);
					if (GameObject* pGo = instance->GetGameObject(m_uiAltarOfMoorabiGUID))
						pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
				}
				if (uiData == SPECIAL)
					DoUseDoorOrButton(m_uiMammothKeyGUID);
				break;
			case TYPE_COLOSSUS:
				m_auiEncounter[TYPE_COLOSSUS] = uiData;
				if (uiData == DONE)
					if (GameObject* pGo = instance->GetGameObject(m_uiAltarOfColossusGUID))
						pGo->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_UNK1);
				if (uiData == SPECIAL)
				{
					if (m_auiEncounter[TYPE_MOORABI] == DONE && m_auiEncounter[TYPE_SLADRAN] == DONE)
						if (GameObject* pGo = instance->GetGameObject(m_uiCollisionGUID))
							pGo->Delete();                          // Still no handling of the Bridge available
					DoUseDoorOrButton(m_uiTrollKeyGUID);
				}
				break;
			case TYPE_GALDARAH:
				m_auiEncounter[TYPE_GALDARAH] = uiData;
				DoUseDoorOrButton(m_uiGaldarahDoorGUID);
				if (uiData == DONE)
				{
					DoUseDoorOrButton(m_uiExitDoorLeftGUID);
					DoUseDoorOrButton(m_uiExitDoorRightGUID);
				}
				break;
			case TYPE_ECK:
				m_auiEncounter[TYPE_ECK] = uiData;
				if (uiData == DONE)
				{
					DoUseDoorOrButton(m_uiEckUnderwaterDoorGUID);
					DoUseDoorOrButton(m_uiRhinoKeyGUID);
				}
				break;
			default:
				error_log("SD2: Instance Gundrak: ERROR SetData = %u for type %u does not exist/not implemented.", uiType, uiData);
				break;
		}

		if (uiData == DONE)
		{
			OUT_SAVE_INST_DATA;

			std::ostringstream saveStream;
			saveStream << m_auiEncounter[TYPE_SLADRAN] << " " << m_auiEncounter[TYPE_MOORABI] << " " << m_auiEncounter[TYPE_COLOSSUS] << " " << m_auiEncounter[TYPE_GALDARAH] << " "
				<< m_auiEncounter[TYPE_ECK];

			strInstData = saveStream.str();

			SaveToDB();
			OUT_SAVE_INST_DATA_COMPLETE;
		}
	}

    const char* Save()
    {
        return strInstData.c_str();
    }

	void Load(const char* chrIn)
	{
		if (!chrIn)
		{
			OUT_LOAD_INST_DATA_FAIL;
			return;
		}

		OUT_LOAD_INST_DATA(chrIn);

		std::istringstream loadStream(chrIn);
		loadStream >> m_auiEncounter[TYPE_SLADRAN] >> m_auiEncounter[TYPE_MOORABI] >> m_auiEncounter[TYPE_COLOSSUS] >> m_auiEncounter[TYPE_GALDARAH] >> m_auiEncounter[TYPE_ECK];

		for(uint8 i = 0; i < MAX_ENCOUNTER; ++i)
		{
			if (m_auiEncounter[i] == IN_PROGRESS)
				m_auiEncounter[i] = NOT_STARTED;
		}

		OUT_LOAD_INST_DATA_COMPLETE;
	}

	uint32 GetData(uint32 uiType)
	{
		switch(uiType)
		{
			case TYPE_SLADRAN:
				return m_auiEncounter[TYPE_SLADRAN];
			case TYPE_MOORABI:
				return m_auiEncounter[TYPE_MOORABI];
			case TYPE_COLOSSUS:
				return m_auiEncounter[TYPE_COLOSSUS];
			case TYPE_GALDARAH:
				return m_auiEncounter[TYPE_GALDARAH];
			case TYPE_ECK:
				return m_auiEncounter[TYPE_ECK];
		}
		return 0;
	}

	uint64 GetData64(uint32 uiType)
	{
		switch(uiType)
		{
			case NPC_SLADRAN:
				return m_uiSladranGUID;
			case NPC_ELEMENTAL:
				return m_uiElementalGUID;
			case NPC_COLOSSUS:
				return m_uiColossusGUID;
			case NPC_MOORABI:
				return m_uiMoorabiGUID;
			case NPC_ECK:
				return m_uiEckGUID;
			case NPC_GALDARAH:
				return m_uiGaldarahGUID;
		}
		return 0;
	}

	void Update(uint32)
	{
		if (GetData(TYPE_SLADRAN) == SPECIAL && GetData(TYPE_COLOSSUS) == SPECIAL && GetData(TYPE_MOORABI) == SPECIAL)
		{
			if (!m_bBridgeActivated)
			{
				GameObject* pBridge = instance->GetGameObject(m_uiBridgeGUID);
				GameObject* pCollision = instance->GetGameObject(m_uiCollisionGUID);
				GameObject* pSnakeKey = instance->GetGameObject(m_uiSnakeKeyGUID);
				GameObject* pMammothKey = instance->GetGameObject(m_uiMammothKeyGUID);
				GameObject* pTrollKey = instance->GetGameObject(m_uiTrollKeyGUID);
				GameObject* pRhinoKey = instance->GetGameObject(m_uiRhinoKeyGUID);

				if (pBridge && pCollision && pSnakeKey && pMammothKey && pTrollKey && pRhinoKey)
				{
					pBridge->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
					pCollision->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
					pSnakeKey->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
					pMammothKey->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
					pTrollKey->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
					pRhinoKey->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
				}

				m_bBridgeActivated = true;
			}
		}
	}
}

InstanceData* GetInstanceData_instance_gundrak(Map* pMap)
{
    return new instance_gundrak(pMap);
}

void AddSC_instance_gundrak()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "go_gundrak_altar";
    pNewScript->pGOHello = &GOHello_go_gundrak_altar;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "instance_gundrak";
    pNewScript->GetInstanceData = &GetInstanceData_instance_gundrak;
    pNewScript->RegisterSelf();
}
