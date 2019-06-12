#include "sample.h"
#include "syBitmapMgr.h"


sample::sample()
{
	m_pCurrentScene = &m_LoginScene;
}


sample::~sample()
{
}


LRESULT		sample::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (WM_UICONTRLMSG == msg)
	{
		UINT msgControll = HIWORD(wParam);
		if (WM_GAMESTART == msgControll)
		{
			m_pCurrentScene = &m_LobbyScene;
		}
		return m_pCurrentScene->MsgProc(hWnd, msg, wParam, lParam);
	}
	return 1;
}

void	sample::DefalultListControll(int iCount,
	int iSubButtonHeight,
	int iOffsetBaseX,
	int iOffsetBaseY,
	int iButtonStep)
{
	int iNormal = I_BitmapMgr.Load(L"../../data/bitmap/black.bmp");
	int iSelect = -1;

	syListCtrl* pListCtl = new syListCtrl;
	syObjectInfo infoBase;
	ZeroMemory(&infoBase, sizeof(syObjectInfo));
	pListCtl->SetStateButton(iNormal, iNormal, iNormal, iNormal, true);
	RECT rt = { 0, 0,
		I_BitmapMgr.GetPtr(iNormal)->m_BitmapInfo.bmWidth,
		I_BitmapMgr.GetPtr(iNormal)->m_BitmapInfo.bmHeight };
	RECT rtBaseClient = { 0, 0,	200, 200 };
	infoBase.InitPos = syPoint(
		rtBaseClient.left + rtBaseClient.right / 2,
		rtBaseClient.top + rtBaseClient.bottom / 2);
	infoBase.rt = rtBaseClient;
	infoBase.rtList.push_back(rt);
	pListCtl->Set(infoBase, iNormal, -1);

	pListCtl->SetAttribute(iSubButtonHeight, // 서브 버튼의 세로 크기
		iOffsetBaseX, // 부모의 시작위치로 부터 떨어진 거리
		iOffsetBaseY,
		iButtonStep);

	pListCtl->m_iEnd =
		(infoBase.rt.bottom - iOffsetBaseY) /
		(iSubButtonHeight + iButtonStep);

	iNormal = I_BitmapMgr.Load(L"../../data/bitmap/EditBoxBacknor.bmp");
	iSelect = I_BitmapMgr.Load(L"../../data/bitmap/EditBoxBacksel.bmp");
	int iPush = I_BitmapMgr.Load(L"../../data/bitmap/EditBoxBackpus.bmp");
	int iDisable = I_BitmapMgr.Load(L"../../data/bitmap/EditBoxBack.bmp");

	syBitmap* pBitmap = I_BitmapMgr.GetPtr(iNormal);

	for (int iButton = 0; iButton < iCount; iButton++)
	{
		syButtonCtrl* pSubButton = (syButtonCtrl*)m_BaseControls.m_ctrlList[0]->Clone();
		pSubButton->m_iIndexType = iButton;
		syObjectInfo info;
		ZeroMemory(&info, sizeof(syObjectInfo));
		RECT rt = { 0, 0,pBitmap->m_BitmapInfo.bmWidth,	pBitmap->m_BitmapInfo.bmHeight };
		RECT rtSubClient = { 0, 0,
			rtBaseClient.right - iOffsetBaseX * 2,
			iSubButtonHeight };
		info.rt = rtSubClient;
		info.rtList.push_back(rt);

		pSubButton->Set(info, iNormal, -1);
		pSubButton->SetStateButton(iNormal, iSelect, iPush, iDisable, true);
		pSubButton->SetPos(rtBaseClient.left + rtSubClient.right / 2 + iOffsetBaseX,
			rtBaseClient.top + (rtSubClient.bottom / 2) +
			iOffsetBaseY +
			(iSubButtonHeight + iButtonStep)*iButton);
		pListCtl->m_ctrlList.push_back(pSubButton);
	}
	m_BaseControls.Add(pListCtl);
}
void sample::DefaultButtonControll()
{
	int iNormal = I_BitmapMgr.Load(L"../../data/bitmap/main_start_nor.bmp");
	int iSelect = I_BitmapMgr.Load(L"../../data/bitmap/main_start_sel.bmp");
	int iPush = I_BitmapMgr.Load(L"../../data/bitmap/main_start_pus.bmp");
	int iDisable = I_BitmapMgr.Load(L"../../data/bitmap/main_start_dis.bmp");
	int iMaskBitmapID = -1;// I_BitmapMgr.Load(MaskPath.c_str());
	syButtonCtrl* pButton = new syButtonCtrl;
	syObjectInfo info;
	ZeroMemory(&info, sizeof(syObjectInfo));
	pButton->SetStateButton(iNormal, iSelect, iPush, iDisable, true);
	RECT rt = { 0, 0,
		I_BitmapMgr.GetPtr(iNormal)->m_BitmapInfo.bmWidth,
		I_BitmapMgr.GetPtr(iNormal)->m_BitmapInfo.bmHeight };
	info.InitPos = syPoint(392,357);
	info.rt = rt;
	info.rtList.push_back(rt);
	pButton->Set(info, iNormal, iMaskBitmapID);
	m_BaseControls.Add(pButton);
}

void  sample::AddBaseControl()
{
	DefaultButtonControll();
	DefalultListControll();
}
bool	sample::Init()
{
	AddBaseControl();
	int iBitmapID = I_BitmapMgr.Load(L"../../data/bitmap/gunter/startBK.bmp");
	int iMaskBitmapID = -1;// I_BitmapMgr.Load(MaskPath.c_str());
	
	syImgCtrl* pBk = new syImgCtrl();
	pBk->Init();
	syObjectInfo info;
	info.InitPos = syPoint(m_rtClient.right / 2, m_rtClient.bottom / 2);
	RECT rt = { 0, 0, m_rtClient.right, m_rtClient.bottom };
	info.rt = rt;
	info.fSpeed = 0.0f;
	info.rtList.push_back(rt);
	pBk->Set(info, iBitmapID, iMaskBitmapID);
	m_LoginScene.m_ctrlList.push_back(pBk);

	syButtonCtrl* pButton = (syButtonCtrl*)m_BaseControls.m_ctrlList[0]->Clone();
	pButton->m_iIndexType = 888;
	m_LoginScene.m_ctrlList.push_back(pButton);

	syListCtrl* pListControl = (syListCtrl*)m_BaseControls.m_ctrlList[1]->Clone();
	pListControl->m_iIndexType = 999;
	m_LobbyScene.m_ctrlList.push_back(pListControl);
	m_pCurrentScene = &m_LoginScene;
	return true;
}

bool	sample::Frame()
{
	m_pCurrentScene->Frame();
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
syCORE_RUN(UIBUTTON, 0, 0, 800, 600);