#include "syMoveAction.h"
#include "syEnemy.h"


syMoveAction::syMoveAction(syEnemy* pParent) : syEnemyState(pParent)
{
}


syMoveAction::~syMoveAction()
{
}

void syMoveAction::Process(sySprite* pTarget)
{

}