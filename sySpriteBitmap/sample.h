#pragma once
#include "syCore.h"
#include "syBitmap.h"
#include "syObject.h"
#include "syStd.h"
#include "sySprite.h"


class sample : public syCore
{
	syBitmap* m_pSprite;
	syBitmap* m_pSpriteMask;
	
	int        m_iCurrentFrame[3];
	int        m_iBitmapID;
	int        m_iMaskBitmapID;
	int			m_iData;

	std::vector<sySpriteInfo >   m_SpriteListData;
	std::vector<sySprite>   m_SpriteList;
	std::vector<sySprite>   m_SpriteListClick;


public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	void GameDataLoad(T_STR name);


public:
	sample();
	~sample();
};
class TPlayer : public syObject
{

public:
	bool Frame()
	{
		if (g_ActionInput.bWKey == KEY_HOLD)
		{
			m_pos.y -= m_fSpeed * g_fSecondPerFrame;
		}
		if (g_ActionInput.bSKey == KEY_HOLD)
		{
			m_pos.y += m_fSpeed * g_fSecondPerFrame;
		}
		if (g_ActionInput.bAKey == KEY_HOLD)
		{
			m_pos.x -= m_fSpeed * g_fSecondPerFrame;
		}
		if (g_ActionInput.bDKey == KEY_HOLD)
		{
			m_pos.x += m_fSpeed * g_fSecondPerFrame;
		}
		return true;
	}


public:
	TPlayer() {};
	~TPlayer() {};
};
