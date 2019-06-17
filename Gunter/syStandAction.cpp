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
	//float x = m_pOwner->getPos().x + g_fSecondPerFrame;
	//float y = m_pOwner->getPos().y + g_fSecondPerFrame;

	if (m_pOwner->isFront)
	{
		m_pOwner->GetMario(2);
	}
	else
	{
		m_pOwner->GetMario(3);

	}
	if (syCollision::RectInRect(m_pOwner->m_rtColl, pTarget->m_rtColl))
	{
		m_pOwner->SetTransition(STATE_DEAD);
		return;
	}
}