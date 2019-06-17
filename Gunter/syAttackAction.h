#pragma once
#include "syEnemyState.h"
class syAttackAction : public syEnemyState
{
public:
	syAttackAction(syEnemy* pParent);
	virtual ~syAttackAction();
public:
	void Process(sySprite* pTarget);
};
