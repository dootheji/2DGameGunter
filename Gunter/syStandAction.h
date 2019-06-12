#pragma once
#include "syEnemyState.h"
class syStandAction : public syEnemyState
{
public:
	syStandAction(syEnemy* pParent);
	virtual ~syStandAction();
public:
	void Process(sySprite* pTarget);
};

