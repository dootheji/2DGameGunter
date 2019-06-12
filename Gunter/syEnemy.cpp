#include "syEnemy.h"
#include "syInput.h"
#include "syStandAction.h"
#include "syMoveAction.h"
#include "syAttackAction.h"

syEnemy::syEnemy()
{
}


syEnemy::~syEnemy()
{
}


bool syEnemy::Init()
{
	m_pActionList[0] = new syStandAction(this);
	m_pActionList[1] = new syMoveAction(this);
	m_pActionList[2] = new syAttackAction(this);
	m_pAction = m_pActionList[0];
	m_dwCurrentState = STATE_STAND;
	return true;
}
void syEnemy::ProcessAI(sySprite* pTarget)
{
	m_pAction->Process(pTarget);
}
void syEnemy::SetTransition(DWORD dwEvent)
{
	// input -> event -> output
	syFiniteState* pState = I_Fsm.GetPtr(m_dwCurrentState);
	if (pState == nullptr) return;

	DWORD dwAction = pState->GetPtr(dwEvent);
	m_pAction = m_pActionList[dwAction];
	m_dwCurrentState = dwAction;
}
bool syEnemy::Frame()
{
	sySprite::Frame();
	return true;
}
