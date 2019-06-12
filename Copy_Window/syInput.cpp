#include "syInput.h"
TInputActionMap  g_ActionInput;
POINT g_MousePos;

DWORD   syInput::Key(DWORD dwKey)
{
	SHORT sKey = GetAsyncKeyState(dwKey);
	return sKey;
}

DWORD   syInput::KeyCheck(DWORD dwKey)
{
	SHORT sKey = GetAsyncKeyState(dwKey);
	// enum { KEY_FREE, KEY_PUSH, KEY_HOLD, KEY_UP}
	//  1000 0000 0000 0000
	if (sKey & 0x8000) // 
	{
		if (m_dwKeyState[dwKey] == KEY_FREE ||
			m_dwKeyState[dwKey] == KEY_UP)
		{
			m_dwKeyState[dwKey] = KEY_PUSH;
		}
		else
		{
			m_dwKeyState[dwKey] = KEY_HOLD;
		}
	}
	else
	{
		if (m_dwKeyState[dwKey] == KEY_PUSH ||
			m_dwKeyState[dwKey] == KEY_HOLD)
		{
			m_dwKeyState[dwKey] = KEY_UP;
		}
		else
		{
			m_dwKeyState[dwKey] = KEY_FREE;
		}
	}
	return m_dwKeyState[dwKey];
}
bool       syInput::Init()
{
	ZeroMemory(m_dwKeyState, sizeof(DWORD) * 256);
	return true;
};
bool       syInput::Frame()
{
	GetCursorPos(&m_MousePos); // 화면스크린 좌표계
	ScreenToClient(g_hWnd, &m_MousePos);
	g_MousePos = m_MousePos;

	g_ActionInput.bWKey = KeyCheck('W');
	g_ActionInput.bSKey = KeyCheck('S');
	g_ActionInput.bAKey = KeyCheck('A');
	g_ActionInput.bDKey = KeyCheck('D');
	g_ActionInput.bExit = KeyCheck(VK_ESCAPE);
	g_ActionInput.bSpace = KeyCheck(VK_SPACE);

	for (int iButton = 0; iButton < 3; iButton++)
	{
		if (m_dwBeforeMouseState[iButton] == KEY_PUSH)
		{
			if (m_dwMouseState[iButton] == KEY_PUSH)
			{
				m_dwMouseState[iButton] = KEY_HOLD;
			}
		}
		m_dwBeforeMouseState[iButton] = m_dwMouseState[iButton];
	}
	g_ActionInput.bLeftClick = m_dwMouseState[0];
	g_ActionInput.bMiddleClick = m_dwMouseState[1];
	g_ActionInput.bRightClick = m_dwMouseState[2];
	return true;
};
bool       syInput::Render() {
	//HDC hdc = GetDC(g_hWnd);
	//SetBkColor(g_hOffScreenDC, RGB(255, 0, 0));
	//SetTextColor(g_hOffScreenDC, RGB(0, 0, 255));
	//SetBkMode(g_hOffScreenDC, TRANSPARENT);
	//TextOut(g_hOffScreenDC, 0, 0, m_csBuffer, _tcslen(m_csBuffer));
	//ReleaseDC(g_hWnd, hdc);
	return true;
};
bool       syInput::Release() {
	return true;
};
LRESULT syInput::MsgProc(MSG msg)
{
	m_dwMouseState[0] = KEY_FREE;
	m_dwMouseState[1] = KEY_FREE;
	m_dwMouseState[2] = KEY_FREE;
	switch (msg.message)
	{
	case WM_LBUTTONDOWN:
	{
		m_dwMouseState[0] = KEY_PUSH;
	}break;
	case WM_LBUTTONUP:
	{
		m_dwMouseState[0] = KEY_UP;
	}break;
	case WM_MBUTTONDOWN:
	{
		m_dwMouseState[1] = KEY_PUSH;
	}break;
	case WM_MBUTTONUP:
	{
		m_dwMouseState[1] = KEY_UP;
	}break;
	case WM_RBUTTONDOWN:
	{
		m_dwMouseState[2] = KEY_PUSH;
	}break;
	case WM_RBUTTONUP:
	{
		m_dwMouseState[2] = KEY_UP;
	}break;
	}
	return 1;
}



syInput::syInput()
{
}


syInput::~syInput()
{
}
