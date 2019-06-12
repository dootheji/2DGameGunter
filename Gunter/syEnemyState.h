#pragma once
#include "sySprite.h"
#include "syFiniteState.h"
class syEnemy;
class syEnemyState
{
protected:
	syEnemy*	m_pOwner;
public:
	virtual void Process(sySprite* pTarget) = 0;
public:
	syEnemyState(syEnemy* pParent) : m_pOwner(pParent) {}
	virtual ~syEnemyState();
};

