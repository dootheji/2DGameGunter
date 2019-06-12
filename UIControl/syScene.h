#pragma once
#include "syPanel.h"
class syScene : public syUIComponent
{
public:
	syScene();
	virtual ~syScene();
public:
	std::vector<syPanel>   m_PanelList;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
	bool IsSceneChange()
	{
		if (m_bSceneChange)
		{
			return true;
		}
		return false;
	};

};

