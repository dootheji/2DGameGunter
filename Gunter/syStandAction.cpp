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
		syPoint m_posinfo = m_pOwner->m_current->m_info.InitPos;
		m_pOwner->GetMario(SY_FORWORD);
		m_pOwner->m_current->SetPos(m_posinfo);

	}
	else
	{
		syPoint m_posinfo = m_pOwner->m_current->m_info.InitPos;
		m_pOwner->GetMario(SY_FORWORD);
		m_pOwner->m_current->SetPos(m_posinfo);

	}
	if (syCollision::RectInRect(m_pOwner->m_current->m_rtColl, pTarget->m_rtColl))
	{
		m_pOwner->SetTransition(SYSTATE_DEAD);
		return;
	}
	if (m_pOwner->isStand)
	{
		m_pOwner->SetTransition(SYSTATE_TILECOLL);
	}
}