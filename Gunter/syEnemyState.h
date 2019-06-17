#pragma once
#include "sySprite.h"
#include "syFiniteState.h"
class syEnemy;
class syEnemyState
{
protected:
	shared_ptr<syEnemy>	m_pOwner;
	
public:
	int			iscriptnum = 0;
	virtual void Process(sySprite* pTarget) = 0;
public:
	syEnemyState(syEnemy* pParent) : m_pOwner(pParent) {}
	virtual ~syEnemyState();
};

