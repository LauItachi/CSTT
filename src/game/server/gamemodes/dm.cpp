/* (c) Magnus Auvinen. See licence.txt in the root of the distribution for more information. */
/* If you are missing that file, acquire a complete release at teeworlds.com.                */

#include <engine/shared/config.h>

#include <game/mapitems.h>

#include <game/server/entities/character.h>
#include <game/server/player.h>
#include <game/server/gamecontext.h>

#include "dm.h"

#include <game/server/ai.h>
#include <game/server/ai/dm_ai.h>



CGameControllerDM::CGameControllerDM(class CGameContext *pGameServer)
: IGameController(pGameServer)
{
	m_pGameType = "DM++";
}

void CGameControllerDM::OnCharacterSpawn(CCharacter *pChr, bool RequestAI)
{
	IGameController::OnCharacterSpawn(pChr);
	
	// init AI
	if (RequestAI)
		pChr->GetPlayer()->m_pAI = new CAIdm(GameServer(), pChr->GetPlayer());

	GameServer()->ResetVotes();
}



void CGameControllerDM::Tick()
{
	IGameController::Tick();
	AutoBalance();
	GameServer()->UpdateAI();
}
