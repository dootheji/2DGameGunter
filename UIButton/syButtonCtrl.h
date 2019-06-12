#pragma once
#include "syUiCtrl.h"

class syButtonCtrl : public syUiCtrl
{

public:
	bool		m_bCollision;
	int			m_iNormal;
	int			m_iHover;
	int			m_iPush;
	int			m_iDisable;
	bool		m_bSelect;
	syBitmap*	m_pCurrentBitmap;
	syBitmap*	m_pStateBitmap[4];

public:
	void		SetStateButton(int nor, int sel, int pus, int dis, bool coll = false);
	void		Draw(DWORD dwMode);
	bool		Set(syObjectInfo info, int id, int mask);
	bool		Frame();
	bool		Release();
public:
	syButtonCtrl();
	virtual ~syButtonCtrl();
};

