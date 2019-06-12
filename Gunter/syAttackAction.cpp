#include "syAttackAction.h"
#include "syEnemy.h"

syAttackAction::syAttackAction(syEnemy* pParent) : syEnemyState(pParent)
{

}


syAttackAction::~syAttackAction()
{
}

void syAttackAction::Process(sySprite* pTarget)
{ 

}