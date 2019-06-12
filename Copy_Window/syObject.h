#pragma once
#include "syBitmap.h"


struct syObjectInfo
{
	syPoint		InitPos;
	int			iNumFrame;
	float		fTime;
	float		fLifeTime;
	int			iBitmapID;
	int			iMaskID;
	bool		bLoop;

	syPoint		m_pos;
	RECT		rt;
	float		fSpeed;

	std::vector<RECT> rtList;
	syObjectInfo() {
		iBitmapID = -1;
		iMaskID	= -1;
		bLoop = false;
	}
	syObjectInfo(syPoint p, RECT r, float f)
	{
		m_pos = p;
		rt = r;
		fSpeed = f;
		iBitmapID = -1;
		iMaskID = -1;
		bLoop = false;
	}
};


class syObject
{
public:
	syObject();
	virtual ~syObject();

protected:
	syBitmap*   m_pBitmap;
	syBitmap*   m_pBitmapMask;
	syPoint		m_pos;
	float		m_fSpeed;
	float		m_fAlpha;
	int         m_irtSize;			
	float		m_frtFactor;

public:
	float		delX;
	float		delY;
	int         i_moveFlag;	//0 : 정지, 1 : 이동(랜덤값이동)  2:충돌했음 3:사용자입력


	RECT        m_rtDraw;
	RECT		m_rtObj;
	RECT		m_rtResize;
	RECT        m_rtColl;
	syBitmap*   GetBitmap() { return m_pBitmap; }
	syBitmap*   GetBitmapMask() { return m_pBitmapMask; }
	RECT		GetDrawRect() { return m_rtDraw; }
	RECT		GetCollRect() { return m_rtColl; }
	syPoint		getPos() 	{	return m_pos;	}
	float       getSpeed() { return m_fSpeed; }
	void		setSpeed(float sp) { m_fSpeed = sp; }
	void		SetPos(POINT pos);
	void		SetPos(syPoint pos);
	void		SetPos(float x, float y);
	void		SetRTSize(float rtsize);

public:
	void		 setDel(float dx, float dy)
	{
		delX = dx;
		delY = dy;
		if (dx < -1)
		{
			delX = -1;
		}
		if (dy < -1)
		{
			delY = -1;
		}
		if (dx > 1)
		{
			delX = 1;
		}
		if (dy > 1)
		{
			delY = 1;
		}

		/*	if (dx == 0 && dy == 0)
		{
			delX = 0;
			delY = 0;
			return;
		}
		*/
		//delX = (float)dx/ sqrt(dx * dx + dy * dy);
		//delY = (float)dy/sqrt(dx * dx + dy * dy);


	}
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();

	virtual bool	Load(std::wstring filename);
	virtual void	SetDrawRect(syPoint p, RECT rt);
	virtual void	SetColliRect(syPoint p, RECT rt);
	virtual void	Set(syPoint pos, RECT rt, float fSpeed = 100.0f);
	virtual void	Set(syObjectInfo info)
	{
		m_pos = info.m_pos;
		m_fSpeed = info.fSpeed;
		m_rtObj = info.rt;
		int iOffWidth = m_rtObj.right;
		int iOffHeight = m_rtObj.bottom;
		m_irtSize = sqrt(iOffWidth*iOffWidth + iOffHeight * iOffHeight);
		SetDrawRect(m_pos, m_rtObj);
	}
};

