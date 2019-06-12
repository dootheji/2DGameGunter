#include "sample.h"
#include "syBitmapMgr.h"
#pragma comment(lib, "sy_WindowLib.lib") 
#include <iostream>


sample::sample()
{
	//m_iTimerSprite = 0;
}


sample::~sample()
{
}

void sample::GameDataLoad(T_STR name)
{
	FILE* fp = 0;
	_wfopen_s(&fp, name.c_str(), _T("rt"));
	assert(fp != NULL);

	TCHAR buffer[256] = { 0, };
	TCHAR temp[256] = { 0, };
	TCHAR bitmap[256] = { 0, };
	TCHAR mask[256] = { 0, };
	int iNumSprite = -1;

	_fgetts(buffer, _countof(buffer), fp);
	_stscanf_s(buffer, _T("%s%d%s%s"),
		temp, _countof(temp),
		&iNumSprite,
		bitmap, _countof(bitmap),
		mask, _countof(mask));



	/*int iKey = I_BitmapMgr.Load(L"../../data/bitmap/bitmap1.bmp");
	m_pSprite = I_BitmapMgr.GetPtr(iKey);

	iKey = I_BitmapMgr.Load(L"../../data/bitmap/Mask_bitmap1.bmp");
	m_pSpriteMask = I_BitmapMgr.GetPtr(iKey);
*/
	T_STR path = L"../../data/bitmap/";
	T_STR BitmapPath = path + bitmap;
	T_STR MaskPath = path + mask;
	m_iBitmapID = I_BitmapMgr.Load(BitmapPath.c_str());
	m_iMaskBitmapID = I_BitmapMgr.Load(MaskPath.c_str());

	m_SpriteListData.resize(iNumSprite);
	int iNumFrame = -1;
	for (int iSprite = 0; iSprite < iNumSprite; iSprite++)
	{
		_fgetts(buffer, _countof(buffer), fp);
		_stscanf_s(buffer, _T("%s%d%d%d%f%f%s%s"),
			temp, _countof(temp),
			&m_SpriteListData[iSprite].m_iNumFrame,
			&m_SpriteListData[iSprite].m_pos.x,
			&m_SpriteListData[iSprite].m_pos.y,
			&m_SpriteListData[iSprite].m_fTime,
			&m_SpriteListData[iSprite].m_fLifeTime,
			bitmap, _countof(bitmap),
			mask, _countof(mask));

		if (_tcscmp(bitmap, L"null"))
		{
			BitmapPath.clear();
			BitmapPath = path + bitmap;
			m_SpriteListData[iSprite].iBitmapID = I_BitmapMgr.Load(BitmapPath.c_str());
		}
		if (_tcscmp(mask, L"null"))
		{
			MaskPath.clear();
			MaskPath = path + bitmap;
			m_SpriteListData[iSprite].iMaskID = I_BitmapMgr.Load(MaskPath.c_str());
		}

		iNumFrame = m_SpriteListData[iSprite].m_iNumFrame;
		m_SpriteListData[iSprite].m_rtList.resize(iNumFrame);
		int iCount = -1;
		for (int iCnt = 0; iCnt < iNumFrame; iCnt++)
		{
			_fgetts(buffer, _countof(buffer), fp);
			_stscanf_s(buffer, _T("%d%d%d%d%d"),
				&iCount,
				&m_SpriteListData[iSprite].m_rtList[iCnt].left,
				&m_SpriteListData[iSprite].m_rtList[iCnt].top,
				&m_SpriteListData[iSprite].m_rtList[iCnt].right,
				&m_SpriteListData[iSprite].m_rtList[iCnt].bottom);
		}
	}
	fclose(fp);
}



bool sample::Init()
{
	GameDataLoad(L"Text.txt");
	
	m_pSprite = I_BitmapMgr.GetPtr(m_iBitmapID);
	assert(m_pSprite != nullptr);
	m_pSpriteMask = I_BitmapMgr.GetPtr(m_iMaskBitmapID);
	assert(m_pSpriteMask != nullptr);

	for (int iSprite = 0; iSprite < m_SpriteListData.size();
		iSprite++)
	{
		sySprite s0;
		s0.Init();
		s0.Set(m_SpriteListData[iSprite], m_iBitmapID, m_iMaskBitmapID);
		m_SpriteList.push_back(s0);
	}
	return true;
}



bool sample::Frame()
{

	static float fTimer = 0.0f;
	fTimer += g_fSecondPerFrame;

	for (int iSprite = 0; iSprite < m_SpriteList.size(); iSprite++)
	{
		m_SpriteList[iSprite].Frame();
	}
	//m_SpliteList[0].m_Pos = I_Input.m_MousePos;
	if (g_ActionInput.bLeftClick == KEY_PUSH)
	{
		int iRand = rand() % m_SpriteList.size();
		sySprite s0 = m_SpriteList[iRand];
		s0.m_iCurrentFrame = 0;
		s0.m_bDead = false;
		s0.m_info.m_fLifeTime = rand() % 3 ;
		s0.m_pos = I_Input.GetMousePos();
		s0.m_info.m_rtList = m_SpriteListData[iRand].m_rtList;
		m_SpriteListClick.push_back(s0);
	}
	for (auto& actor : m_SpriteListClick)
	{
		actor.Frame();
	}
	return true;
}

bool sample::Render()
{
	//m_SpriteList[m_iTimerSprite].Draw(MERGEPAINT);

	for (int i = 0; i < m_SpriteListClick.size(); i++)
	{
		m_SpriteListClick[i].Render();
	}
	//m_SpriteList[0].Render();

	//***
	//m_SpriteList[1].Render();
	///****
	for (std::vector<sySprite>::iterator iter =
		m_SpriteListClick.begin();
		iter != m_SpriteListClick.end();)
	{
		if ((*iter).m_bDead)
		{
			iter = m_SpriteListClick.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	return true;
}

bool sample::Release() {
	for (int i = 0; i < m_SpriteListClick.size(); i++)
	{
		m_SpriteListClick[i].Release();
	}
	m_SpriteList[0].Release();
	return true;

}


syCORE_RUN(siyeon spriteWindow,0,0,800,600);