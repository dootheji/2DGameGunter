#include "sample.h"



sample::sample()
{
}


sample::~sample()
{
}

bool	sample::Init()
{
	////////////////////// login scene ///////
	int iBitmapID = I_BitmapMgr.Load(L"../../data/bitmap/kgcabk.bmp");
	int iMaskBitmapID = -1;// I_BitmapMgr.Load(MaskPath.c_str());

	syImageCtrl* pBk = new syImageCtrl();
	pBk->Init();
	syObjectInfo info;
	info.InitPos = syPoint(m_rtClient.right / 2, m_rtClient.bottom / 2);
	RECT rt = { 0, 0, m_rtClient.right, m_rtClient.bottom };
	info.rt = rt;
	info.fSpeed = 0.0f;
	info.rtList.push_back(rt);
	pBk->Set(info, iBitmapID, iMaskBitmapID);
	m_LoginScene.m_ctrlList.push_back(pBk);


	int iNormal = I_BitmapMgr.Load(L"../../data/bitmap/main_start_nor.bmp");
	int iSelect = I_BitmapMgr.Load(L"../../data/bitmap/main_start_sel.bmp");
	int iPush = I_BitmapMgr.Load(L"../../data/bitmap/main_start_pus.bmp");
	int iDisable = I_BitmapMgr.Load(L"../../data/bitmap/main_start_dis.bmp");
	iMaskBitmapID = -1;// I_BitmapMgr.Load(MaskPath.c_str());

	syButtonCtrl* pButton = new syButtonCtrl;
	syObjectInfo info2;
	pButton->SetStateButton(iNormal, iSelect, iPush, iDisable, true);
	info2.InitPos = syPoint(m_rtClient.right / 2, m_rtClient.bottom / 2);
	RECT rt2 = { 0, 0,
		I_BitmapMgr.GetPtr(iNormal)->m_BitmapInfo.bmWidth,
		I_BitmapMgr.GetPtr(iNormal)->m_BitmapInfo.bmHeight };
	info2.rt = rt2;
	info2.fSpeed = 0.0f;
	info2.rtList.push_back(rt2);
	pButton->m_pOwner = &m_LoginScene;
	pButton->Set(info2, iNormal, iMaskBitmapID);
	m_LoginScene.m_ctrlList.push_back(pButton);


	///////////////////////// LOBBY /////////////////////
	iBitmapID = I_BitmapMgr.Load(L"../../data/bitmap/KGCALOGO.bmp");
	syImageCtrl* pLobbyBk = new syImageCtrl();
	syObjectInfo info3;
	info3.InitPos = syPoint(m_rtClient.right / 2, m_rtClient.bottom / 2);
	RECT rt3 = { 0, 0, m_rtClient.right, m_rtClient.bottom };
	info3.rt = rt3;
	info3.fSpeed = 0.0f;
	info3.rtList.push_back(rt3);
	pLobbyBk->Set(info3, iBitmapID, iMaskBitmapID);
	m_LobbyScene.m_ctrlList.push_back(pLobbyBk);

	// ÇöÀç ¾À ¼¼ÆÃ
	m_pCurrentScene = &m_LoginScene;

	//m_LoginScene.Load(L"loginInfo.txt");
	return true;
};

bool	sample::Frame()
{
	m_pCurrentScene->Frame();
	if (m_pCurrentScene->IsSceneChange() == true)
	{
		m_pCurrentScene = &m_LobbyScene;
	}
	return true;
};

bool	sample::Render()
{
	m_pCurrentScene->Render();
	return true;
};
bool	sample::Release()
{
	m_LoginScene.Release();
	m_LobbyScene.Release();
	return true;
};



syCORE_RUN(sy UIButton, 0, 0, 800, 600);