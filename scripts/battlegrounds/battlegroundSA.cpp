#include "precompiled.h"
#include "BattleGroundSA.h"
#include "Vehicle.h"

#define Spell_Boom 52408

struct MANGOS_DLL_DECL npc_sa_bombAI : public ScriptedAI
{
    npc_sa_bombAI(Creature* pCreature) : ScriptedAI(pCreature) { SetCombatMovement(false); Reset();	}
	uint32 event_bomb;
	float fx, fy, fz;
    void Reset() { m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PASSIVE); event_bomb = 10000; }
    void Aggro(Unit* who){}
    void JustDied(Unit* Killer){m_creature->ForcedDespawn();}
    void KilledUnit(Unit *victim){}
    void UpdateAI(const uint32 diff)
    {
		if (event_bomb < diff)
		{
			m_creature->GetPosition(fx, fy, fz);
			m_creature->CastSpell(m_creature, 34602, true);
			m_creature->CastSpell(m_creature, 71495, true);
			m_creature->CastSpell(fx,fy,fz,Spell_Boom,true,0,0,m_creature->GetCharmerGuid());
			m_creature->ForcedDespawn();
		} else event_bomb -= diff;
	}
};

CreatureAI* GetAI_npc_sa_bomb(Creature* pCreature)
{
    return new npc_sa_bombAI (pCreature);
}

#define SA_DESPAWN_T 30000

struct MANGOS_DLL_DECL npc_sa_demolisherAI : public ScriptedAI
{
    npc_sa_demolisherAI(Creature* pCreature) : ScriptedAI(pCreature){Reset();}
	bool cramer;
	uint32 timer;
	uint32 faction;
	void Reset() {	m_creature->SetVisibility(VISIBILITY_ON);	timer = SA_DESPAWN_T;	cramer = false;	faction = 0;	}
	void StartEvent(Player* pPlayer)
    {
		if (BattleGround *bg = pPlayer->GetBattleGround())
		{
			if (bg->GetDefender() == pPlayer->GetTeam())
				return;
			else
			{
				if (Creature *vech = pPlayer->SummonCreature(m_creature->GetEntry(), m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 0))
				{
					m_creature->SetVisibility(VISIBILITY_OFF);
					switch(pPlayer->GetTeam())
					{
						case ALLIANCE: faction = BG_IC_TEAM[0]; vech->setFaction(faction); break;
						case HORDE: faction = BG_IC_TEAM[1]; vech->setFaction(faction); break;
					}
					vech->SetHealth(m_creature->GetHealth());
					        
					if (!vech->GetVehicleKit())
						return;

					pPlayer->EnterVehicle(vech->GetVehicleKit(), 0);
					m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
				}
			}
		}
    }

    void UpdateAI(const uint32 diff)
    {
		if (!cramer)
			if (Unit* Charmer = m_creature->GetCharmer())
				cramer = true;

		if (cramer)
		{
			if (!m_creature->GetCharmer())
			{
				m_creature->setFaction(faction);

				if (timer > diff)
					timer -= diff;
				else
					m_creature->ForcedDespawn();

			}
			else
				timer = SA_DESPAWN_T;
		}

    }
};

CreatureAI* GetAI_npc_sa_demolisher(Creature* pCreature)
{
    return new npc_sa_demolisherAI(pCreature);
}

bool GossipHello_npc_sa_demolisher(Player* pPlayer, Creature* pCreature)
{
	pPlayer->CLOSE_GOSSIP_MENU();
	((npc_sa_demolisherAI*)pCreature->AI())->StartEvent(pPlayer);
    return true;
}

struct MANGOS_DLL_DECL npc_sa_cannonAI : public ScriptedAI
{
    npc_sa_cannonAI(Creature* pCreature) : ScriptedAI(pCreature){Reset();}
	bool cramer;
	uint32 timer;
	uint32 faction;
	void Reset() {	m_creature->SetVisibility(VISIBILITY_ON);	timer = SA_DESPAWN_T;	cramer = false;	faction = 0;	}
	void StartEvent(Player* pPlayer)
    {
		if (BattleGround *bg = pPlayer->GetBattleGround())
		{
			if (bg->GetDefender() != pPlayer->GetTeam())
				return;
			else
			{

				if (Creature *vech = pPlayer->SummonCreature(m_creature->GetEntry(), m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), m_creature->GetOrientation(), TEMPSUMMON_CORPSE_DESPAWN, 0))
				{
					m_creature->SetVisibility(VISIBILITY_OFF);
					switch(pPlayer->GetTeam())
					{
						case ALLIANCE: faction = BG_IC_TEAM[0]; vech->setFaction(faction); break;
						case HORDE: faction = BG_IC_TEAM[1]; vech->setFaction(faction); break;
					}
										        
					if (!vech->GetVehicleKit())
						return;

					pPlayer->EnterVehicle(vech->GetVehicleKit(), 0);
					m_creature->DealDamage(m_creature, m_creature->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
				}
			}
		}
    }

    void UpdateAI(const uint32 diff)
    {
		if (!cramer)
			if (Unit* Charmer = m_creature->GetCharmer())
				cramer = true;

		if (cramer)
		{
			if (!m_creature->GetCharmer())
			{
				m_creature->setFaction(faction);

				if (timer > diff)
					timer -= diff;
				else
					m_creature->ForcedDespawn();

			}
			else
				timer = SA_DESPAWN_T;
		}

    }
};

CreatureAI* GetAI_npc_sa_cannon(Creature* pCreature)
{
    return new npc_sa_cannonAI(pCreature);
}

bool GossipHello_npc_sa_cannon(Player* pPlayer, Creature* pCreature)
{
	pPlayer->CLOSE_GOSSIP_MENU();
	((npc_sa_cannonAI*)pCreature->AI())->StartEvent(pPlayer);
    return true;
}

#define GOSSIP_START_EVENT_1		"Запустить строительство Разрушителя!\nВремя строительства 1.5 минуты!\nПовторный запуск прервет предыдущий процесс!"
#define GOSSIP_START_EVENT_2		"Закрыть окно!"

#define NPC_DEMILISHER		28781

#define SA_MESSAGE_0		"Запущено строительство Разрушителя"
#define SA_MESSAGE_1		"Время завершения строительства - 1.5 минуты"
#define SA_MESSAGE_1_1		"Время завершения строительства - 1 минута 20 секунд"
#define SA_MESSAGE_1_2		"Время завершения строительства - 1 минута 10 секунд"
#define SA_MESSAGE_2		"Время завершения строительства - 1 минута"
#define SA_MESSAGE_3		"Время завершения строительства - 50 секунд"
#define SA_MESSAGE_4		"Время завершения строительства - 40 секунд"
#define SA_MESSAGE_5		"Время завершения строительства - 30 секунд"
#define SA_MESSAGE_6		"Время завершения строительства - 20 секунд"
#define SA_MESSAGE_7		"Время завершения строительства - 10 секунд"
#define SA_MESSAGE_8		"СТРОИТЕЛЬСТВО ЗАВЕРШЕНО!"

static float SummonLocations[2][4]=
{
    {1371.06f, -317.046f, 35.001f, 1.916f},
	{1353.24f, 223.91f, 35.2535f, 4.366f},
};

struct MANGOS_DLL_DECL npc_sa_vendorAI : public ScriptedAI
{
    npc_sa_vendorAI(Creature* pCreature) : ScriptedAI(pCreature){Reset();}
	uint32 build_time;
	uint8 gydId;
	bool build;
    void Reset(){build=false;}
	void StartEvent(Player* pPlayer, uint8 gyd)
    {
		build_time = 60000;
		gydId = gyd;
		build=true;
		m_creature->MonsterSay(SA_MESSAGE_0,LANG_UNIVERSAL,0);
		m_creature->MonsterSay(SA_MESSAGE_1,LANG_UNIVERSAL,0);
    }

    void UpdateAI(const uint32 diff)
    {
		if (build)
		{
			if (build_time < diff)
			{
				m_creature->SummonCreature(NPC_DEMILISHER,SummonLocations[gydId][0],SummonLocations[gydId][1],SummonLocations[gydId][2],SummonLocations[gydId][3], TEMPSUMMON_DEAD_DESPAWN, 0);
				m_creature->MonsterSay(SA_MESSAGE_8,LANG_UNIVERSAL,0);
				build=false;
			}else build_time -= diff;

			switch(build_time/2)
			{
				case 40000: m_creature->MonsterSay(SA_MESSAGE_1_1,LANG_UNIVERSAL,0); break;
				case 35000: m_creature->MonsterSay(SA_MESSAGE_1_2,LANG_UNIVERSAL,0); break;
				case 30000: m_creature->MonsterSay(SA_MESSAGE_2,LANG_UNIVERSAL,0); break;
				case 25000: m_creature->MonsterSay(SA_MESSAGE_3,LANG_UNIVERSAL,0); break;
				case 20000: m_creature->MonsterSay(SA_MESSAGE_4,LANG_UNIVERSAL,0); break;
				case 15000: m_creature->MonsterSay(SA_MESSAGE_5,LANG_UNIVERSAL,0); break;
				case 10000: m_creature->MonsterSay(SA_MESSAGE_6,LANG_UNIVERSAL,0); break;
				case 5000: m_creature->MonsterSay(SA_MESSAGE_7,LANG_UNIVERSAL,0); break;
			}
		}
    }
};

CreatureAI* GetAI_npc_sa_vendor(Creature* pCreature)
{
    return new npc_sa_vendorAI(pCreature);
}

bool GossipHello_npc_sa_vendor(Player* pPlayer, Creature* pCreature)
{
	uint8 gyd = NULL;
	if (pCreature->GetEntry() == 29260) {	gyd = 0;	}
	if (pCreature->GetEntry() == 29262) {	gyd = 1;	}
	if (pPlayer->GetMapId() == 607)
		if (BattleGround *bg = pPlayer->GetBattleGround())
			if (bg->GetDefender() != pPlayer->GetTeam() && bg->GetGydController(gyd) == pPlayer->GetTeam())
				pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_EVENT_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_START_EVENT_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_sa_vendor(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
		uint8 gyd = NULL;
		if (pCreature->GetEntry() == 29260) {	gyd = 0;	}
		if (pCreature->GetEntry() == 29262) {	gyd = 1;	}
        pPlayer->CLOSE_GOSSIP_MENU();
		((npc_sa_vendorAI*)pCreature->AI())->StartEvent(pPlayer,gyd);
    }
    if (uiAction == GOSSIP_ACTION_INFO_DEF+2) {	pPlayer->CLOSE_GOSSIP_MENU(); }
    return true;
}

/*######
## go_wintergrasp_def_portal
######*/

static float SpawnLocation[7][3]=
{
    {1468.12f, -225.7f, 30.8969f},
    {1394.07f, 72.3632f, 31.0541f},
    {1216.12f, 47.7665f, 54.2785f},
    {1255.73f, -233.153f, 56.4357f},
    {1065.02f, -89.9522f, 81.0758f},
    {880.162f, -95.979f, 109.835f},
    {880.68f, -120.799f, 109.835f},
};

static float TeleLocation[7][3]=
{
    {1451.72f, -224.863f, 41.9564f},
    {1401.6f, 88.6693f, 41.1833f},
    {1210.68f, 60.3558f, 64.7388f},
    {1245.03f, -226.439f, 66.7201f},
    {1062.83f, -87.1955f, 93.8061f},
    {808.447f, -109.192f, 109.835f},
    {808.447f, -109.192f, 109.835f},
};

bool GOHello_go_wintergrasp_def_portal(Player* pPlayer, GameObject* pGo)
{
	if (pPlayer->GetMapId() == 607)
	{
		if (BattleGround *bg = pPlayer->GetBattleGround())
		{
			if (pPlayer->GetTeam() == bg->GetDefender())
			{
				for (uint32 i=0; i<7; ++i)
				{
					if ((pGo->GetPositionX() == SpawnLocation[i][0]) && 
						(pGo->GetPositionY() == SpawnLocation[i][1]) &&
						(pGo->GetPositionZ() == SpawnLocation[i][2]))
					{
						pPlayer->TeleportTo(bg->GetMapId(),TeleLocation[i][0],TeleLocation[i][1],TeleLocation[i][2],0);
						return true;
					}
				}
			} else pPlayer->MonsterSay("Я не могу это использовать!",LANG_UNIVERSAL,pPlayer);
		}
	}
	return false;
}

void AddSC_battlegroundSA()
{
    Script *newscript;

	newscript = new Script;
    newscript->Name="npc_sa_bomb";
    newscript->GetAI = &GetAI_npc_sa_bomb;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_sa_demolisher";
    newscript->GetAI = &GetAI_npc_sa_demolisher;
    newscript->pGossipHello = &GossipHello_npc_sa_demolisher;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_sa_cannon";
    newscript->GetAI = &GetAI_npc_sa_cannon;
    newscript->pGossipHello = &GossipHello_npc_sa_cannon;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_sa_vendor";
    newscript->GetAI = &GetAI_npc_sa_vendor;
    newscript->pGossipHello = &GossipHello_npc_sa_vendor;
    newscript->pGossipSelect = &GossipSelect_npc_sa_vendor;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_sa_def_portal";
    newscript->pGossipHelloGO = &GOHello_go_wintergrasp_def_portal;
    newscript->RegisterSelf();
}