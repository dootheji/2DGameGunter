#pragma once
#include "syEnemyState.h"
#include "syFSM.h"
#include "sySprite.h"
#include "syCollision.h"
#include "syScriptManager.h"
#include "syEnemy.h"
class syEnemy : public sySprite
{
public:
	syEnemy();
	virtual ~syEnemy();
public:
	std::vector<shared_ptr<syEnemy>>   m_mario;

	syEnemyState*  m_pAction;
	syEnemyState*  m_pActionList[4];
	DWORD		  m_dwCurrentState;
	bool		  isFront = true;
public:
	bool Init();
	bool Frame();
	bool Release();
	void ProcessAI(sySprite* pTarget);

public:
	void SetTransition(DWORD dwEvent);

	shared_ptr<syEnemy> GetMario(DWORD num)
	{
		//m_dwCurrentState = num;
		return m_mario.at(num);
		
	};
};


