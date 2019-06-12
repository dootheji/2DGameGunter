#pragma once
#include "TStd.h"
class xBitmap 
{
public:
	xBitmap();
	virtual ~xBitmap();

public:
	HBITMAP m_hBitmap;
	HDC m_hMemDC;
	T_STR m_szName;
	T_STR m_szPath;
	int m_iIndex;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	bool Load(std::wstring filename);
	bool Draw(float x, float y, RECT rt, DWORD iMode);
	bool    DrawColorKey(
		float x, float y, RECT rt, COLORREF color);
};

