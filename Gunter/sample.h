#pragma once
#include "syCore.h"
#include "syScriptManager.h"
#include "sySprite.h"
#include "syCollision.h"
#include "syStd.h"
#include "syEnemy.h"
#include "syFSM.h"

class sample : public syCore
{
	int        m_iBitmapID;
	int        m_iMaskBitmapID;
	int        m_iCurrentFrame[15];
	int		   m_iData;
	int        m_iTimerSprite;
	int		   iSpriteNum; 

	int iKeyNumber0;
	int iKeyNumber1;
	std::vector<sySprite>   m_gunter;
	std::vector<shared_ptr<syEnemy>>   m_mario;
	std::map<RECT*, int>	m_tiles;
	syObject m_bk;
	RECT bkRect[40][30];

private :
	void	drawtileRect();

public:
	bool   Init();
	bool   Frame();
	bool   Render();
	bool   Release();

	void setSpriteNum();

public:
	sample();
	~sample();
};

