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
	float x = m_pOwner->getPos().x + g_fSecondPerFrame;
	float y = m_pOwner->getPos().y + g_fSecondPerFrame;



	if (g_ActionInput.bWKey == KEY_HOLD)
	{
		//m_pOwner->m_info.
	}
	m_pOwner->SetPos(x, y);
}