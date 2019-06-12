#include "syStandAction.h"
#include "syEnemy.h"

syStandAction::syStandAction(syEnemy* pParent) : syEnemyState(pParent)
{

}


syStandAction::~syStandAction()
{
}

void syStandAction::Process(sySprite* pTarget)
{
	this->m_pOwner->SetPos(this->m_pOwner->getPos().x + 1, this->m_pOwner->getPos().y +1 );
}