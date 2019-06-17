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
	

		if (pTarget->delY < 0 && pTarget->delY>-1)
		{
		
			/*		current_mario.get()->m_bDead = true;*/
			m_pOwner->GetMario(4);
		}
		else
		{
			
			/*current_gunter->m_bDead = true;*/
			//delete current_gunter;
			//current_gunter->Release();

		}

}