#include "Sample.h"
#include "XBitmapMgr.h"
#pragma comment(lib, "TTTTCoreLib.lib") 


Sample::Sample()
{
}


Sample::~Sample()
{
}

bool Sample::Init()
{
	m_bk.Init();
	m_bk.Load(L"../../data/bitmap/Loading800x600.bmp");
	syObjectInfo info;
	info.pos = syPoint(0, 0);
	RECT rt = { 0, 0, m_rtClient.right, m_rtClient.bottom };
	info.rt = rt;
	info.fSpeed = 0.0f;
	m_bk.Set(info);

	m_Hero.Init();
	m_Hero.Load(L"../../data/bitmap/bitmap1.bmp");
	info.pos = syPoint(100, 100);
	RECT rt1 = { 90, 1, 40, 60 };	info.rt = rt1;
	info.fSpeed = 100.0f;
	m_Hero.Set(info);

	m_npc.Init();
	m_npc.Load(L"../../data/bitmap/bitmap1.bmp");
	info.pos = syPoint(200, 200);
	RECT rt2 = { 46, 62, 67, 79 };	info.rt = rt2;
	info.fSpeed = 100.0f;
	m_npc.Set(info);

	for (int i = 0; i < 10; i++)
	{
		T_STR bmpName = L"../../data/bitmap/fill";
		bmpName += std::to_wstring(i);
		bmpName += L".bmp";
	
	}

	return true;
}

bool Sample::Render()
{
	m_bk.Render();
	m_Hero.Render();
	m_npc.Render();

	
	return true;
}


bool Sample::Frame()
{
	m_bk.Frame();
	m_Hero.Frame();
	m_npc.Frame();
	return true;
}

bool Sample::Release() {
	m_bk.Release();
	m_Hero.Release();
	m_npc.Release();
	return true;

}
TCORE_RUN(0, 0, 800, 600);