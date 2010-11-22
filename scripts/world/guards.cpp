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
SDName: Guards
SD%Complete: 100
SDComment: CombatAI should be organized better for future.
SDCategory: Guards
EndScriptData */

/* ContentData
guard_azuremyst
guard_bluffwatcher
guard_contested
guard_dalaran
guard_darnassus
guard_dunmorogh
guard_durotar
guard_elwynnforest
guard_eversong
guard_exodar
guard_ironforge
guard_mulgore
guard_orgrimmar
guard_shattrath
guard_shattrath_aldor
guard_shattrath_scryer
guard_silvermoon
guard_stormwind
guard_teldrassil
guard_tirisfal
guard_undercity
EndContentData */

#include "precompiled.h"
#include "guard_ai.h"

CreatureAI* GetAI_guard_azuremyst(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_bluffwatcher(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_contested(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_darnassus(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_dunmorogh(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_durotar(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_elwynnforest(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_eversong(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_exodar(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_ironforge(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_mulgore(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_orgrimmar(Creature* pCreature)
{
    return new guardAI_orgrimmar(pCreature);
}

CreatureAI* GetAI_guard_shattrath(Creature* pCreature)
{
    return new guardAI(pCreature);
}

/*******************************************************
 * guard_shattrath_aldor
 *******************************************************/

struct MANGOS_DLL_DECL guard_shattrath_aldorAI : public guardAI
{
    guard_shattrath_aldorAI(Creature* pCreature) : guardAI(pCreature) { Reset(); }

    uint32 m_uiExile_Timer;
    uint32 m_uiBanish_Timer;
    uint64 m_uiPlayerGUID;
    bool m_bCanTeleport;

    void Reset()
    {
        m_uiBanish_Timer = 5000;
        m_uiExile_Timer = 8500;
        m_uiPlayerGUID = 0;
        m_bCanTeleport = false;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_bCanTeleport)
        {
            if (m_uiExile_Timer < uiDiff)
            {
                if (Player* pTarget = m_creature->GetMap()->GetPlayer(m_uiPlayerGUID))
                {
                    pTarget->CastSpell(pTarget, SPELL_EXILE, true);
                    pTarget->CastSpell(pTarget, SPELL_BANISH_TELEPORT, true);
                }

                m_uiPlayerGUID = 0;
                m_uiExile_Timer = 8500;
                m_bCanTeleport = false;
            }
            else
                m_uiExile_Timer -= uiDiff;
        }
        else if (m_uiBanish_Timer < uiDiff)
        {
            Unit* pVictim = m_creature->getVictim();

            if (pVictim && pVictim->GetTypeId() == TYPEID_PLAYER)
            {
                DoCastSpellIfCan(pVictim, SPELL_BANISHED_SHATTRATH_A);
                m_uiBanish_Timer = 9000;
                m_uiPlayerGUID = pVictim->GetGUID();

                if (m_uiPlayerGUID)
                    m_bCanTeleport = true;
            }
        }
        else
            m_uiBanish_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_guard_shattrath_aldor(Creature* pCreature)
{
    return new guard_shattrath_aldorAI(pCreature);
}

/*******************************************************
 * guard_shattrath_scryer
 *******************************************************/

struct MANGOS_DLL_DECL guard_shattrath_scryerAI : public guardAI
{
    guard_shattrath_scryerAI(Creature* pCreature) : guardAI(pCreature) { Reset(); }

    uint32 m_uiExile_Timer;
    uint32 m_uiBanish_Timer;
    uint64 m_uiPlayerGUID;
    bool m_bCanTeleport;

    void Reset()
    {
        m_uiBanish_Timer = 5000;
        m_uiExile_Timer = 8500;
        m_uiPlayerGUID = 0;
        m_bCanTeleport = false;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_bCanTeleport)
        {
            if (m_uiExile_Timer < uiDiff)
            {
                if (Player* pTarget = m_creature->GetMap()->GetPlayer(m_uiPlayerGUID))
                {
                    pTarget->CastSpell(pTarget, SPELL_EXILE, true);
                    pTarget->CastSpell(pTarget, SPELL_BANISH_TELEPORT, true);
                }

                m_uiPlayerGUID = 0;
                m_uiExile_Timer = 8500;
                m_bCanTeleport = false;
            }
            else
                m_uiExile_Timer -= uiDiff;
        }
        else if (m_uiBanish_Timer < uiDiff)
        {
            Unit* pVictim = m_creature->getVictim();

            if (pVictim && pVictim->GetTypeId() == TYPEID_PLAYER)
            {
                DoCastSpellIfCan(pVictim, SPELL_BANISHED_SHATTRATH_S);
                m_uiBanish_Timer = 9000;
                m_uiPlayerGUID = pVictim->GetGUID();

                if (m_uiPlayerGUID)
                    m_bCanTeleport = true;
            }
        }
        else
            m_uiBanish_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

 /*******************************************************
 * guard_dalaran start
 *******************************************************/

enum{
	GOSSIP_SENDER_ARENA=					2,
	GOSSIP_SENDER_Q=						3,
	GOSSIP_SENDER_BANK=						4,
	GOSSIP_SENDER_I=						5,
	GOSSIP_SENDER_MAIL=						6,
	GOSSIP_SENDER_POI=						7,
	GOSSIP_SENDER_TRAINERS=					8,
	GOSSIP_SENDER_VENDORS=					9,
	GOSSIP_SENDER_ARMOR=					10,
	GOSSIP_SENDER_WEAPONS=					11,
	GOSSIP_SENDER_PROFTRAINER=				12
};

#define GOSSIP_TEXT_ARENA_GER				"Arena"
#define GOSSIP_TEXT_BARBER_GER				"Barbier"
#define GOSSIP_TEXT_CAPITAL_PORTALS			"Portale zu den Hauptstädten"
#define GOSSIP_TEXT_FLIGHT_MASTER			"Den Flugmeister"
#define GOSSIP_TEXT_LOCKSMITH				"Schlosser"
#define GOSSIP_TEXT_POINTS_OF_INTEREST		"Sehenswürdigkeiten"
#define GOSSIP_TEXT_ACTION_HOUSE			"Auktionshaus"
#define GOSSIP_TEXT_BANK_GER				"Die Bank"
#define GOSSIP_TEXT_BATTLEMASTERS			"Kampfmeister"
#define GOSSIP_TEXT_GUILDMASTER_GER			"Gildenmeister"
#define GOSSIP_TEXT_INN_GER					"Gasthaus"
#define GOSSIP_TEXT_MAILBOX_GER				"Einen Briefkasten"
#define GOSSIP_TEXT_STABLEMASTER_GER		"Der Stallmeister"
#define GOSSIP_TEXT_TRAINERS				"Lehrer"
#define GOSSIP_TEXT_VENDOR					"Verkäufer"

//Arena
#define GOSSIP_TEXT_E_S_E					"Östlicher Eingang zur Kanalisation"
#define GOSSIP_TEXT_W_S_E					"Westlicher Eingang zur Kanalisation"
#define GOSSIP_TEXT_W_E						"Brunneneingang"
//Action House
#define GOSSIP_TEXT_A_Q						"Das Viertel der Allianz"
#define GOSSIP_TEXT_H_Q						"Das Viertel der Horde"
//Bank
#define GOSSIP_TEXT_N_B						"Nördliche Bank"
#define GOSSIP_TEXT_S_B						"Südliche Bank"
#define GOSSIP_TEXT_SE						"Die Kanalisation"
//Inn
#define GOSSIP_TEXT_A_I						"Allianzgasthaus"
#define GOSSIP_TEXT_H_I						"Hordengasthaus"
//Mail
#define GOSSIP_TEXT_K_L						"Krasus' Landeplatz"
//Points of Inetrest
#define GOSSIP_TEXT_V_C						"Die Violette Zitadelle"
#define GOSSIP_TEXT_V_H						"Die Violette Festung"
#define GOSSIP_TEXT_T						"Handelsdistrikt"
#define GOSSIP_TEXT_A_M						"Antonidas' Denkmal"
#define GOSSIP_TEXT_R_S						"Runenweberplatz"
#define GOSSIP_TEXT_T_E						"Die Abendruh"
#define GOSSIP_TEXT_C						"Friedhof"
#define GOSSIP_TEXT_L_o_P					"Lexikon der Macht"
//Trainers
#define GOSSIP_TEXT_C_T						"Ein Lehrer für eine Klasse"
#define GOSSIP_TEXT_C_W_F_T					"Lehrer für Kaltwetterflug"
#define GOSSIP_TEXT_Po_T					"Portallehrer"
#define GOSSIP_TEXT_Pr_T					"Ein Lehrer für einen Beruf"
//Vendors
#define GOSSIP_TEXT_A						"Rüstung"
#define GOSSIP_TEXT_Cl						"Kleidung"
#define GOSSIP_TEXT_E_G						"Emblemausrüstung"
#define GOSSIP_TEXT_F						"Blumen"
#define GOSSIP_TEXT_Fr						"Obst"
#define GOSSIP_TEXT_G_G						"Gemischtwaren"
#define GOSSIP_TEXT_J						"Juwelier"
#define GOSSIP_TEXT_P_S_A_E_M				"Tierbedarf & exotische Reittiere"
#define GOSSIP_TEXT_P_P_A_C					"Kuchen, Gebäck & Torten"
#define GOSSIP_TEXT_R_A_M_G					"Reagenzien & magischen Gegenstände"
#define GOSSIP_TEXT_T_GER					"Spielzeug"
#define GOSSIP_TEXT_T_S						"Handwerksbedarf"
#define GOSSIP_TEXT_T_R_A_O_I				"Schmuckstücke, Relikte & Schildhandgegenstände"
#define GOSSIP_TEXT_W						"Waffen"
#define GOSSIP_TEXT_W_A_C					"Wein & Käse"
//Vendor 
#define GOSSIP_TEXT_C_A						"Stoffrüstung"
#define GOSSIP_TEXT_L_A						"Lederrüstung"
#define GOSSIP_TEXT_M_A						"Schwere Rüstung"
#define GOSSIP_TEXT_P_A						"Plattenrüstung"
#define GOSSIP_TEXT_S						"Schilde"
#define GOSSIP_TEXT_M_W						"Nahkampfwaffen"
#define GOSSIP_TEXT_R_A_T_W					"Fernkampf- & Wurfwaffen"
#define GOSSIP_TEXT_S_A_W					"Stäbe und Zauberstäbe"

//Trainer 
#define GOSSIP_TEXT_Al						"Alchemie"
#define GOSSIP_TEXT_Bl						"Schmiedekunst"
#define GOSSIP_TEXT_Co						"Kochkunst"
#define GOSSIP_TEXT_En						"Verzauberkunst"
#define GOSSIP_TEXT_Eng						"Ingenieurskunst"
#define GOSSIP_TEXT_F_A						"Erste Hilfe"
#define GOSSIP_TEXT_Fi						"Angeln"
#define GOSSIP_TEXT_He						"Kräuterkunde"
#define GOSSIP_TEXT_In						"Inschriftenkunde"
#define GOSSIP_TEXT_Jew						"Juwelenschleifen"
#define GOSSIP_TEXT_Le						"Lederverarbeitung"
#define GOSSIP_TEXT_Min						"Bergbau"
#define GOSSIP_TEXT_Skin					"Kürschnerei"
#define GOSSIP_TEXT_Ta						"Schneiderei"

bool GossipHello_guard_dalaran(Player* pPlayer, Creature* pCreature)
{
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ARENA_GER			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_ACTION_HOUSE			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK_GER				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BARBER_GER			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BATTLEMASTERS		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_CAPITAL_PORTALS		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_FLIGHT_MASTER		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_GUILDMASTER_GER		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN_GER				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_LOCKSMITH			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_MAILBOX_GER			, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_POINTS_OF_INTEREST	, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 12);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_STABLEMASTER_GER		, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 13);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_TRAINERS				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 14);
	pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_VENDOR				, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 15);
    pPlayer->SEND_GOSSIP_MENU(14014, pCreature->GetGUID());
    return true;
}
void SendDefaultMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch (action)
	{
		//Arena
		case GOSSIP_ACTION_INFO_DEF + 1: 
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_E_S_E, GOSSIP_SENDER_ARENA, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_W_S_E, GOSSIP_SENDER_ARENA, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_W_E	, GOSSIP_SENDER_ARENA, GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->SEND_GOSSIP_MENU(13976, pCreature->GetGUID());
			break;
		//Action House
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A_Q, GOSSIP_SENDER_Q, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_H_Q, GOSSIP_SENDER_Q, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->SEND_GOSSIP_MENU(14010, pCreature->GetGUID());
			break;
		//Bank
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_N_B, GOSSIP_SENDER_BANK, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_S_B, GOSSIP_SENDER_BANK, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SE , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->SEND_GOSSIP_MENU(14007, pCreature->GetGUID());
			break;
		//Barber
		case GOSSIP_ACTION_INFO_DEF + 4: 
			pPlayer->SEND_POI(5892.12f, 618.577f, 7, 6, 0, "Barbier von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14003, pCreature->GetGUID());
			break;
		//Battlemasters
		case GOSSIP_ACTION_INFO_DEF + 5:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A_Q, GOSSIP_SENDER_Q, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_H_Q, GOSSIP_SENDER_Q, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->SEND_GOSSIP_MENU(13977, pCreature->GetGUID());
			break;
		//Portals
		case GOSSIP_ACTION_INFO_DEF + 6:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A_Q, GOSSIP_SENDER_Q, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_H_Q, GOSSIP_SENDER_Q, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->SEND_GOSSIP_MENU(13977, pCreature->GetGUID());
		break;
		//Flight Master
		case GOSSIP_ACTION_INFO_DEF + 7:
			pPlayer->SEND_POI(5813.37f, 453.403f, 7, 6, 0, "Der Flugmeister von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14004, pCreature->GetGUID());
		break;
		//Guild Master
		case GOSSIP_ACTION_INFO_DEF + 8:
			pPlayer->SEND_POI(5767.96f, 627.193f, 7, 6, 0, "Das Besucherzentrum von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14015, pCreature->GetGUID());
			break;
		//Inn
		case GOSSIP_ACTION_INFO_DEF + 9:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A_I, GOSSIP_SENDER_I   , GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_H_I, GOSSIP_SENDER_I	  , GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SE , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->SEND_POI(5859.86f, 634.46f, 7, 6, 0, "Gasthaus von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14002, pCreature->GetGUID());
			break;
		//Locksmith
		case GOSSIP_ACTION_INFO_DEF + 10:
			pPlayer->SEND_POI(5934.13f, 575.821f, 7, 6, 0, "Der Schlosser von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14251, pCreature->GetGUID());
			break;
		//Mailbox
		case GOSSIP_ACTION_INFO_DEF + 11:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_INN , GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_BANK, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_K_L , GOSSIP_SENDER_MAIL, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->SEND_GOSSIP_MENU(14008, pCreature->GetGUID());
			break;
	   //Points of Inetrest
		case GOSSIP_ACTION_INFO_DEF + 12:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A_Q	, GOSSIP_SENDER_Q	, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_H_Q	, GOSSIP_SENDER_Q	, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_V_C	, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_V_H	, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_SE	, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_T	, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_K_L	, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 4);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A_M	, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 5);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_R_S	, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 6);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_T_E	, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 7);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_C	, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 8);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_L_o_P, GOSSIP_SENDER_POI , GOSSIP_ACTION_INFO_DEF + 9);
			pPlayer->SEND_GOSSIP_MENU(13975, pCreature->GetGUID());
			break;
		//Stable Master
		case GOSSIP_ACTION_INFO_DEF + 13: pPlayer->SEND_POI(5859.68f, 557.571f, 7, 6, 0, "Der Stallmeister von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14001, pCreature->GetGUID());
			break;
		//Trainer
		case GOSSIP_ACTION_INFO_DEF + 14:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_C_T	  , GOSSIP_SENDER_TRAINERS, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_C_W_F_T, GOSSIP_SENDER_TRAINERS, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Po_T	  , GOSSIP_SENDER_TRAINERS, GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Pr_T	  , GOSSIP_SENDER_TRAINERS, GOSSIP_ACTION_INFO_DEF + 4);
			pPlayer->SEND_GOSSIP_MENU(14000, pCreature->GetGUID());
			break;
		//Vendors
		case GOSSIP_ACTION_INFO_DEF + 15:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Cl		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_E_G		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_F		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 4);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Fr		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 5);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_G_G		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 6);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_J		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 7);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_P_S_A_E_M, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 8);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_P_P_A_C	, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 9);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_R_A_M_G	, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 10);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_T_GER	, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 11);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_T_S		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 12);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_T_R_A_O_I, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 13);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_W		, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 14);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_W_A_C	, GOSSIP_SENDER_VENDORS, GOSSIP_ACTION_INFO_DEF + 15);
			pPlayer->SEND_GOSSIP_MENU(14117, pCreature->GetGUID());
			break;
	}

}

void SendArenaMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action)
	{
		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->SEND_POI(5805.33f, 556.04f, 7, 6, 0, "Östlicher Eingang zur Kanalisation");
			pPlayer->SEND_GOSSIP_MENU(13961, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5816.37f, 758.51f, 7, 6, 0, "Westlicher Eingang zur Kanalisation");
			pPlayer->SEND_GOSSIP_MENU(13960, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->SEND_POI(5885.96f, 647.26f, 7, 6, 0, "Brunnen von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13969, pCreature->GetGUID());
			break;
	}

}
void SendQuarterMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action){

		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->SEND_POI(5762.29f, 712.98f, 7, 6, 0, "Die Silberne Enklave");
			pPlayer->SEND_GOSSIP_MENU(13973, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5857.64f, 593.74f, 7, 6, 0, "Sonnenhäschers Zuflucht");
			pPlayer->SEND_GOSSIP_MENU(13973, pCreature->GetGUID());
			break;
	}
}

void SendBankMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action){

		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->SEND_POI(5926.78f, 646.52f, 7, 6, 0, "Die Südliche Bank von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14005, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5679.18f, 666.92f, 7, 6, 0, "Die Nördliche Bank von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14006, pCreature->GetGUID());
			break;
	}

}
void SendInnMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action)
	{
	case GOSSIP_ACTION_INFO_DEF + 1:
		pPlayer->SEND_POI(5735.24f, 676.15f, 7, 6, 0, "Das Allianzgasthaus von Dalaran");
		pPlayer->SEND_GOSSIP_MENU(13992, pCreature->GetGUID());
		break;
	case GOSSIP_ACTION_INFO_DEF + 2:
		pPlayer->SEND_POI(5885.10f, 527.30f, 7, 6, 0, "Das Hordengasthaus von Dalaran");
		pPlayer->SEND_GOSSIP_MENU(13993, pCreature->GetGUID());
		break;
	}

}
void SendMailMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action)
	{
	case GOSSIP_ACTION_INFO_DEF + 1:
		pPlayer->SEND_POI(5831.95f, 507.86f, 7, 6, 0, GOSSIP_TEXT_K_L);
		pPlayer->SEND_GOSSIP_MENU(14009, pCreature->GetGUID());
		break;
	}
}
void SendPoiMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action)
	{
		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->SEND_POI(5790.33f, 737.05f, 7, 6, 0, "Die Violette Zitadelle");
			pPlayer->SEND_GOSSIP_MENU(13971, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5692.27f, 500.17f, 7, 6, 0, "Die Violette Festung");
			pPlayer->SEND_GOSSIP_MENU(13970, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->SEND_POI(5897.56f, 733.24f, 7, 6, 0, "Handelsdistrikt");
			pPlayer->SEND_GOSSIP_MENU(13980, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 4:
			pPlayer->SEND_POI(5831.99f, 657.70f, 7, 6, 0, "Krasus' Landeplatz");
			pPlayer->SEND_GOSSIP_MENU(14009, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 5:
			pPlayer->SEND_POI(5949.71f, 669.26f, 7, 6, 0, "Antonidas' Denkmal");
			pPlayer->SEND_GOSSIP_MENU(13968, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 6:
			pPlayer->SEND_POI(5805.78f, 647.68f, 7, 6, 0, "Runenweberplatz");
			pPlayer->SEND_GOSSIP_MENU(13967, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 7:
			pPlayer->SEND_POI(5713.84f, 646.22f, 7, 6, 0, "Die Abendruh");
			pPlayer->SEND_GOSSIP_MENU(13966, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 8:
			pPlayer->SEND_POI(5856.75f, 697.99f, 7, 6, 0, "Der Friedhof von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13965, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 9:
			pPlayer->SEND_POI(5848.27f, 766.34f, 7, 6, 0, "Lexikon der Macht");
			pPlayer->SEND_GOSSIP_MENU(14174, pCreature->GetGUID());
			break;
	}
}
void SendTrainersMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action)
	{
		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->SEND_POI(5807.69f, 586.88f, 7, 6, 0, "Der Magierlehrer von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13999, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5815.27f, 473.49f, 7, 6, 0, "Krasus' Landeplatz");
			pPlayer->SEND_GOSSIP_MENU(13998, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->SEND_POI(5807.69f, 586.88f, 7, 6, 0, "Der Portallehrer von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13999, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 4:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Al  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Bl  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Co  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_En  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 4);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Eng , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 5);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_F_A , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 6);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Fi  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 7);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_He  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 8);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_In  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 9);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Jew , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 10);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Le  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 11);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Min , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 12);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Skin, GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 13);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Ta  , GOSSIP_SENDER_PROFTRAINER, GOSSIP_ACTION_INFO_DEF + 14);
			pPlayer->SEND_GOSSIP_MENU(13996, pCreature->GetGUID());
	}

}
void SendVendorsMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{

	switch(action)
	{
		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_C_A, GOSSIP_SENDER_ARMOR, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_L_A, GOSSIP_SENDER_ARMOR, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_M_A, GOSSIP_SENDER_ARMOR, GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_P_A, GOSSIP_SENDER_ARMOR, GOSSIP_ACTION_INFO_DEF + 4);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_S  , GOSSIP_SENDER_ARMOR, GOSSIP_ACTION_INFO_DEF + 5);
			pPlayer->SEND_GOSSIP_MENU(14114, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5786.20f, 647.08f, 7, 6, 0, "Stoffrüstung & Kleidung in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14112, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A_Q, GOSSIP_SENDER_Q, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_H_Q, GOSSIP_SENDER_Q, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->SEND_GOSSIP_MENU(14108, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 4:
			pPlayer->SEND_POI(5773.01f, 577.11f, 7, 6, 0, "Blumen in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14107, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 5:
			pPlayer->SEND_POI(5753.19f, 694.93f, 7, 6, 0, "Obstverkäufer in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14106, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 6:
			pPlayer->SEND_POI(5688.13f, 648.05f, 7, 6, 0, "Gemischt- & Handwerkswaren in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14105, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 7:
			pPlayer->SEND_POI(5871.58f, 725.30f, 7, 6, 0, "Juwelenschleifen von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13984, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 8:
			pPlayer->SEND_POI(5833.19f, 571.80f, 7, 6, 0, "Tierbedarf in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14103, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 9:
			pPlayer->SEND_POI(5906.07f, 627.51f, 7, 6, 0, "Kuchen, Gebäck und Torten in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14102, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 10:
			pPlayer->SEND_POI(5767.48f, 732.60f, 7, 6, 0, "Reagenzien in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14104, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 11:
			pPlayer->SEND_POI(5819.48f, 696.89f, 7, 6, 0, "Spielzeug in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14100, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 12:
			pPlayer->SEND_POI(5690.12f, 621.70f, 7, 6, 0, "Gemischt- & Handwerkswaren in Dalaran");
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_Pr_T, GOSSIP_SENDER_TRAINERS, GOSSIP_ACTION_INFO_DEF + 4);
			pPlayer->SEND_GOSSIP_MENU(14101, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 13:
			pPlayer->SEND_POI(5762.18f, 638.81f, 7, 6, 0, "Schmuckstücke in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14110, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 14:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_M_W	  , GOSSIP_SENDER_WEAPONS, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_R_A_T_W, GOSSIP_SENDER_WEAPONS, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_S_A_W  , GOSSIP_SENDER_WEAPONS, GOSSIP_ACTION_INFO_DEF + 3);
			pPlayer->SEND_GOSSIP_MENU(14113, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 15:
			pPlayer->SEND_POI(5879.49f, 612.42f, 7, 6, 0, "Wein & Käse in Dalaran");
			pPlayer->SEND_GOSSIP_MENU(14095, pCreature->GetGUID());
			break;
	}
}
void SendArmorMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action)
	{
		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->SEND_POI(5786.20f, 647.08f, 7, 6, 0, "Stoffrüstung & Kleidung");
			pPlayer->SEND_GOSSIP_MENU(14112, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5675.09f, 630.65f, 7, 6, 0, "Leder & Schwere Rüstung");
			pPlayer->SEND_GOSSIP_MENU(14111, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->SEND_POI(5675.09f, 630.65f, 7, 6, 0, "Plattenrüstung & Schilde");
			pPlayer->SEND_GOSSIP_MENU(14109, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 4:
			pPlayer->SEND_POI(5675.09f, 630.65f, 7, 6, 0, "Plattenrüstung & Schilde");
			pPlayer->SEND_GOSSIP_MENU(14109, pCreature->GetGUID());
			break;
	}

}
void SendWeaponsMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action)
	{
		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->SEND_POI(5731.85f, 608.23f, 7, 6, 0, "Nahkampfwaffen");
			pPlayer->SEND_GOSSIP_MENU(14098, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5783.44f, 561.81f, 7, 6, 0, "Fernkampfwaffen");
			pPlayer->SEND_GOSSIP_MENU(14097, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->SEND_POI(5674.73f, 647.00f, 7, 6, 0, "Stäbe & Zauberstäbe");
			pPlayer->SEND_GOSSIP_MENU(14096, pCreature->GetGUID());
			break;
	}

}
void SendProfTrainerMenu_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 action)
{
	switch(action)
	{
		case GOSSIP_ACTION_INFO_DEF + 1:
			pPlayer->SEND_POI(5895.75f, 711.08f, 7, 6, 0, "Alchemielehrer von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13995, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 2:
			pPlayer->SEND_POI(5900.17f, 686.36f, 7, 6, 0, "Schmiedekunst von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13994, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 3:
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_A_I, GOSSIP_SENDER_I, GOSSIP_ACTION_INFO_DEF + 1);
			pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TEXT_H_I, GOSSIP_SENDER_I, GOSSIP_ACTION_INFO_DEF + 2);
			pPlayer->SEND_GOSSIP_MENU(13991, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 4:
			pPlayer->SEND_POI(5835.09f, 719.40f, 7, 6, 0, "Verzauberkunst von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13990, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 5:
			pPlayer->SEND_POI(5914.88f, 728.24f, 7, 6, 0, "Ingenieurskunst von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13989, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 6:
			pPlayer->SEND_POI(5864.82f, 737.73f, 7, 6, 0, "Erste Hilfe von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13988, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 7:
			pPlayer->SEND_POI(5703.40f, 615.44f, 7, 6, 0, "Angellehrer von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13987, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 8:
			pPlayer->SEND_POI(5872.11f, 687.78f, 7, 6, 0, "Kräuterkunde von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13986, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 9:
			pPlayer->SEND_POI(5859.55f, 700.48f, 7, 6, 0, "Inschriftenkunde von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13985, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 10:
			pPlayer->SEND_POI(5872.69f, 724.94f, 7, 6, 0, "Juwelenschleifen von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13984, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 11:
			pPlayer->SEND_POI(5902.58f, 746.44f, 7, 6, 0, "Lederverarbeitung von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13982, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 12:
			pPlayer->SEND_POI(5914.93f, 710.01f, 7, 6, 0, "Bergbau von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13983, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 13:
			pPlayer->SEND_POI(5902.58f, 746.44f, 7, 6, 0, "Kürschnerei von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13982, pCreature->GetGUID());
			break;
		case GOSSIP_ACTION_INFO_DEF + 14:
			pPlayer->SEND_POI(5883.58f, 741.38f, 7, 6, 0, "Schneiderei von Dalaran");
			pPlayer->SEND_GOSSIP_MENU(13981, pCreature->GetGUID());
			break;
	}
}

bool GossipSelect_guard_dalaran(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
    switch (sender)
    {
        case GOSSIP_SENDER_MAIN:            SendDefaultMenu_guard_dalaran(pPlayer, pCreature, action); break;
		case GOSSIP_SENDER_ARENA:           SendArenaMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_Q:               SendQuarterMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_BANK:			SendBankMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_I:               SendInnMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_MAIL:            SendMailMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_POI:             SendPoiMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_TRAINERS:        SendTrainersMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_VENDORS:         SendVendorsMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_ARMOR:           SendArmorMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_WEAPONS:         SendWeaponsMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
		case GOSSIP_SENDER_PROFTRAINER:     SendProfTrainerMenu_guard_dalaran(pPlayer,  pCreature,  action); break;
    }
    return true;
}

/*******************************************************
 * guard_dalaran end
 *******************************************************/


/*******************************************************
 * guard_contested start
 *******************************************************/
enum eguard_contested
{
	PVP_GUARD_SAY1 = -1000198,
	PVP_GUARD_SAY2 = -1000199,
	PVP_GUARD_SAY3 = -1000200
 
};

struct MANGOS_DLL_DECL guard_contested : public guardAI
{
    guard_contested(Creature* pCreature) : guardAI(pCreature) {Reset();}
	

	void Reset()
    {
		m_creature->AttackStop();
		m_creature->DeleteThreatList();
		m_creature->setFaction(121);
	}

    void MoveInLineOfSight(Unit* pUnit)
    {
        if ( pUnit->isInCombat() && pUnit->isAttackingPlayer())
        {
            if(pUnit->GetTypeId() == TYPEID_PLAYER)
            {
				const ObjectGuid objGuid = pUnit->GetOwnerGuid();
				if(!objGuid.IsEmpty())
				{

					Unit* pVictim = pUnit->getVictim();
					if(pVictim->GetTypeId() == TYPEID_PLAYER)
					{
						m_creature->AddThreat(pUnit, 0.0f);
						if(Unit* owner = pUnit->GetOwner())
							m_creature->AddThreat(owner, 0.0f);
			    		m_creature->Attack(pUnit,true);
			    		m_creature->setFaction(72);

						DoStartMovement(pUnit);
						SpellEntry const *spell = m_creature->ReachWithSpellAttack(pUnit);
						DoCastSpell(pUnit, spell);
							

						if(!m_creature->isInCombat())
						{
							if (m_creature->GetEntry() == 15184)    //Cenarion Hold Infantry
							{
								srand (time(NULL));
								if (rand()%100 <= 30)
								{
									DoScriptText(PVP_GUARD_SAY1,m_creature);
									//DoSay("Taste blade, mongrel!", LANG_UNIVERSAL,NULL);
								}
								else if (rand()%100 > 30 && rand()%100 < 50)
								{
									DoScriptText(PVP_GUARD_SAY2,m_creature);
									//DoSay("Please tell me that you didn`t just do what I think you just did. Please tell me that I`m not going to have to hurt you...", LANG_UNIVERSAL,NULL);
								}
								else if (rand()%100 >= 50)
								{
									DoScriptText(PVP_GUARD_SAY3,m_creature);
									//DoSay("As if we don`t have enough problems, you go and create more!", LANG_UNIVERSAL,NULL);
								}
							}
						}
					}
	                
				}
			}
			m_creature->AttackStop();
			m_creature->DeleteThreatList();
			m_creature->setFaction(121);
        }
    }
};

 /*******************************************************
  * guard_contested end
  *******************************************************/

CreatureAI* GetAI_guard_shattrath_scryer(Creature* pCreature)
{
    return new guard_shattrath_scryerAI(pCreature);
}

CreatureAI* GetAI_guard_silvermoon(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_stormwind(Creature* pCreature)
{
    return new guardAI_stormwind(pCreature);
}

CreatureAI* GetAI_guard_teldrassil(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_tirisfal(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_undercity(Creature* pCreature)
{
    return new guardAI(pCreature);
}

CreatureAI* GetAI_guard_dalaran(Creature* pCreature)
{
    return new guardAI(pCreature);
}

void AddSC_guards()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "guard_azuremyst";
    newscript->GetAI = &GetAI_guard_azuremyst;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_bluffwatcher";
    newscript->GetAI = &GetAI_guard_bluffwatcher;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_contested";
    newscript->GetAI = &GetAI_guard_contested;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_darnassus";
    newscript->GetAI = &GetAI_guard_darnassus;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_dunmorogh";
    newscript->GetAI = &GetAI_guard_dunmorogh;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_durotar";
    newscript->GetAI = &GetAI_guard_durotar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_elwynnforest";
    newscript->GetAI = &GetAI_guard_elwynnforest;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_eversong";
    newscript->GetAI = &GetAI_guard_eversong;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_exodar";
    newscript->GetAI = &GetAI_guard_exodar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_ironforge";
    newscript->GetAI = &GetAI_guard_ironforge;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_mulgore";
    newscript->GetAI = &GetAI_guard_mulgore;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_orgrimmar";
    newscript->GetAI = &GetAI_guard_orgrimmar;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_shattrath";
    newscript->GetAI = &GetAI_guard_shattrath;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_shattrath_aldor";
    newscript->GetAI = &GetAI_guard_shattrath_aldor;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_shattrath_scryer";
    newscript->GetAI = &GetAI_guard_shattrath_scryer;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_silvermoon";
    newscript->GetAI = &GetAI_guard_silvermoon;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_stormwind";
    newscript->GetAI = &GetAI_guard_stormwind;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_teldrassil";
    newscript->GetAI = &GetAI_guard_teldrassil;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_tirisfal";
    newscript->GetAI = &GetAI_guard_tirisfal;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_undercity";
    newscript->GetAI = &GetAI_guard_undercity;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "guard_dalaran";
    newscript->pGossipHello          = &GossipHello_guard_dalaran;
    newscript->pGossipSelect         = &GossipSelect_guard_dalaran;
    newscript->GetAI = &GetAI_guard_undercity;
    newscript->RegisterSelf();
}
