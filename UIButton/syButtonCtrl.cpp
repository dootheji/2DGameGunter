#include "syButtonCtrl.h"
#include "syCollision.h"
#include "syBitmapMgr.h"


syButtonCtrl::syButtonCtrl()
{
	m_pCurrentBitmap = nullptr;
	m_bCollision = false;
}


syButtonCtrl::~syButtonCtrl()
{
}

bool  syButtonCtrl::Set(syObjectInfo info, int id, int mask)
{
	if (!sySprite::Set(info, id, mask))
	{
		return false;
	}
	m_pCurrentBitmap = m_pBitmap;
	return true;
}

void syButtonCtrl::Draw(DWORD dwMode)
{
	BLENDFUNCTION bf;
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.SourceConstantAlpha = m_fAlpha;
	if (m_pBitmap->m_BitmapInfo.bmBitsPixel == 32)
	{
		bf.AlphaFormat = AC_SRC_ALPHA;
		m_pCurrentBitmap->Draw(m_rtDraw.left, m_rtDraw.top,
			m_info.rtList[m_iCurrentFrame], bf);
	}
	else
	{
		bf.AlphaFormat = AC_SRC_OVER;
		m_pCurrentBitmap->Draw(m_rtDraw.left, m_rtDraw.top,
			m_info.rtList[m_iCurrentFrame], dwMode);	//dwMode = SRCCOPY
	}
}



bool  syButtonCtrl::Frame()
{
	// sprite frame
	if (!sySprite::Frame())
	{
		return false;
	}
	//button state
	if (m_bSelect && g_ActionInput.bLeftClick == KEY_UP)
	{
		if (syCollision::RectInPt(m_rtColl, g_MousePos))
		{
			m_pOwner->m_bSceneChange = true;
		}
	}
	if (m_bCollision == true)
	{
		m_pCurrentBitmap = m_pStateBitmap[0];
		m_bSelect = false;
		if (syCollision::RectInPt(m_rtColl, g_MousePos))
		{
			if (g_ActionInput.bLeftClick == KEY_HOLD)
			{
				m_pCurrentBitmap = m_pStateBitmap[2];
				m_bSelect = true;
			}
			else
			{
				m_pCurrentBitmap = m_pStateBitmap[1];
			}
		}
	}
	return true;
}

bool syButtonCtrl::Release()
{
	sySprite::Release();
	return true;
}

void syButtonCtrl::SetStateButton(
	int nor, int sel, int pus, int dis, bool bColl)
{
	m_iNormal = nor;
	m_iHover = sel;
	m_iPush = pus;
	m_iDisable = dis;
	m_bSelect = false;
	m_pStateBitmap[0] = I_BitmapMgr.GetPtr(m_iNormal);
	m_pStateBitmap[1] = I_BitmapMgr.GetPtr(m_iHover);
	m_pStateBitmap[2] = I_BitmapMgr.GetPtr(m_iPush);
	m_pStateBitmap[3] = I_BitmapMgr.GetPtr(m_iDisable);
	m_bCollision = bColl;
}