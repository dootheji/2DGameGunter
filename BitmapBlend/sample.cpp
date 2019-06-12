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
	info.m_pos = syPoint(m_rtClient.right/2, m_rtClient.bottom/2);
	RECT rt = { 0,0,m_rtClient.right, m_rtClient.bottom };
	info.rt = rt;
	info.fSpeed = 0.0f;
	m_bk2.Init();
	m_bk2.Load(L"../../data/bitmap/ocean.bmp");
	m_bk2.Set(info);
	m_bk2.i_moveFlag = 0;

	info.fSpeed = 500.0f;
	rt = { 751,0,32, 32 };
	info.rt = rt;
	info.fSpeed = 500.0f;
	m_fish.Init();
	m_fish.Load(L"../../data/bitmap/acnl.bmp");
	m_fish.Set(info);
	m_fish.i_moveFlag = 3;
	m_fish.delX = 1;
	m_fish.delY = 1;


	info.fSpeed = 500.0f;
	rt = { 0,0,32, 32 };
	info.m_pos = syPoint(300, 400);
	info.rt = rt;
	info.fSpeed = 10.0f;
	m_fish2.Init();
	m_fish2.Load(L"../../data/bitmap/acnl.bmp");
	m_fish2.Set(info);
	m_fish2.i_moveFlag = 1;

	for(int i=0; i<10; i++)
	{
		info.fSpeed = rand()%300+100;
		rt = { 32,32,32, 32 };
		info.m_pos = syPoint(rand()%800, rand()%600);
		info.rt = rt;
		m_fish3[i].Init();
		m_fish3[i].Load(L"../../data/bitmap/acnl.bmp");
		m_fish3[i].Set(info);
		m_fish3[i].setDel((float)(rand() % 5 + 1), (float)(rand() % 5 + 1));
		m_fish3[i].i_moveFlag = 1;
	}
	return true;
}
bool   sample::Frame() 
{

	static float temX = ((rand() % 10)+1) ;
	static float temY = ((rand() % 10)+1);


	if (m_fish2.getPos().x > m_rtClient.right - m_fish2.m_rtObj.right)
	{
		temX = -((rand() % 4) + 1) ;
		temY = (-(rand() % 8) + 4) ;
	}
	if (m_fish2.getPos().x < 0)
	{
		temX = ((rand() % 4) + 1);
		temY = (-(rand() % 8) + 4) ;
	}
	if (m_fish2.getPos().y > m_rtClient.bottom - m_fish2.m_rtObj.bottom)
	{
		temX = ((rand() % 4) + 1) ;
		temY = -((rand() % 8) + 4) ;
	}
	if (m_fish2.getPos().y < 0)
	{
		temX = ((rand() % 4) + 1);
		temY = ((rand() % 8) + 4) ;
	}
	m_fish2.SetPos(m_fish2.getPos().x * g_fSecondPerFrame* m_fish2.getSpeed() + temX , m_fish2.getPos().y + temY * g_fSecondPerFrame* m_fish2.getSpeed());



	for (int i = 0; i < 10; i++) 
	{
		// 사각형 안에 있도록
		if (m_fish3[i].getPos().x > m_rtClient.right - m_fish3[i].m_rtObj.right)
		{
			int x = -((rand() % 4) );
			int y = (-(rand() % 8) );
			m_fish3[i].setDel(x, y);
			m_fish3[i].SetPos(m_fish3[i].getPos().x + m_fish3[i].delX * g_fSecondPerFrame * m_fish3[i].getSpeed(), m_fish3[i].getPos().y + m_fish3[i].delY * g_fSecondPerFrame * m_fish3[i].getSpeed());
		
		
		}
		if (m_fish3[i].getPos().x < 0)
		{
			int x = ((rand() % 4) );
			int y = (-(rand() % 8) );
			m_fish3[i].setDel(x, y);
			m_fish3[i].SetPos(m_fish3[i].getPos().x + m_fish3[i].delX * g_fSecondPerFrame * m_fish3[i].getSpeed(), m_fish3[i].getPos().y + m_fish3[i].delY * g_fSecondPerFrame * m_fish3[i].getSpeed());
			
			

		}
		if (m_fish3[i].getPos().y > m_rtClient.bottom - m_fish3[i].m_rtObj.bottom)
		{
			int x = ((rand() % 4) );
			int y = -((rand() % 8) );
			m_fish3[i].setDel(x, y);
			m_fish3[i].SetPos(m_fish3[i].getPos().x + m_fish3[i].delX * g_fSecondPerFrame * m_fish3[i].getSpeed(), m_fish3[i].getPos().y + m_fish3[i].delY * g_fSecondPerFrame * m_fish3[i].getSpeed());
		
		
		}
		if (m_fish3[i].getPos().y < 0)
		{
			int x = ((rand() % 4) );
			int y = ((rand() % 8) );
			m_fish3[i].setDel(x, y);
			m_fish3[i].SetPos(m_fish3[i].getPos().x + m_fish3[i].delX * g_fSecondPerFrame * m_fish3[i].getSpeed(), m_fish3[i].getPos().y + m_fish3[i].delY * g_fSecondPerFrame * m_fish3[i].getSpeed());
		
			
		}

		//범위안
		if (abs(m_fish.getPos().x - m_fish3[i].getPos().x) < 100
			&& abs(m_fish.getPos().y - m_fish3[i].getPos().y) < 100)
		{
			if(m_fish3[i].i_moveFlag ==1)
			{
				m_fish3[i].setDel((m_fish.getPos().x - m_fish3[i].getPos().x), (m_fish.getPos().y - m_fish3[i].getPos().y));
			
				if (syCollision::RectInRect(m_fish3[i].m_rtColl, m_fish.m_rtColl))
				{
					m_fish3[i].setDel(-(m_fish.getPos().x - m_fish3[i].getPos().x), -(m_fish.getPos().y - m_fish3[i].getPos().y));
					if (m_fish3[i].i_moveFlag != 2)
					{
						m_fish3[i].i_moveFlag = 2;
						m_fish.SetRTSize(2);
					}

				}

				for (int j = 0; j < 10; j++)
				{
					if (i != j && syCollision::RectInRect(m_fish3[i].m_rtColl, m_fish3[j].m_rtColl))
					{
						int x = -(rand() % 8) + 3;
						int y = -(rand() % 8) + 3;
						m_fish3[i].setDel(x, y);
						if (m_fish3[i].i_moveFlag !=2)
						{
							m_fish3[i].i_moveFlag = 0;
						}

						//break;
					}
				}
			}

		}
		//범위밖
		else 
		{
			if (m_fish3[i].i_moveFlag == 2)
			{
				m_fish3[i].i_moveFlag = 1;
				m_fish.SetRTSize(0.5);

			}
			if (m_fish3[i].i_moveFlag == 0)
			{
				m_fish3[i].i_moveFlag = 1;
				int x = -(rand() % 8) + 3;
				int y = -(rand() % 8) + 3;
				m_fish3[i].setDel(x, y);
			}

			for (int j = 0; j < 10; j++)
			{

				if (i != j && syCollision::RectInRect(m_fish3[i].m_rtColl, m_fish3[j].m_rtColl))
				{

					m_fish3[i].setDel((m_fish3[i].getPos().x - m_fish3[j].getPos().x), (m_fish3[i].getPos().y - m_fish3[j].getPos().y));

					//break;
				}
			}
		}

		m_fish3[i].SetPos(m_fish3[i].getPos().x + m_fish3[i].i_moveFlag* m_fish3[i].delX * g_fSecondPerFrame * m_fish3[i].getSpeed(), m_fish3[i].getPos().y + m_fish3[i].i_moveFlag* m_fish3[i].delY  * g_fSecondPerFrame * m_fish3[i].getSpeed());
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

		//m_fish.m_irtSize = 1;

	SetROP2(g_hOffScreenDC, R2_NOTXORPEN);
	for (int iCnt = 0; iCnt < 10; iCnt++)
	{
		Rectangle(g_hOffScreenDC,
			m_fish3[iCnt].m_rtColl.left,
			m_fish3[iCnt].m_rtColl.top,
			m_fish3[iCnt].m_rtColl.right,
			m_fish3[iCnt].m_rtColl.bottom);
	}
	int PrevMode = Rectangle(g_hOffScreenDC,
		m_fish.m_rtColl.left,
		m_fish.m_rtColl.top,
		m_fish.m_rtColl.right,
		m_fish.m_rtColl.bottom);

	SetROP2(m_hOffScreenDC, PrevMode);
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