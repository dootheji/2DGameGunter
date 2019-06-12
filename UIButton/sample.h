#pragma once
#include "syCore.h"
#include "syScene.h"

class sample : public syCore
{
public:
	sample();
	~sample();
private:
	syScene  m_LoginScene;
	syScene  m_LobbyScene;
	syScene* m_pCurrentScene;
	//syScene  m_InGameScene;
	//syScene  m_ResultScene;
public:
	bool   Init();
	bool   Frame();
	bool   Render();
	bool   Release();
};

