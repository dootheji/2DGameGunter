#include "syDeadAction.h"
#include "syEnemy.h"


syDeadAction::syDeadAction(syEnemy* pParent) : syEnemyState(pParent)
{
}


syDeadAction::~syDeadAction()
{
}
void syDeadAction::Process(sySprite* pTarget)
{
	
	static float fTime = 0;
	fTime += g_fSecondPerFrame;
	if (fTime > 1.0f)
	{
		fTime = 0.0f;
		if (m_pOwner->m_current == m_pOwner.get()->m_mario[4])
		{
			syPoint m_posinfo = m_pOwner->m_current->m_info.InitPos;
			m_pOwner->m_current->SetPos(m_posinfo);
			m_pOwner->m_current->m_bDead = true;
		}
	}

	if (m_pOwner->m_current == m_pOwner->m_mario[4])
	{
		syPoint m_posinfo = m_pOwner->m_current->m_info.InitPos;
		m_pOwner->m_current->SetPos(m_posinfo);
		return;
	}
	if (pTarget->m_rtColl.bottom +5< m_pOwner->m_current->m_rtColl.bottom && pTarget->m_bDead != true)
	{
		syPoint m_posinfo = m_pOwner->m_current->m_info.InitPos;
		m_pOwner->GetMario(4);
		m_pOwner->m_current->SetPos(m_posinfo);
		pTarget->delY = 1;
		pTarget->Frame();
		/*		current_mario.get()->m_bDead = true;*/
		return;

	}

		pTarget->m_bDead = true;

}