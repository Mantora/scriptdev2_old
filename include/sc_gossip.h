/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef SC_GOSSIP_H
#define SC_GOSSIP_H

#include "Player.h"
#include "GossipDef.h"
#include "QuestDef.h"

// Gossip Item Text
#define GOSSIP_TEXT_BROWSE_GOODS        "Me gustar�a echar un vistazo a tus suministros."
#define GOSSIP_TEXT_TRAIN               "�Ense�ame!"

#define GOSSIP_TEXT_BANK                "El Banco"
#define GOSSIP_TEXT_IRONFORGE_BANK      "El Banco de Forjaz"
#define GOSSIP_TEXT_STORMWIND_BANK      "El Banco de Ventormenta"
#define GOSSIP_TEXT_WINDRIDER           "El Maestro Jinete de Viento"
#define GOSSIP_TEXT_GRYPHON             "El Maestro de Grifos"
#define GOSSIP_TEXT_BATHANDLER          "El Cuidador de Murci�lagos"
#define GOSSIP_TEXT_HIPPOGRYPH          "El Maestro de Hipogrifos"
#define GOSSIP_TEXT_ZEPPLINMASTER       "El Maestro de Zeppelin"
#define GOSSIP_TEXT_DEEPRUNTRAM         "El Tranv�a Deeprun"
#define GOSSIP_TEXT_FERRY               "El Ferry de Rut'theran"
#define GOSSIP_TEXT_FLIGHTMASTER        "El Maestro de Vuelo"
#define GOSSIP_TEXT_AUCTIONHOUSE        "La Casa de Subastas"
#define GOSSIP_TEXT_GUILDMASTER         "El Maestro de Hermandad"
#define GOSSIP_TEXT_INN                 "La Posada"
#define GOSSIP_TEXT_MAILBOX             "El Correo"
#define GOSSIP_TEXT_STABLEMASTER        "El Maestro de Establos"
#define GOSSIP_TEXT_WEAPONMASTER        "El Maestro de Armas"
#define GOSSIP_TEXT_OFFICERS            "Sala de los Oficiales"
#define GOSSIP_TEXT_BATTLEMASTER        "El Maestro de Batallas"
#define GOSSIP_TEXT_BARBER              "Barbero"
#define GOSSIP_TEXT_CLASSTRAINER        "Instructores de Clases"
#define GOSSIP_TEXT_PROFTRAINER         "Instructores de Profesiones"
#define GOSSIP_TEXT_LEXICON             "Lexicon de Poder"

#define GOSSIP_TEXT_ALTERACVALLEY       "Valle de Alterac"
#define GOSSIP_TEXT_ARATHIBASIN         "Cuenca de Arathi"
#define GOSSIP_TEXT_WARSONGULCH         "Garganta Grito de Guerra"
#define GOSSIP_TEXT_ARENA               "Arena"
#define GOSSIP_TEXT_EYEOFTHESTORM       "Ojo de Tormenta"
#define GOSSIP_TEXT_STRANDOFANCIENT      "Playa de los Ancestros"

#define GOSSIP_TEXT_DEATH_KNIGHT        "Caballero de la Muerte"
#define GOSSIP_TEXT_DRUID               "Druida"
#define GOSSIP_TEXT_HUNTER              "Cazador"
#define GOSSIP_TEXT_PRIEST              "Sacerdote"
#define GOSSIP_TEXT_ROGUE               "Picaro"
#define GOSSIP_TEXT_WARRIOR             "Guerrero"
#define GOSSIP_TEXT_PALADIN             "Paladin"
#define GOSSIP_TEXT_SHAMAN              "Chaman"
#define GOSSIP_TEXT_MAGE                "Mago"
#define GOSSIP_TEXT_WARLOCK             "Brujo"

#define GOSSIP_TEXT_ALCHEMY             "Alquimia"
#define GOSSIP_TEXT_BLACKSMITHING       "Herreria"
#define GOSSIP_TEXT_COOKING             "Cocina"
#define GOSSIP_TEXT_ENCHANTING          "Encantamiento"
#define GOSSIP_TEXT_ENGINEERING         "Ingenieria"
#define GOSSIP_TEXT_FIRSTAID            "Primeros Auxilios"
#define GOSSIP_TEXT_HERBALISM           "Botanica"
#define GOSSIP_TEXT_LEATHERWORKING      "Peleteria"
#define GOSSIP_TEXT_TAILORING           "Sastreria"
#define GOSSIP_TEXT_MINING              "Mineria"
#define GOSSIP_TEXT_FISHING             "Pesca"
#define GOSSIP_TEXT_SKINNING            "Desollado"
#define GOSSIP_TEXT_JEWELCRAFTING       "Joyeria"
#define GOSSIP_TEXT_INSCRIPTION         "Inscripci�n"

enum
{
    // Skill defines
    TRADESKILL_ALCHEMY             = 1,
    TRADESKILL_BLACKSMITHING       = 2,
    TRADESKILL_COOKING             = 3,
    TRADESKILL_ENCHANTING          = 4,
    TRADESKILL_ENGINEERING         = 5,
    TRADESKILL_FIRSTAID            = 6,
    TRADESKILL_HERBALISM           = 7,
    TRADESKILL_LEATHERWORKING      = 8,
    TRADESKILL_POISONS             = 9,
    TRADESKILL_TAILORING           = 10,
    TRADESKILL_MINING              = 11,
    TRADESKILL_FISHING             = 12,
    TRADESKILL_SKINNING            = 13,
    TRADESKILL_JEWLCRAFTING        = 14,
    TRADESKILL_INSCRIPTION         = 15,

    TRADESKILL_LEVEL_NONE          = 0,
    TRADESKILL_LEVEL_APPRENTICE    = 1,
    TRADESKILL_LEVEL_JOURNEYMAN    = 2,
    TRADESKILL_LEVEL_EXPERT        = 3,
    TRADESKILL_LEVEL_ARTISAN       = 4,
    TRADESKILL_LEVEL_MASTER        = 5,
    TRADESKILL_LEVEL_GRAND_MASTER  = 6,

    // Gossip defines
    GOSSIP_ACTION_TRADE            = 1,
    GOSSIP_ACTION_TRAIN            = 2,
    GOSSIP_ACTION_TAXI             = 3,
    GOSSIP_ACTION_GUILD            = 4,
    GOSSIP_ACTION_BATTLE           = 5,
    GOSSIP_ACTION_BANK             = 6,
    GOSSIP_ACTION_INN              = 7,
    GOSSIP_ACTION_HEAL             = 8,
    GOSSIP_ACTION_TABARD           = 9,
    GOSSIP_ACTION_AUCTION          = 10,
    GOSSIP_ACTION_INN_INFO         = 11,
    GOSSIP_ACTION_UNLEARN          = 12,
    GOSSIP_ACTION_INFO_DEF         = 1000,

    GOSSIP_SENDER_MAIN             = 1,
    GOSSIP_SENDER_INN_INFO         = 2,
    GOSSIP_SENDER_INFO             = 3,
    GOSSIP_SENDER_SEC_PROFTRAIN    = 4,
    GOSSIP_SENDER_SEC_CLASSTRAIN   = 5,
    GOSSIP_SENDER_SEC_BATTLEINFO   = 6,
    GOSSIP_SENDER_SEC_BANK         = 7,
    GOSSIP_SENDER_SEC_INN          = 8,
    GOSSIP_SENDER_SEC_MAILBOX      = 9,
    GOSSIP_SENDER_SEC_STABLEMASTER = 10
};

extern uint32 GetSkillLevel(Player* pPlayer,uint32 skill);

// Defined fuctions to use with player.

// This fuction add's a menu item,
// a - Icon Id
// b - Text
// c - Sender(this is to identify the current Menu with this item)
// d - Action (identifys this Menu Item)
// e - Text to be displayed in pop up box
// f - Money value in pop up box
#define ADD_GOSSIP_ITEM(a, b, c, d)   PlayerTalkClass->GetGossipMenu().AddMenuItem(a, b, c, d, "", 0)
#define ADD_GOSSIP_ITEM_EXTENDED(a, b, c, d, e, f, g)   PlayerTalkClass->GetGossipMenu().AddMenuItem(a, b, c, d, e, f, g)

// This fuction Sends the current menu to show to client, a - NPCTEXTID(uint32) , b - npc guid(uint64)
#define SEND_GOSSIP_MENU(a, b)      PlayerTalkClass->SendGossipMenu(a, b)

// This fuction shows POI(point of interest) to client.
// a - position X
// b - position Y
// c - Icon Id
// d - Flags
// e - Data
// f - Location Name
#define SEND_POI(a, b, c, d, e, f)      PlayerTalkClass->SendPointOfInterest(a, b, c, d, e, f)

// Closes the Menu
#define CLOSE_GOSSIP_MENU()        PlayerTalkClass->CloseGossip()

// Fuction to tell to client the details
// a - quest object
// b - npc guid(uint64)
// c - Activate accept(bool)
#define SEND_QUEST_DETAILS(a, b, c)  PlayerTalkClass->SendQuestDetails(a, b, c)

// Fuction to tell to client the requested items to complete quest
// a - quest object
// b - npc guid(uint64)
// c - Iscompletable(bool)
// d - close at cancel(bool) - in case single incomplite ques
#define SEND_REQUESTEDITEMS(a, b, c, d) PlayerTalkClass->SendRequestedItems(a, b, c, d)

// Fuctions to send NPC lists, a - is always the npc guid(uint64)
#define SEND_VENDORLIST(a)         GetSession()->SendListInventory(a)
#define SEND_TRAINERLIST(a)        GetSession()->SendTrainerList(a)
#define SEND_BANKERLIST(a)         GetSession()->SendShowBank(a)
#define SEND_TABARDLIST(a)         GetSession()->SendTabardVendorActivate(a)
#define SEND_TAXILIST(a)           GetSession()->SendTaxiStatus(a)

// Function to send the Auction List, a - npc guid(uint64), b - pointer to npc(Creature*)
#define SEND_AUCTIONLIST(a, b)     GetSession()->SendAuctionHello(a, b)

// Ressurect's the player if is dead.
#define SEND_SPRESURRECT()         GetSession()->SendSpiritResurrect()

// Get the player's honor rank.
#define GET_HONORRANK()            GetHonorRank()
// -----------------------------------

// defined fuctions to use with Creature

#define QUEST_DIALOG_STATUS(a, b, c)   GetSession()->getDialogStatus(a, b, c)
#endif
