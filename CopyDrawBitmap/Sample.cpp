#include "Sample.h"
#pragma comment(lib, "TTTTCoreLib.lib") 
// Bitmap -> Bitmap / blit
// DC -> DC
bool Sample::Init()
{
	m_hBitmap = (HBITMAP)LoadImage(
		m_hInstance,
		_T("../../data/bitmap/bitmap1.bmp"),
		IMAGE_BITMAP,
		0, 0,
		LR_DEFAULTSIZE | LR_LOADFROMFILE);

	m_hMemDC = CreateCompatibleDC(m_hScreenDC);
	SelectObject(m_hMemDC, m_hBitmap);	

	m_rtHero.left = 90;
	m_rtHero.top = 1;
	m_rtHero.right = 40;
	m_rtHero.bottom = 60;
	return true;
}
bool Sample::Render()
{
	
	// DC -> DC
	BitBlt(m_hScreenDC, m_dwX, m_dwY,
		m_rtHero.right,
		m_rtHero.bottom,
			m_hMemDC, 
		m_rtHero.left, 
		m_rtHero.top, SRCCOPY);

	return true;
}
bool Sample::Frame()
{
	if (g_ActionInput.bSpace == KEY_PUSH)
	{
		m_bDebug = !m_bDebug;
	}

	if (g_ActionInput.bWKey == KEY_HOLD)
	{
		m_dwY -= 100*g_fSeoundPerFrame;
	}
	if (g_ActionInput.bSKey == KEY_HOLD)
	{
		m_dwY += 100 * g_fSeoundPerFrame;
	}
	if (g_ActionInput.bAKey == KEY_HOLD)
	{
		m_dwX -= 100 * g_fSeoundPerFrame;
	}
	if (g_ActionInput.bDKey == KEY_HOLD)
	{
		m_dwX += 100 * g_fSeoundPerFrame;
	}
	return true;
}
bool Sample::Release()
{
	DeleteObject(m_hBitmap);
	return true;
}
Sample::Sample()
{
	m_dwX = 100;
	m_dwY = 100;
}


Sample::~Sample()
{
}
TCORE_RUN(0, 0, 800, 600);