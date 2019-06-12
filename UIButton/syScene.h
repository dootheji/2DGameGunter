#pragma once
#include "syPanel.h"
class syScene : public sySprite
{
public:
	syScene();
	virtual ~syScene();
public:
	std::vector<syPanel>   m_PanelList;
	std::list<syUiCtrl*>	  m_ctrlList;
	//bool  m_bSceneChange;
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

