#pragma once
#include "syListCtrl.h"
#include "syImageCtrl.h"
class syPanel : public sySprite
{
public:
	syPanel();
	virtual ~syPanel();

public:
	std::vector<syPanel>	m_PanelList;
	std::vector<syUiCtrl>	m_ctrlList;
	syImageCtrl				m_rtDrawList[9];
public:
	bool Render();
	bool Release();
};

