#ifndef GAME_SERVER_AI_H
#define GAME_SERVER_AI_H

#include <base/vmath.h>


#include "ai_protocol.h"

#define RAD 0.017453292519943295769236907684886f


class CAI
{
	class CGameContext *m_pGameServer;
	class CPlayer *m_pPlayer;
	
	int m_UnstuckCount;
	
protected:
	
	CGameContext *GameServer() const { return m_pGameServer; }
	CPlayer *Player() const { return m_pPlayer; }
	
	virtual void DoBehavior() = 0;
	
	vec2 m_Pos;
	vec2 m_LastPos;
	int m_LastMove;
	int m_LastJump;
	
	vec2 m_Direction;
	int m_Move;
	int m_Jump;
	int m_Attack;
	int m_LastAttack;
	
	int m_Hook;
	int m_LastHook;
	
	int m_NextReaction;
	int m_ReactionTime;
	
	int m_Sleep;
	int m_Stun;
	
	// last spotted the enemy here
	vec2 m_PlayerPos;
	vec2 m_PlayerDirection;
	int m_PlayerDistance;
	int m_PlayerSpotTimer;
	int m_PlayerSpotCount;
	
	vec2 m_TargetPos;
	vec2 m_WaypointPos;
	
	int m_TargetTimer;
	
	bool MoveTowardsPlayer(int Dist = 0);
	bool MoveTowardsTarget(int Dist = 0);
	bool MoveTowardsWaypoint(int Dist = 0);
	
	void Unstuck();
	void HeadToMovingDirection();
	void JumpIfPlayerIsAbove();
	
	void ShootAtClosestEnemy();
	int WeaponShootRange();
	
public:
	CAI(class CGameContext *pGameServer, class CPlayer *pPlayer);
	
	virtual ~CAI(){ }

	void Reset();
	void Tick();
	void UpdateInput(int *Data); // MAX_INPUT_SIZE
	
	void SeekBombArea();
	void SeekBomb();
	
	bool SeekClosestEnemy();
	bool SeekClosestEnemyInSight();
	void CheckAITiles();
	
	bool m_InputChanged;
	
	virtual void OnCharacterSpawn(class CCharacter *pChr);
	
	void Zzz(int Time);
	void Stun(int Time);
	
	void StandStill(int Time);
	
	virtual void ReceiveDamage();

	
	int GetMove(){ return m_Move; }
};



#endif