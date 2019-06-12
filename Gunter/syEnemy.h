#pragma once
#include "syEnemyState.h"
#include "syFSM.h"
#include "sySprite.h"
#include "syCollision.h"
class syEnemy : public sySprite
{
public:
	syEnemy();
	virtual ~syEnemy();
public:
	syEnemyState*  m_pAction;
	syEnemyState*  m_pActionList[3];
	DWORD		  m_dwCurrentState;
public:
	bool Init();
	bool Frame();
	void ProcessAI(sySprite* pTarget);
public:
	void SetTransition(DWORD dwEvent);
};

