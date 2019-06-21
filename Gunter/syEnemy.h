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
	shared_ptr < syEnemy >				m_current;
	syEnemyState*  m_pAction;
	syEnemyState*  m_pActionList[4];
	DWORD		  m_dwCurrentState;
	bool		  isFront = rand()%2;
	bool		  isStand = false;
public:
	bool Init();
	bool Frame();
	bool Release();
	void ProcessAI(sySprite* pTarget);

public:
	void SetTransition(DWORD dwEvent);

	void GetMario(DWORD num)
	{
		//m_dwCurrentState = num;
		m_current =  m_mario.at(num);
		
	};
};


