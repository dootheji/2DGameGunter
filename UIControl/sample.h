#pragma once
#include "syCore.h"
#include "syScene.h"
class sample : public syCore
{
public:
	sample();
	~sample();
public:
	// [R],[G],[B]
	syUIComponent  m_BaseControls;
	void  AddBaseControl();
	void    DefaultButtonControll();
	void	DefalultListControll(int iCount = 10,
		int iSubButtonHeight = 25, // ���� ��ư�� ���� ũ��
		int iOffsetBaseX = 10, // �θ��� ������ġ�� ���� ������ �Ÿ�
		int iOffsetBaseY = 10,
		int iButtonStep = 2);

	syScene* m_pCurrentScene;
	syScene  m_LoginScene;
	syScene  m_LobbyScene;
	syScene  m_InGameScene;
	syScene  m_ResultScene;
public:
	bool   Init();
	bool   Frame();
	bool   Render();
	bool   Release();
	LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

