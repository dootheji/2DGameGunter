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
		syPoint m_posinfo = m_pOwner->m_current->m_info.InitPos;
		m_pOwner->GetMario(SY_FORWORD);
		m_pOwner->SetPos(m_posinfo);
	}
	else 
	{
		syPoint m_posinfo = m_pOwner->m_current->m_info.InitPos;
		m_pOwner->GetMario(SY_BACKWORD);
		m_pOwner->SetPos(m_posinfo);
	
	}
	

	if (syCollision::RectInRect(m_pOwner->m_current->m_rtColl, pTarget->m_rtColl))
	{
		m_pOwner->SetTransition(SYSTATE_DEAD);
		return;
	}
}