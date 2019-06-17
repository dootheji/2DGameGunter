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
	if (m_pOwner->isFront)
	{
		m_pOwner->GetMario(0);
	}
	else 
	{
		m_pOwner->GetMario(1);
	
	}
	

	if (syCollision::RectInRect(m_pOwner->m_rtColl, pTarget->m_rtColl))
	{
		m_pOwner->SetTransition(STATE_DEAD);
		return;
	}
}