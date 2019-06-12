#pragma once
#include "TCore.h"
#include "xBitmap.h"
#include "xObject.h"

class TPlayer : public xObject
{

public:
	bool Frame()
	{
		if (g_ActionInput.bWKey == KEY_HOLD)
		{
			m_pos.y -= m_fSpeed * g_fSeoundPerFrame;
		}
		if (g_ActionInput.bSKey == KEY_HOLD)
		{
			m_pos.y += m_fSpeed * g_fSeoundPerFrame;
		}
		if (g_ActionInput.bAKey == KEY_HOLD)
		{
			m_pos.x -= m_fSpeed * g_fSeoundPerFrame;
		}
		if (g_ActionInput.bDKey == KEY_HOLD)
		{
			m_pos.x += m_fSpeed * g_fSeoundPerFrame;
		}
		return true;
	}


public:
	TPlayer() {};
	~TPlayer() {};
};

class Sample : public TCore
{
	xObject  m_bk;
	TPlayer  m_Hero;
	TPlayer  m_npc;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	Sample();
	~Sample();
};
