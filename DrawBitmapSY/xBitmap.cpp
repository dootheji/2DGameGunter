#include "xBitmap.h"



xBitmap::xBitmap()
{
}


xBitmap::~xBitmap()
{
}

bool xBitmap::Load(std::wstring filename)
{
	m_hBitmap = (HBITMAP)LoadImage(
		g_hInstance,
		filename.c_str(),
		IMAGE_BITMAP,
		0, 0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);

	if (m_hBitmap == NULL) return false;

	m_hMemDC = CreateCompatibleDC(g_hScreenDC);
	SelectObject(m_hMemDC, m_hBitmap);
	return true;
}

bool xBitmap::Draw(float x, float y, RECT rt, DWORD iMode)
{

	BitBlt(g_hOffScreenDC, x, y, 
		rt.right, rt.bottom, m_hMemDC, rt.left, rt.top, iMode
	);

	return true;
}

bool    xBitmap::DrawColorKey(
	float x, float y, RECT rt, COLORREF color)
{
	// DC -> DC
	TransparentBlt(
		g_hOffScreenDC, x, y, rt.right, rt.bottom,
		m_hMemDC, rt.left, rt.top, rt.right, rt.bottom,
		color);
	return true;
}

bool xBitmap::Init()
{
	return true;
}
bool xBitmap::Frame()
{
	return true;
}
bool xBitmap::Render()
{
	return true;
}
bool xBitmap::Release()
{
	DeleteObject(m_hBitmap);
	return true;
}