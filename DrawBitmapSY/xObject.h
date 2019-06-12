#pragma once
#include "xBitmap.h"


struct syObjectInfo
{
	TInputActionMap map;
	syPoint pos;
	RECT rt;
	float fSpeed;
	syObjectInfo() {}

	syObjectInfo(syPoint p, RECT r, float f)
	{
		pos = p;
		rt = r;
		fSpeed = f;
	}

};

class xObject
{
public:
	xObject();
	virtual ~xObject();
	
protected:
	xBitmap*   m_pBitmap;
	xBitmap*   m_pBitmapMask;
	syPoint		m_pos;
	float		m_fSpeed;
public:
	RECT		m_rtObj;
	xBitmap*   GetBitmap() { return m_pBitmap; }

public: 
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();

	BOOL Load(std::wstring filename);
	virtual void Set(syPoint pos, RECT rt, float fSpeed=100.0f);
	virtual void Set(syObjectInfo info)
	{
		m_pos = info.pos;
		m_fSpeed = info.fSpeed;
		m_rtObj = info.rt;
	}
};

