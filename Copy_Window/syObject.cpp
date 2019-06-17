#include "syObject.h"
#include "syBitmapMgr.h"
#include "syInput.h"


syObject::syObject()
{
	delX = 0;
	delY = 0;
	m_irtSize = 1;
	m_frtFactor = 1.0f;
	m_fAlpha = 255.0f;
	bool isFront = true;
}


syObject::~syObject()
{
}

bool syObject::Load(std::wstring filename)
{
	int iKey = I_BitmapMgr.Load(filename);
	m_pBitmap = I_BitmapMgr.GetPtr(iKey);
	if (m_pBitmap == nullptr) return false;

	T_STR name = m_pBitmap->m_szPath;
	name += L"Mask_";
	name += m_pBitmap->m_szName;

	iKey = I_BitmapMgr.Load(name);
	m_pBitmapMask = I_BitmapMgr.GetPtr(iKey);

	return true;
}


bool syObject::Init()
{
	return true;
}


bool syObject::Frame()
{
	if (this->i_moveFlag == 0)
	{
		return true;
	}
	syPoint pos(m_pos.x, m_pos.y);

	if (i_moveFlag == 3)		// 중력 존재
	{
		setDel(0, delY);
		if (g_ActionInput.bWKey == KEY_HOLD)
		{
			if (delY <= -1) 
			{
				setDel(delX, 1); 
			}
		}
		if (g_ActionInput.bSKey == KEY_HOLD)
		{
			//setDel(delX, -1);
		}
		if (g_ActionInput.bAKey == KEY_HOLD)
		{
			setDel(-1, delY);
		}
		if (g_ActionInput.bDKey == KEY_HOLD)
		{
			setDel(1, delY);
		}
	}
	setDel(delX, delY - 0.05);

	pos.x = m_pos.x + delX * m_fSpeed * g_fSecondPerFrame;
	pos.y = m_pos.y - delY * m_fSpeed * g_fSecondPerFrame * 3;
	SetPos(pos);
	return true;
}

bool syObject::Render()
{
	m_pBitmap->m_fScale = this->m_frtFactor;
	if (m_pBitmapMask != nullptr)
	{
		m_pBitmapMask->Draw(m_rtDraw.left, m_rtDraw.top, m_rtObj, SRCAND);
	
		m_pBitmap->Draw(m_rtDraw.left, m_rtDraw.top, m_rtObj, SRCINVERT);
		m_pBitmapMask->Draw(m_rtDraw.left, m_rtDraw.top, m_rtObj, SRCINVERT);
	}
	else
	{
		m_pBitmap->Draw(m_rtDraw.left, m_rtDraw.top, m_rtObj, SRCCOPY);
	}



	return true;
}


bool syObject::Release()
{

	return true;
}

void syObject::SetColliRect(syPoint p, RECT rt)
{
	m_rtColl.left = p.x - (rt.right*m_frtFactor / 2);
	m_rtColl.top = p.y - (rt.bottom*m_frtFactor / 2);
	m_rtColl.right = rt.right*m_frtFactor + m_rtColl.left;
	m_rtColl.bottom = rt.bottom*m_frtFactor + m_rtColl.top;

	float fDistance = sqrt(
		(m_rtColl.right - m_rtColl.left) * (m_rtColl.right - m_rtColl.left)
		+
		(m_rtColl.bottom - m_rtColl.top) * (m_rtColl.bottom - m_rtColl.top));

	m_Sphere.vCenter = m_pos;
	m_Sphere.fRadius = fDistance / 2;
}

void syObject::SetDrawRect(syPoint p, RECT rt)
{
	m_rtDraw.left = p.x - (rt.right*m_frtFactor / 2);
	m_rtDraw.top = p.y - (rt.bottom*m_frtFactor / 2);
	m_rtDraw.right = rt.right*m_frtFactor;
	m_rtDraw.bottom = rt.bottom*m_frtFactor;
	SetColliRect(p, rt);
}



void syObject::Set(syPoint pos, RECT rt, float fSpeed)
{
	m_rtObj = rt;
	int iOffWidth = m_rtObj.right;
	int iOffHeight = m_rtObj.bottom;

	m_irtSize = sqrt(iOffWidth*iOffWidth + iOffHeight * iOffHeight);
	m_pos = pos;
	m_fSpeed = fSpeed;
	SetDrawRect(m_pos, m_rtObj);
	
}
void     syObject::SetPos(POINT pos)
{
	m_pos.x = pos.x;
	m_pos.y = pos.y;
	SetDrawRect(m_pos, m_rtObj);
}
void     syObject::SetPos(syPoint pos)
{
	m_pos = pos;
	SetDrawRect(m_pos, m_rtObj);
}
void     syObject::SetPos(float x, float y)
{
	m_pos.x = x;
	m_pos.y = y;
	SetDrawRect(m_pos, m_rtObj);
}

void     syObject::SetRTSize(float rtsize)
{
	m_frtFactor *= rtsize;
	//m_irtSize *= m_frtFactor;
	//여기 그리는 위치 다시 해야 함...
//	this->GetBitmap.setScale(m_frtFactor);

	/*
	RECT        m_rtDraw;			2배
	RECT		m_rtObj;			그대로
	RECT        m_rtColl;			2배
	*/


}