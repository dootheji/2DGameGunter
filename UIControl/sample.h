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
		int iSubButtonHeight = 25, // 서브 버튼의 세로 크기
		int iOffsetBaseX = 10, // 부모의 시작위치로 부터 떨어진 거리
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

