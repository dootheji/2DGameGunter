#include "sample.h"
#include "syScriptManager.h"
#include "syBitmapMgr.h"

sample::sample()
{

}


sample::~sample()
{
}

bool	sample::Init()
{
	syObjectInfo info;
	info.m_pos = syPoint(0, 0);
	RECT rt = { 0,0,m_rtClient.right, m_rtClient.bottom };
	info.rt = rt;
	info.fSpeed = 0.0f;
	m_bk2.Init();
	m_bk2.Load(L"../../data/bitmap/ocean.bmp");
	m_bk2.Set(info);

	info.fSpeed = 500.0f;
	rt = { 751,0,32, 32 };
	info.m_pos = syPoint(200,500);
	info.rt = rt;
	m_fish.Init();
	m_fish.Load(L"../../data/bitmap/acnl.bmp");
	m_fish.Set(info);

	info.fSpeed = 10.0f;
	rt = { 0,0,32, 32 };
	info.m_pos = syPoint(300, 400);
	info.rt = rt;
	info.fSpeed = 10.0f;
	m_fish2.Init();
	m_fish2.Load(L"../../data/bitmap/acnl.bmp");
	m_fish2.Set(info);

	for (int i = 0; i < 10; i++)
	{
		info.fSpeed = rand() % 30 + 1;
		rt = { 32,32,32, 32 };
		info.m_pos = syPoint(rand() % 800, rand() % 600);
		info.rt = rt;
		m_fish3[i].Init();
		m_fish3[i].Load(L"../../data/bitmap/acnl.bmp");
		m_fish3[i].Set(info);
	}
	return true;
}
bool   sample::Frame()
{

	static float temX = ((rand() % 10) + 1) * g_fSecondPerFrame;
	static float temY = ((rand() % 10) + 1) * g_fSecondPerFrame;


	if (m_fish2.getPos().x > m_rtClient.right - m_fish2.m_rtObj.right)
	{
		temX = -((rand() % 4) + 1) * g_fSecondPerFrame* m_fish2.getSpeed();
		temY = (-(rand() % 8) + 4) * g_fSecondPerFrame* m_fish2.getSpeed();
	}
	if (m_fish2.getPos().x < 0)
	{
		temX = ((rand() % 4) + 1) * g_fSecondPerFrame* m_fish2.getSpeed();
		temY = (-(rand() % 8) + 4) * g_fSecondPerFrame* m_fish2.getSpeed();
	}
	if (m_fish2.getPos().y > m_rtClient.bottom - m_fish2.m_rtObj.bottom)
	{
		temX = ((rand() % 4) + 1) * g_fSecondPerFrame* m_fish2.getSpeed();
		temY = -((rand() % 8) + 4) * g_fSecondPerFrame* m_fish2.getSpeed();
	}
	if (m_fish2.getPos().y < 0)
	{
		temX = ((rand() % 4) + 1) * g_fSecondPerFrame* m_fish2.getSpeed();
		temY = (-(rand() % 8) + 4) * g_fSecondPerFrame* m_fish2.getSpeed();
	}

	//if (m_fish2.getPos().x < m_rtClient.left ||
	//	m_fish2.getPos().x > m_rtClient.right )
	//{
	//	temX = -temX;
	//}
	//if (m_fish2.getPos().y < m_rtClient.top ||
	//	m_fish2.getPos().y > m_rtClient.bottom)
	//{
	//	temY = -temY;
	//}


	m_fish2.SetPos(m_fish2.getPos().x + temX, m_fish2.getPos().y + temY);
	static float temX2 = ((rand() % 10) + 1) * g_fSecondPerFrame;
	static float temY2 = ((rand() % 10) + 1) * g_fSecondPerFrame;

	for (int i = 0; i < 10; i++)
	{
		temX2 = ((rand() % 5) + 1) * g_fSecondPerFrame;// *m_fish3[i].getSpeed();
		temY2 = ((rand() % 5) + 1) * g_fSecondPerFrame;// *m_fish3[i].getSpeed();


		if (abs(m_fish.getPos().x - m_fish3[i].getPos().x) < m_fish.m_rtObj.right
			&& abs(m_fish.getPos().y - m_fish3[i].getPos().y) < m_fish.m_rtObj.left)
		{
			temX2 *= ((m_fish.getPos().x - m_fish3[i].getPos().x)*(m_fish.getPos().x - m_fish3[i].getPos().x))
				/ (m_fish.getPos().x * m_fish.getPos().x + m_fish3[i].getPos().x * m_fish3[i].getPos().x)
				;// *g_fSecondPerFrame * m_fish3[i].getSpeed();
			temY2 *= (m_fish.getPos().y - m_fish3[i].getPos().y)*(m_fish.getPos().y - m_fish3[i].getPos().y)
				/ (m_fish.getPos().y *m_fish.getPos().y + m_fish3[i].getPos().y*m_fish3[i].getPos().y)
				;// *g_fSecondPerFrame * m_fish3[i].getSpeed();
		}



		m_fish3[i].SetPos(m_fish3[i].getPos().x + temX2 * m_fish3[i].getSpeed(), m_fish3[i].getPos().y + temY2 * m_fish3[i].getSpeed());



		if (abs(m_fish.getPos().x - m_fish3[i].getPos().x) < m_fish.m_rtObj.right
			&& abs(m_fish.getPos().y - m_fish3[i].getPos().y) < m_fish.m_rtObj.bottom)
		{
			m_fish.m_sizeFactor = 2;
		}

		m_fish3[i].Frame();
	}


	m_bk2.Frame();
	m_fish.Frame();

	m_fish2.Frame();


	return true;
}



bool   sample::Render()
{

	m_bk2.Render();
	m_fish.Render();
	m_fish2.Render();
	for (int i = 0; i < 10; i++)
	{
		m_fish3[i].Render();
	}

	m_fish.m_sizeFactor = 1;
	return true;

}
bool   sample::Release()
{
	m_fish.Release();
	m_bk2.Release();
	m_fish2.Release();
	for (int i = 0; i < 10; i++)
	{
		m_fish3[i].Release();
	}
	return true;
}

syCORE_RUN(BitmapBlend, 0, 0, 800, 600);