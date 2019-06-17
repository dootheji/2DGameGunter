#pragma once
#include "syCore.h"
#include "syScriptManager.h"
#include "sySprite.h"
#include "syCollision.h"
#include "syStd.h"
#include "syEnemy.h"
#include "syFSM.h"
syEnemy Enemy;
class sample : public syCore
{
	int        m_iBitmapID;
	int        m_iMaskBitmapID;
	int        m_iCurrentFrame[15];
	int		   m_iData;
	int        m_iTimerSprite = 0;
	int        m_iTimerSpriteMARIO;	//int		   iSpriteNum; 

	int iKeyNumber0;
	int iKeyNumber1;
	std::vector<sySprite>   m_gunter;
	sySprite*				current_gunter;
	shared_ptr<syEnemy>		current_mario;
	syEnemy					mario;
	std::map<RECT*, int>	m_tiles;
	syObject m_bk;
	RECT bkRect[40][30];

private :
	void	drawtileRect();
	template <typename T>
	void	tileColl(T *gamecharacter);
	void	playerkill();
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

