#pragma once
#include "TCore.h"
class Sample : public TCore
{
	// ��Ʈ�� �ڵ�
	HBITMAP  m_hBitmap;
	HDC      m_hMemDC;
	float    m_dwX;
	float    m_dwY;
	RECT     m_rtHero;
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	Sample();
	~Sample();
};

