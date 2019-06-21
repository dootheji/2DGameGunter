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
	std::vector<sySprite>					m_gunter;
	sySprite*								current_gunter;
	std::vector<shared_ptr<syEnemy>>		current_mario;
	//shared_ptr<syEnemy> 	mario;
	std::map<RECT*, int>					m_tiles;
	syObject								m_bk;
	syObject								m_win;
	syObject								m_gameover;
	RECT									bkRect[40][30];

private :
	void	drawtileRect();
	//template <typename T>
	//void	tileColl(T *gamecharacter);
	template <typename T>
	void	tileColl(T *gamecharacter);
	template <typename T>
	void	tileColl(shared_ptr<T> gamecharacter);
	template <typename T>
	bool	istileColl(T *gamecharacter);

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

