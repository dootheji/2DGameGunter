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
	if (m_pOwner->isFront)
	{
	//	m_pOwner = m_pOwner->GetMario(0);
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