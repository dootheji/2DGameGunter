#pragma once
#include "syBitmapMgr.h"

struct sySpriteInfo 
{

	std::vector<RECT> m_rtList;
	POINT   m_pos;

	float		m_fLifeTime;
	float		m_fTime;
	int         iBitmapID;
	int         iMaskID;
	int			m_iNumFrame; // 프레임 수 저장
	sySpriteInfo()
	{
		iBitmapID = -1;
		iMaskID = -1;
	
	}
};


class sySprite
{
public:
	sySpriteInfo m_info;

	syBitmap* m_pSprite;
	syBitmap* m_pSpriteMask;
	float		m_fDeltaTime;// = 3.0f / iNumSprite;
	bool		m_bDead;
	POINT       m_pos;
	int			m_iSpriteID;
	int			m_iCurrentFrame;
	float       m_fTmpTime;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool  Set(sySpriteInfo info, int id, int mask);
	void  Draw(DWORD dwMode);

public:
	sySprite();
	virtual ~sySprite();
};

