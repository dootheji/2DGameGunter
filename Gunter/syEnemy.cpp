//enum tState { STATE_STAND, STATE_MOVE, STATE_ATTACK, STATE_COUNT };
//enum tEvent { EVENT_TIMER, EVENY_DEAD, EVENT_FINDTARGET, EVENT_LOSTTARGET, EVENT_COUNT };

#include "syEnemy.h"
#include "syInput.h"
#include "syStandAction.h"
#include "syMoveAction.h"
#include "syAttackAction.h"
#include "syDeadAction.h"

syEnemy::syEnemy()
{
}


syEnemy::~syEnemy()
{
}


bool syEnemy::Init()
{
	m_pActionList[0] = new syMoveAction(this); 
	m_pActionList[1] = new syStandAction(this);
	m_pActionList[2] = new syAttackAction(this);
	m_pActionList[3] = new syDeadAction(this);
	m_pAction = m_pActionList[1];
	m_dwCurrentState = ACTION_MOVE;


	int 	iKeyNumber1 = I_ScriptManager.Load(L"mario.txt");
	sySpriteData* pData = I_ScriptManager.GetPtr(iKeyNumber1);
	for (int iSprite = 0; iSprite < pData->m_SpriteListData.size(); iSprite++)
	{
		shared_ptr<syEnemy> s1 = make_shared<syEnemy>();
//		s1.get()->sySprite::Init();

		s1.get()->sySprite::Init();

		s1.get()->m_pActionList[0] = m_pActionList[0];
		s1.get()->m_pActionList[1] = m_pActionList[1];
		s1.get()->m_pActionList[2] = m_pActionList[2];
		s1.get()->m_pActionList[3] = m_pActionList[3];
		s1.get()->m_pAction = m_pAction;
		s1.get()->m_dwCurrentState = m_dwCurrentState;

		s1.get()->SetRTSize(1.3f);
		s1.get()->m_info.bLoop = true;
		s1.get()->m_bDead = false;
		s1.get()->m_iCurrentFrame = 0;
		s1.get()->setSpeed(rand()%60 + 60);
		s1.get()->i_moveFlag = 1;
		s1.get()->Set(pData->m_SpriteListData[iSprite], pData->m_iBitmapID, pData->m_iMaskBitmapID);
		s1.get()->SetPos(rand()%300+300, 0);
		m_mario.push_back(s1);
	}
	GetMario(ACTION_MOVE);
	return true;
}

void syEnemy::ProcessAI(sySprite* pTarget)
{
	m_pAction->Process(pTarget);
}
void syEnemy::SetTransition(DWORD dwEvent)
{
	// input -> event -> output

	syFiniteState* pState = I_Fsm.GetPtr((m_dwCurrentState));
	if (pState == nullptr) return;

	DWORD dwAction = pState->GetPtr(dwEvent);
	m_pAction = m_pActionList[dwAction];
	m_dwCurrentState = dwAction;
}
bool syEnemy::Frame()
{

	m_current->sySprite::Frame();
	SetPos(m_current.get()->m_pos);
	return true;
}

bool syEnemy::Release()
{
	for (auto &a : m_mario)
	{
		a.get()->Release();
	}
	delete(m_pAction);
	for (auto &a : m_pActionList)
	{
		delete(a);
	}

	return true;
}
