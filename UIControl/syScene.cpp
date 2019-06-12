#include "syScene.h"



syScene::syScene()
{
	m_bSceneChange = false;
}


syScene::~syScene()
{
}


bool syScene::Init()
{
	return true;
}

bool syScene::Frame()
{
	for (syUIComponent* data : m_ctrlList)
	{
		data->Frame();
	}
	return true;
}

bool	syScene::Render()
{
	for (syUIComponent* data : m_ctrlList)
	{
		syListCtrl* pButton = (syListCtrl*)data;
		SetDrawRect(data->getPos(), data->m_info.rtList[0]);
		data->Draw(SRCCOPY);
	}
	for (syPanel& data : m_PanelList)
	{
		data.Draw(SRCCOPY);
	}
	return true;
}

bool syScene::Release()
{
	for (syPanel& data : m_PanelList)
	{
		data.Release();
	}

	for (syUIComponent* data : m_ctrlList)
	{
		data->Release();
	}
	return true;
}



