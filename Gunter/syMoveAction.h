#pragma once
#include "syEnemyState.h"
class syMoveAction : public syEnemyState
{
public:
	syMoveAction(syEnemy* pParent);
	virtual ~syMoveAction();
public:
	void Process(sySprite* pTarget);
};

