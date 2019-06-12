#include "sample.h"
enum objectState 
{
	STATE_FORWORD, STATE_BACKWORD, 
	STATE_LANDINGFORWORD, STATE_LANDINGBACKWORD, 
	STATE_JUMPINGFORWORD, STATE_JUMPINGBACKWORD,
	STATE_IDLEFORWORD, STATE_IDLEBACKWORD

};



sample::sample()
{

	m_iTimerSprite = 0;
	iSpriteNum = 0;
}


sample::~sample()
{
}

void	sample::drawtileRect()
{

	FILE* fp;
	char buffer[256];
	fopen_s(&fp, "background.txt", "r");
	if (fp == NULL)
	{
		//경고창 띄워야하는데
	}
	while (!feof(fp))
	{
		static int col = 0;
		fgets(buffer, sizeof(buffer), fp);
		char* tok = strtok(buffer, "\t");
		int row = 0;
		while (tok != NULL)
		{
			int tilevaule = atoi(tok);
			if (tilevaule != -1)
			{
				m_tiles.insert(pair<RECT*, int>(&bkRect[row][col], tilevaule));
			}
			row++;
			tok = strtok(NULL, "\t");

		}
		col++;
	}
	fclose(fp);

		for (int row = 0; row < 40; row++) 
	{
		for (int col = 0; col < 30; col++)
		{
			bkRect[row][col].top = 16 * col;
			bkRect[row][col].left = 16 * row;
			bkRect[row][col].bottom = bkRect[row][col].top+16;
			bkRect[row][col].right = bkRect[row][col].left+16;
			
		}
	}

}

bool	sample::Init()
{
	syObjectInfo info;
	info.m_pos = syPoint(m_rtClient.right / 2, m_rtClient.bottom / 2);
	RECT rt = { 0,0,m_rtClient.right, m_rtClient.bottom };
	info.rt = rt;
	info.fSpeed = 0.0f;
	m_bk.Init();
	m_bk.Load(L"../../data/bitmap/0612.bmp");
	m_bk.Set(info);
	m_bk.i_moveFlag = 0;
	drawtileRect();
	


	int iKeyNumber0 = I_ScriptManager.Load(L"Text.txt");
	int iKeyNumber1 = I_ScriptManager.Load(L"mario.txt");
	sySpriteData* pData = I_ScriptManager.GetPtr(iKeyNumber0);

	for (int iSprite = 0; iSprite < pData->m_SpriteListData.size(); iSprite++)
	{
		sySprite s0;
		s0.Init();
		s0.SetRTSize(0.5f);
		s0.Set(pData->m_SpriteListData[iSprite], pData->m_iBitmapID, pData->m_iMaskBitmapID);
		s0.m_info.bLoop = true;
		s0.m_bDead = false;
		s0.m_iCurrentFrame = 0;

		s0.setSpeed(80.0f);
		s0.i_moveFlag = 3;
		
		s0.SetPos(100,100);
		m_gunter.push_back(s0);
	}
	pData = I_ScriptManager.GetPtr(iKeyNumber1);
	
	for (int iSprite = 0; iSprite < pData->m_SpriteListData.size(); iSprite++)
	{
		syEnemy s1;
		s1.Init();
		s1.SetRTSize(0.6f);
		s1.Set(pData->m_SpriteListData[iSprite], pData->m_iBitmapID, pData->m_iMaskBitmapID);
		s1.m_info.bLoop = true;
		s1.m_bDead = false;
		s1.m_iCurrentFrame = 0;
		s1.SetRTSize(0.75f);
		s1.setSpeed(500.0f);
		s1.i_moveFlag = 1;
		s1.SetPos(500, 417);
		m_mario.push_back(s1);
	}

	return true;
}

void sample::setSpriteNum()
{
	static bool isFront = true;
	if (g_ActionInput.bAKey == KEY_HOLD)
	{
		isFront = false;
	}
	if (g_ActionInput.bDKey == KEY_HOLD)
	{
		isFront = true;
	}

	syPoint m_posinfo = m_gunter[iSpriteNum].getPos();
	//앞 보는 펭귄
	if (isFront)
	{
		//jumping
		if (m_gunter[iSpriteNum].delY > -1 || g_ActionInput.bWKey == KEY_HOLD)
		{
			iSpriteNum = STATE_JUMPINGFORWORD;
			m_gunter[iSpriteNum].SetPos(m_posinfo);
			m_iTimerSprite = 0;
			return;
		}
	
		else
		{	//walking
			//m_gunter[iSpriteNum].setDel(m_gunter[iSpriteNum].delX, 0);
			if (g_ActionInput.bDKey == KEY_HOLD)
			{
				iSpriteNum = STATE_FORWORD;
				m_gunter[iSpriteNum].SetPos(m_posinfo);
				m_iTimerSprite = 0;
			}

			//idle
			else
			{
				iSpriteNum = STATE_IDLEFORWORD;
				//m_gunter[iSpriteNum].setDel(0, 0);
				m_gunter[iSpriteNum].SetPos(m_posinfo);
				m_iTimerSprite = 0;
				return;
			}
		}
	}
	//뒤 보는 펭귄
	else
	{
		//jumping
		if (m_gunter[iSpriteNum].delY > -1 || g_ActionInput.bWKey == KEY_HOLD)
		{
			iSpriteNum = STATE_JUMPINGBACKWORD;
			m_gunter[iSpriteNum].SetPos(m_posinfo);
			m_iTimerSprite = 0;
		
		}
		
		else
		{
			//walking
			//m_gunter[iSpriteNum].setDel(m_gunter[iSpriteNum].delX, 0);
			if (g_ActionInput.bAKey == KEY_HOLD)
			{
				iSpriteNum = STATE_BACKWORD;
				m_gunter[iSpriteNum].SetPos(m_posinfo);
				m_iTimerSprite = 0;
			}

			//idle
			else
			{
				iSpriteNum = STATE_IDLEBACKWORD;
				//m_gunter[iSpriteNum].setDel(0, 0);
				m_gunter[iSpriteNum].SetPos(m_posinfo);
				m_iTimerSprite = 0;
				
			}
		}
	}
}

bool   sample::Frame()
{
	setSpriteNum();
	//시간
	static float fTimer = 0.0f;
	if (m_iTimerSprite == 0) fTimer = 0.0f;
	fTimer += g_fSecondPerFrame;
	if (fTimer >= 1.0f)
	{
		m_iTimerSprite++;
		if (m_iTimerSprite > m_gunter[iSpriteNum].m_info.iNumFrame-1)
		{
			m_iTimerSprite = 0;
			
		}
		fTimer = 0.0f;
	}
	//일단 프레임 걸고


	m_bk.Frame();
	m_gunter[iSpriteNum].Frame();

	for (auto a : m_tiles)
	{
		RECT r;
		r.top = a.first->top;
		r.bottom = a.first->bottom;
		r.left = a.first->left;
		r.right = a.first->right;


		if (syCollision::RectInRect(m_gunter[iSpriteNum].m_rtColl, r) )
		{
			if (m_gunter[iSpriteNum].m_rtColl.bottom >= r.top && m_gunter[iSpriteNum].delY < 0)//위에서 떨어지는 상황
			{
				m_gunter[iSpriteNum].Set
					(syPoint(m_gunter[iSpriteNum].getPos().x, r.top - (m_gunter[iSpriteNum].m_rtDraw.bottom / 2)-1 ),
					m_gunter[iSpriteNum].m_info.rtList[m_iTimerSprite],
					m_gunter[iSpriteNum].getSpeed()
					);
			}
			else if (m_gunter[iSpriteNum].m_rtColl.top <= r.bottom && m_gunter[iSpriteNum].delY > 0) //밑에서 올라오는 상황
			{
				m_gunter[iSpriteNum].setDel(m_gunter[iSpriteNum].delX, -m_gunter[iSpriteNum].delY);
				m_gunter[iSpriteNum].Set
					(syPoint(m_gunter[iSpriteNum].getPos().x, r.bottom + (m_gunter[iSpriteNum].m_rtDraw.bottom / 2)+1),
					m_gunter[iSpriteNum].m_info.rtList[m_iTimerSprite],
					m_gunter[iSpriteNum].getSpeed()
					);

			}
			//옆구리로 들어올 때
			
			break;
		}
		else
		{
			m_gunter[iSpriteNum].Set
			(syPoint(m_gunter[iSpriteNum].getPos().x, m_gunter[iSpriteNum].getPos().y),
				m_gunter[iSpriteNum].m_info.rtList[m_iTimerSprite],
				m_gunter[iSpriteNum].getSpeed());
		}

	}

	//	if (syCollision::RectInRect(m_gunter[iSpriteNum].m_rtColl, r) &&
	//		m_gunter[iSpriteNum].m_rtColl.bottom >= r.top &&
	//		m_gunter[iSpriteNum].delY<0)
	//	{
	//		m_gunter[iSpriteNum].Set
	//		(
	//			syPoint(m_gunter[iSpriteNum].getPos().x, r.top- m_gunter[iSpriteNum].m_rtDraw.bottom/2),
	//			m_gunter[iSpriteNum].m_info.rtList[m_iTimerSprite],
	//			m_gunter[iSpriteNum].getSpeed()
	//		);
	//		break;
	//	}
	//	else 
	//	{
	//		m_gunter[iSpriteNum].Set
	//		(syPoint(m_gunter[iSpriteNum].getPos().x, m_gunter[iSpriteNum].getPos().y),
	//			m_gunter[iSpriteNum].m_info.rtList[m_iTimerSprite], 
	//			m_gunter[iSpriteNum].getSpeed());
	//	}
	//	
	//}


	/*m_gunter[iSpriteNum].Set(syPoint(m_gunter[iSpriteNum].getPos().x, min(417-m_gunter[iSpriteNum].m_rtDraw.bottom/2,m_gunter[iSpriteNum].getPos().y)),
							m_gunter[iSpriteNum].m_info.rtList[m_iTimerSprite], m_gunter[iSpriteNum].getSpeed());*/
	 
	m_mario[0].Frame();
	m_mario[0].ProcessAI(&m_gunter[iSpriteNum]);
	//m_mario[0].Set
	//(syPoint(m_mario[0].getPos().x, min(417-m_mario[0].m_rtDraw.bottom/2, m_mario[0].getPos().y)),
	//	m_mario[0].m_info.rtList[0], 
	//	m_mario[0].getSpeed());

	
	return true;
}



bool   sample::Render()
{
	
	m_bk.Render();
	m_mario[0].Render();
	m_gunter[iSpriteNum].Render();

	//m_gunter[iSprite].Draw(417, 400, SRCAND);

//	m_mario[0].Draw(SRCCOPY);
	//m_gunter[iSpriteNum].Draw(SRCCOPY);

	TCHAR m_csDebug[256];
	_stprintf_s(m_csDebug,
		L"delx = %1.5f dely = %1.5f  pos(%1.5f, %1.5f)",
		m_gunter[iSpriteNum].delX, m_gunter[iSpriteNum].delY,
		m_gunter[iSpriteNum].getPos().x, m_gunter[iSpriteNum].getPos().y);
	PrintText(syPoint(100, 100), m_csDebug, RGB(0, 0, 0));

	SetROP2(g_hOffScreenDC, R2_NOTXORPEN);



	Rectangle(g_hOffScreenDC,
		m_gunter[iSpriteNum].m_rtColl.left,
		m_gunter[iSpriteNum].m_rtColl.top,
		m_gunter[iSpriteNum].m_rtColl.right,
		m_gunter[iSpriteNum].m_rtColl.bottom);

	//for (int row = 0; row < 40; row++)
	//{
	//	//for (int col = 0; col < 30; col++)
	//	//{
	//	//	int i = m_tiles[&bkRect[row][col]];
	//	//	if (i != -1)
	//	//	{
	//	//		Rectangle(g_hOffScreenDC,
	//	//			bkRect[row][col].left,
	//	//			bkRect[row][col].top,
	//	//			bkRect[row][col].left + bkRect[row][col].right,
	//	//			bkRect[row][col].top + bkRect[row][col].bottom);
	//	//	}

	//	//}

	//	

	//}
	for (auto &a : m_tiles)
	{
		Rectangle(g_hOffScreenDC,
			a.first->left,
			a.first->top,
			a.first->right,
			a.first->bottom);
	}

	int PrevMode = Rectangle(g_hOffScreenDC,
		m_mario[0].m_rtColl.left,
		m_mario[0].m_rtColl.top,
		m_mario[0].m_rtColl.right,
		m_mario[0].m_rtColl.bottom);

	SetROP2(m_hOffScreenDC, PrevMode);

	return true;

}

bool   sample::Release()
{
	for (int iSprite = 0; iSprite < m_gunter.size(); iSprite++)
	{
		m_gunter[iSprite].Release();
	}
	for (int iSprite = 0; iSprite < m_mario.size(); iSprite++)
	{
		m_mario[iSprite].Release();
	}

	m_bk.Release();
	m_tiles.clear();
	return true;
}

syCORE_RUN(Gunter, 0, 0, 640, 480);