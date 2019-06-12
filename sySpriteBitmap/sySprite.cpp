#include "sySprite.h"



sySprite::sySprite()
{
	m_fTmpTime = 0.0f;
	m_fDeltaTime = 0.0f;
	m_iCurrentFrame = 0;
	m_iSpriteID = 0;
	m_bDead = false;
}


sySprite::~sySprite()
{

}

bool sySprite::Set(sySpriteInfo info, int id, int mask)
{
	m_info = info;
	if (info.m_fLifeTime < 0.0f)
	{
		m_bDead == true;
	}
	if (m_info.iBitmapID == -1)
	{
		m_pSprite = I_BitmapMgr.GetPtr(id);
	}
	else
	{
		m_pSprite = I_BitmapMgr.GetPtr(m_info.iBitmapID);
	}
	if (m_info.iMaskID == -1)
	{
		m_pSpriteMask = I_BitmapMgr.GetPtr(mask);
	}
	else
	{
		m_pSpriteMask = I_BitmapMgr.GetPtr(m_info.iMaskID);
	}
	m_fDeltaTime = m_info.m_fTime / m_info.m_iNumFrame;
	m_pos.x = m_info.m_pos.x;
	m_pos.y = m_info.m_pos.y;


	return true;
}

bool sySprite::Init()
{
	return true;
}
bool sySprite::Frame()
{
	if (m_info.m_iNumFrame <= 1) return true;	//프레임 하나일 때 연산 X

	m_fTmpTime += g_fSecondPerFrame;
	m_info.m_fLifeTime -= g_fSecondPerFrame;
	if (m_info.m_fLifeTime <= 0) m_bDead = true;


	if (m_fTmpTime > m_fDeltaTime)
	{
		m_iCurrentFrame++;
		if (m_iCurrentFrame >= m_info.m_iNumFrame)
		{
			m_iCurrentFrame = 0;
		}
		m_fTmpTime = 0.0f;
	}
	return true;
}
bool sySprite::Render()
{

	if (m_bDead == true) return true;

	if (m_pSpriteMask != nullptr)
	{
		m_pSpriteMask->Draw(m_pos.x, m_pos.y,
			m_info.m_rtList[m_iCurrentFrame], SRCAND);
		m_pSprite->Draw(m_pos.x, m_pos.y,
			m_info.m_rtList[m_iCurrentFrame], SRCINVERT);
		m_pSpriteMask->Draw(m_pos.x, m_pos.y,
			m_info.m_rtList[m_iCurrentFrame], SRCINVERT);

	}
	else
	{
		m_pSprite->Draw(m_pos.x, m_pos.y,
			m_info.m_rtList[m_iCurrentFrame], MERGEPAINT);
	}
	return true;
}
bool sySprite::Release()
{
	m_info.m_rtList.clear();
	return true;
}

void  sySprite::Draw(DWORD dwMode) 
{
	
	m_pSprite->Draw(m_info.m_pos.x, m_info.m_pos.y,
		m_info.m_rtList[m_iCurrentFrame], dwMode);
}