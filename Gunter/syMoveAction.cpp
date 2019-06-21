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

	static float fTime = 0;
	fTime +=g_fSecondPerFrame;
	static float ran = rand() % 5;
	syPoint m_posinfo = m_pOwner->m_current->m_info.InitPos;
	float dxtem = m_pOwner->m_current.get()->delX;
	float dytem = m_pOwner->m_current.get()->delY;

	if (m_pOwner->isFront)
	{		
		if (m_pOwner->m_current != m_pOwner->m_mario[SY_FORWORD])
		{
			m_pOwner->GetMario(SY_FORWORD);
		}
		m_pOwner->m_current->SetPos(m_posinfo);
		m_pOwner->m_current->setDel(1, dytem);
	}
	else
	{
		if (m_pOwner->m_current != m_pOwner->m_mario[SY_BACKWORD])
		{

			m_pOwner->GetMario(SY_BACKWORD);
		}
		m_pOwner->m_current->SetPos(m_posinfo);
		m_pOwner->m_current->setDel(-1, dytem);
	}

	if (syCollision::RectInRect(m_pOwner->m_current->m_rtColl, pTarget->m_rtColl))
	{
		m_pOwner->SetTransition(SYSTATE_DEAD);
		return;
	}

	if (fTime > ran)
	{
		//float dxtem = m_pOwner->m_current.get()->delX;
		fTime = 0.0f;
		ran = rand() % 10;
		m_pOwner->m_current->setDel(0, 1);
		m_pOwner->isFront = rand() % 2;
	}
	
}