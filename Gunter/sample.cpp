#include "sample.h"
static float fTimer = 0.0f;
sample::sample()
{
	m_iTimerSprite = 0;
	m_iTimerSpriteMARIO = 0;
	//iSpriteNum = 0;
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
	I_Fsm.Add(STATE_STAND, EVENT_TIMER, STATE_MOVE);
	I_Fsm.Add(STATE_STAND, STATE_DEAD, STATE_DEAD);

	I_Fsm.Add(STATE_MOVE, EVENT_FINDTARGET, STATE_ATTACK);
	I_Fsm.Add(STATE_MOVE, STATE_DEAD, STATE_DEAD);
	I_Fsm.Add(STATE_MOVE, EVENT_FINDTARGET, STATE_STAND);

	I_Fsm.Add(STATE_ATTACK, EVENT_TIMER, STATE_STAND);
	I_Fsm.Add(STATE_ATTACK, STATE_DEAD, STATE_DEAD);
	I_Fsm.Add(STATE_ATTACK, EVENT_LOSTTARGET, STATE_MOVE);


	I_SoundMgr.Load(L"../../data/sound/mario.mp3");
	I_SoundMgr.Load(L"../../data/sound/Jump.wav");
	I_SoundMgr.Load(L"../../data/sound/Mariodies.wav");
	I_SoundMgr.Load(L"../../data/sound/Gameover.wav");
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
	

	iKeyNumber0 = I_ScriptManager.Load(L"Text.txt");
	iKeyNumber1 = I_ScriptManager.Load(L"mario.txt");
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
	current_gunter = &m_gunter[0];

	mario.Init();
	current_mario = mario.GetMario(1);

	
	return true;
}

void sample::setSpriteNum()
{
	sySound* pSoundJump = I_SoundMgr.GetPtr(1);

	static bool isFront = true;
	if (g_ActionInput.bAKey == KEY_HOLD)
	{
		isFront = false;
	}
	if (g_ActionInput.bDKey == KEY_HOLD)
	{
		isFront = true;
	}
	if (g_ActionInput.bWKey == KEY_PUSH)
	{
		pSoundJump->Play();
	}


	syPoint m_posinfo = current_gunter->m_info.InitPos;
	//앞 보는 펭귄
	if (isFront)
	{
		//jumping
		if (current_gunter->delY > -1 || g_ActionInput.bWKey == KEY_HOLD)
		{
			current_gunter = &m_gunter[STATE_JUMPINGFORWORD];
			current_gunter->SetPos(m_posinfo);
			m_iTimerSprite = 0;
			return;
		}
	
		else
		{	//walking
			if (g_ActionInput.bDKey == KEY_HOLD)
			{
				current_gunter = &m_gunter[STATE_FORWORD];
				current_gunter->SetPos(m_posinfo);
				m_iTimerSprite = 0;
			}

			//idle
			else
			{
				current_gunter = &m_gunter[STATE_IDLEFORWORD];
				current_gunter->SetPos(m_posinfo);
				m_iTimerSprite = 0;
				return;
			}
		}
	}
	//뒤 보는 펭귄
	else
	{
		//jumping
		if (current_gunter->delY > -1 || g_ActionInput.bWKey == KEY_HOLD)
		{
			current_gunter = &m_gunter[STATE_JUMPINGBACKWORD];
			current_gunter->SetPos(m_posinfo);
			m_iTimerSprite = 0;
		}
		else
		{
			//walking
			if (g_ActionInput.bAKey == KEY_HOLD)
			{
				current_gunter = &m_gunter[STATE_BACKWORD];
				current_gunter->SetPos(m_posinfo);
				m_iTimerSprite = 0;
			}
			//idle
			else
			{
				current_gunter = &m_gunter[STATE_IDLEBACKWORD];
				current_gunter->SetPos(m_posinfo);
				m_iTimerSprite = 0;
			}
		}
	}
}

void	sample::playerkill()
{	///////////////어케해야해!!!!!!!몰라!!!!!!!
	sySound* pSoundDie = I_SoundMgr.GetPtr(2);
	sySound* pGameOver = I_SoundMgr.GetPtr(3);
	if (syCollision::RectInRect(current_mario->m_rtColl, current_gunter->m_rtColl))
	{
		if (current_gunter->delY < 0 && current_gunter->delY>-1)
		{
			pSoundDie->Play();
	/*		current_mario.get()->m_bDead = true;*/

		}
		else
		{
			pGameOver->Play();
			/*current_gunter->m_bDead = true;*/
			//delete current_gunter;
			//current_gunter->Release();
	
		}
	}

}
bool   sample::Frame()
{
	sySound* pSound = I_SoundMgr.GetPtr(0);

	pSound->Play();
	setSpriteNum();
	//시간
	fTimer += g_fSecondPerFrame;
	if (fTimer >= 1.0f)
	{
		m_iTimerSprite++;
	}
	m_bk.Frame();

	current_gunter->Frame();
	tileColl(current_gunter);

	current_mario.get()->Frame();
	current_mario.get()->ProcessAI(current_gunter);
	tileColl(current_mario.get());

	//마리오와 부딪혔을 시
	playerkill();
	return true;
}
template <typename T>
void	sample::tileColl(T *gamecharacter)
{
	
	for (auto a : m_tiles)
	{
		RECT r;
		r.top = a.first->top;
		r.bottom = a.first->bottom;
		r.left = a.first->left;
		r.right = a.first->right;

		if (syCollision::RectInRect(gamecharacter->m_rtColl, r))
		{
			if (gamecharacter->m_rtColl.bottom >= r.top &&gamecharacter->delY < 0)//위에서 떨어지는 상황
			{
				gamecharacter->Set
				(syPoint(gamecharacter->getPos().x, r.top - (gamecharacter->m_rtDraw.bottom / 2) -1),
					gamecharacter->m_info.rtList[m_iTimerSprite%(gamecharacter->m_info.iNumFrame)],
					gamecharacter->getSpeed()
				);
			}
			else if (gamecharacter->m_rtColl.top <= r.bottom && gamecharacter->delY > 0) //밑에서 올라오는 상황
			{
				gamecharacter->setDel(gamecharacter->delX, -gamecharacter->delY);
				gamecharacter->Set
				(syPoint(gamecharacter->getPos().x, r.bottom + (gamecharacter->m_rtDraw.bottom / 2)+1 ),
					gamecharacter->m_info.rtList[m_iTimerSprite% (gamecharacter->m_info.iNumFrame)],
					gamecharacter->getSpeed()
				);
			}
			//옆구리로 들어올 때
			//오른쪽

			break;
		}
		else
		{
			gamecharacter->Set
			(syPoint(gamecharacter->getPos().x, gamecharacter->getPos().y),
				gamecharacter->m_info.rtList[m_iTimerSprite% (gamecharacter->m_info.iNumFrame)],
				gamecharacter->getSpeed());
		}

	}
}


bool   sample::Render()
{
	
	m_bk.Render();
	current_mario.get()->Render();
	current_gunter->Render();

	TCHAR m_csDebug[256];
	_stprintf_s(m_csDebug,
		L"delx = %1.5f dely = %1.5f  pos(%1.5f, %1.5f)",
		current_gunter->delX, current_gunter->delY,
		current_gunter->getPos().x, current_gunter->getPos().y);
	PrintText(syPoint(100, 100), m_csDebug, RGB(0, 0, 0));

	SetROP2(g_hOffScreenDC, R2_NOTXORPEN);

	for (auto &a : m_tiles)
	{
		Rectangle(g_hOffScreenDC,
			a.first->left,
			a.first->top,
			a.first->right,
			a.first->bottom);
	}


	int PrevMode = Rectangle(g_hOffScreenDC,
		current_gunter->m_rtColl.left,
		current_gunter->m_rtColl.top,
		current_gunter->m_rtColl.right,
		current_gunter->m_rtColl.bottom);

 Rectangle(g_hOffScreenDC,
	 current_mario.get()->m_rtColl.left,
	 current_mario.get()->m_rtColl.top,
	 current_mario.get()->m_rtColl.right,
	 current_mario.get()->m_rtColl.bottom);

	SetROP2(m_hOffScreenDC, PrevMode);

	return true;

}

bool   sample::Release()
{
	for (auto &a : m_gunter)
	{
		a.Release();
	}

	m_bk.Release();
	m_tiles.clear();
	return true;
}

syCORE_RUN(Gunter, 0, 0, 640, 480);