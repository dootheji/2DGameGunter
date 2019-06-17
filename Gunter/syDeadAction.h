#pragma once
#include "syEnemyState.h"
class syDeadAction : public syEnemyState
{
public:
	syDeadAction(syEnemy* pParent);
	virtual ~syDeadAction();
public:
	void Process(sySprite* pTarget);
};