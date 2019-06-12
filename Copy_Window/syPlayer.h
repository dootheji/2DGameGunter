#pragma once
#include "syObject.h"
#include "syStd.h"
#include "syInput.h"
class syPlayer : public syObject
{
public:
	BITMAPINFO bmi;



	HDC		m_hMaskDC;
	HDC		m_hColorDC;
	float   m_fAngle = 0;
	float   m_fAlpha;


public:
	bool Init();
	bool Frame()
	{
		//m_fAngle += g_fSecondPerFrame * 180.0f;
		static float delAlpha = g_fSecondPerFrame * 0.02f;
		m_fAlpha += delAlpha * 0.2f;
		if (m_fAlpha > 1 || m_fAlpha < 0.02) delAlpha = -delAlpha;

	/*	void     syObject::SetPos(float x, float y)
		{
			m_pos.x = x;
			m_pos.y = y;
			SetDrawRect(m_pos, m_rtObj);
		}
*/
		syPoint pos(m_pos.x, m_pos.y);
		if (g_ActionInput.bWKey == KEY_HOLD)
		{
			pos.y = m_pos.y - m_fSpeed * g_fSecondPerFrame*delY;
			//m_pos.y -= m_fSpeed * g_fSecondPerFrame;
		}
		if (g_ActionInput.bSKey == KEY_HOLD)
		{
			pos.y = m_pos.y + m_fSpeed * g_fSecondPerFrame*delY;
		}
		if (g_ActionInput.bAKey == KEY_HOLD)
		{
			pos.x = m_pos.x - m_fSpeed * g_fSecondPerFrame*delX;
		}
		if (g_ActionInput.bDKey == KEY_HOLD)
		{
			pos.x = m_pos.x + m_fSpeed * g_fSecondPerFrame*delX;
		}

		SetPos(pos);
		

		//SetDrawRect(m_pos, m_rtObj);

		return true;
	}	

	bool Render();
	bool Release();

	bool RotateBlt();
	void GetRotationBimap(HDC hdc,
		HDC dcDesk,
		float fAngle, int w, int h);
	bool AlphaBlendRender
	(
		int iWidth, int iHeight,
		HDC hOffScreenDC,
		HDC hColorDC,
		HDC hMaskDC,
		float fAlpha
	);
	void Set(syObjectInfo info);
	void Set(syPoint pos, RECT rt, float fSpeed = 100.0f);
public:
	syPlayer();
	virtual ~syPlayer();
};



