#include "syScene.h"



syScene::syScene()
{
	m_bSceneChange = false;
}


syScene::~syScene()
{
	m_bSceneChange = false;
}


bool syScene::Init()
{
	return true;
}

bool syScene::Frame()
{
	for (syUiCtrl* data : m_ctrlList)
	{
		data->Frame();
	}
	return true;
}

bool syScene::Render()
{
	for (syUiCtrl* data : m_ctrlList)
	{
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
	for (syUiCtrl* data : m_ctrlList)
	{
		data->Release();
	}

	for (syPanel& data : m_PanelList)
	{
		data.Release();
	}

	return true;
}
//
//bool	syScene::Frame()
//{
//	for (syUiCtrl* data : m_ctrlList)
//	{
//		data->Frame();
//	}
//	return true;
//}
//
//bool	syScene::Render()
//{
//	for (syUiCtrl* data : m_ctrlList)
//	{
//		data->Draw(SRCCOPY);
//	}
//	return true;
//};