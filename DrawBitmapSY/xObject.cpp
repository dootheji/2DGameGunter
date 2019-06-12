#include "xObject.h"
#include "xBitmapMgr.h"
#include "TInput.h"


xObject::xObject()
{
}


xObject::~xObject()
{
}

bool xObject::Init()
{
	return true;
}


bool xObject::Frame()
{
	return true;
}


bool xObject::Render()
{
	if (m_pBitmapMask != nullptr)
	{
		m_pBitmapMask->Draw(m_pos.x, m_pos.y, m_rtObj, SRCAND);
		m_pBitmap->Draw(m_pos.x, m_pos.y, m_rtObj, SRCINVERT);
		m_pBitmapMask->Draw(m_pos.x, m_pos.y, m_rtObj, SRCINVERT);
	}
	else
	{
		m_pBitmap->Draw(m_pos.x, m_pos.y, m_rtObj, SRCCOPY);
	}
	return true;
}


bool xObject::Release()
{

	return true;
}

void xObject::Set(syPoint pos, RECT rt, float fSpeed)
{
	m_rtObj = rt;
	m_pos = pos;
	m_fSpeed = fSpeed;

}


BOOL xObject::Load(std::wstring filename)
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

