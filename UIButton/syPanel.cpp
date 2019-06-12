#include "syPanel.h"



syPanel::syPanel()
{
}


syPanel::~syPanel()
{
}
bool syPanel::Render()
{
	for (syUiCtrl& data : m_ctrlList)
	{
		data.Draw(SRCCOPY);
	}

	for (syPanel& data : m_PanelList)
	{
		data.Draw(SRCCOPY);
	}
	return true;
}
bool syPanel::Release()
{
	for (syUiCtrl& data : m_ctrlList)
	{
		data.Release();
	}

	for (syPanel& data : m_PanelList)
	{
		data.Release();
	}
	return true;
}