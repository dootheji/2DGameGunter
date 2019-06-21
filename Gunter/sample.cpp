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
	I_Fsm.Add(ACTION_STAND, SYSTATE_TILECOLL, ACTION_MOVE);
	I_Fsm.Add(ACTION_STAND, SYSTATE_DEAD, ACTION_DEAD);

	I_Fsm.Add(ACTION_MOVE, SYSTATE_FINDTARGET, ACTION_ATTACK);
	I_Fsm.Add(ACTION_MOVE, SYSTATE_DEAD, ACTION_DEAD);
	I_Fsm.Add(ACTION_MOVE, SYSTATE_TILECOLL, ACTION_STAND);

	I_Fsm.Add(ACTION_ATTACK, SYSTATE_FINDTARGET, ACTION_STAND);
	I_Fsm.Add(ACTION_ATTACK, SYSTATE_DEAD, ACTION_DEAD);
	I_Fsm.Add(ACTION_ATTACK, SYSTATE_TILECOLL, ACTION_MOVE);


	I_SoundMgr.Load(L"../../data/sound/mario.mp3");
	I_SoundMgr.Load(L"../../data/sound/Jump.wav");
	I_SoundMgr.Load(L"../../data/sound/Mariodies.wav");
	I_SoundMgr.Load(L"../../data/sound/Gameover.mp3");
	I_SoundMgr.Load(L"../../data/sound/win.wav");
	syObjectInfo info;
	info.m_pos = syPoint(m_rtClient.right / 2, m_rtClient.bottom / 2);
	RECT rt = { 0,0,m_rtClient.right, m_rtClient.bottom };
	info.rt = rt;
	info.fSpeed = 0.0f;
	m_bk.Init();
	m_bk.Load(L"../../data/bitmap/0612.bmp");
	m_bk.Set(info);
	m_bk.i_moveFlag = 0;

	
	rt = { 0,0,300, 50 };
	info.rt = rt;
	info.fSpeed = 0.0f;
	m_gameover.Init();
	m_gameover.Load(L"../../data/bitmap/Gunter_gameover.bmp");
	m_gameover.Set(info);
	m_gameover.i_moveFlag = 0;

	
	rt = { 0,0,300, 100 };
	info.rt = rt;
	info.fSpeed = 0.0f;
	m_win.Init();
	m_win.Load(L"../../data/bitmap/gunter_win.bmp");
	m_win.Set(info);
	m_win.i_moveFlag = 0;



	drawtileRect();
	

	iKeyNumber0 = I_ScriptManager.Load(L"Text.txt");
	iKeyNumber1 = I_ScriptManager.Load(L"mario.txt");
	sySpriteData* pData = I_ScriptManager.GetPtr(iKeyNumber0);

	for (int iSprite = 0; iSprite < pData->m_SpriteListData.size(); iSprite++)
	{
		sySprite s0;
		s0.Init();
		s0.SetRTSize(0.5f);		


		s0.m_info.bLoop = true;
		s0.m_bDead = false;
		s0.m_iCurrentFrame = 0;

		s0.setSpeed(80.0f);
		s0.i_moveFlag = 3;
		s0.Set(pData->m_SpriteListData[iSprite], pData->m_iBitmapID, pData->m_iMaskBitmapID);
		s0.SetPos(100, 100);
		m_gunter.push_back(s0);
	}
	current_gunter = &m_gunter[0];


	
	shared_ptr<syEnemy> data = make_shared<syEnemy>();
	data.get()->Init();
	current_mario.push_back(data);
	shared_ptr<syEnemy> data2 = make_shared<syEnemy>();
	data2.get()->Init();
	current_mario.push_back(data2);
	shared_ptr<syEnemy> data3 = make_shared<syEnemy>();
	data3.get()->Init();
	current_mario.push_back(data3);
	/*current_mario = (data.get()->m_current);*/
	//current_mario.get()->m_dwCurrentState = 0;
	//current_mario = make_shared<syEnemy>();
	//current_mario.get()->Init();
	

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
	float   tem_delX = current_gunter->delX;
	float   tem_delY = current_gunter->delY;
	//앞 보는 펭귄
	if (isFront)
	{
		//jumping
		if (istileColl(current_gunter) == false ||current_gunter->delY > -1 || g_ActionInput.bWKey == KEY_HOLD)
		{
			current_gunter = &m_gunter[STATE_JUMPINGFORWORD];
			current_gunter->SetPos(m_posinfo);
			current_gunter->setDel(tem_delX, tem_delY);
			m_iTimerSprite = 0;
			return;
		}
	
		else
		{	//walking
			if (g_ActionInput.bDKey == KEY_HOLD)
			{
				current_gunter = &m_gunter[STATE_FORWORD];
				current_gunter->SetPos(m_posinfo);
				current_gunter->setDel(tem_delX, tem_delY);
				m_iTimerSprite = 0;
			}

			//idle
			else
			{
				current_gunter = &m_gunter[STATE_IDLEFORWORD];
				current_gunter->SetPos(m_posinfo);
				current_gunter->setDel(tem_delX, tem_delY);
				m_iTimerSprite = 0;
				return;
			}
		}
	}
	//뒤 보는 펭귄
	else
	{
		//jumping
		if (istileColl(current_gunter) == false || current_gunter->delY > -1 || g_ActionInput.bWKey == KEY_HOLD)
		{
			current_gunter = &m_gunter[STATE_JUMPINGBACKWORD];
			current_gunter->SetPos(m_posinfo);
			current_gunter->setDel(tem_delX, tem_delY);
			m_iTimerSprite = 0;
		}
		else
		{
			//walking
			if (g_ActionInput.bAKey == KEY_HOLD)
			{
				current_gunter = &m_gunter[STATE_BACKWORD];
				current_gunter->SetPos(m_posinfo);
				current_gunter->setDel(tem_delX, tem_delY);
				m_iTimerSprite = 0;
			}
			//idle
			else
			{
				current_gunter = &m_gunter[STATE_IDLEBACKWORD];
				current_gunter->SetPos(m_posinfo);
				current_gunter->setDel(tem_delX, tem_delY);
				m_iTimerSprite = 0;
			}
		}
	}
}


bool   sample::Frame()
{
	sySound* pSound = I_SoundMgr.GetPtr(0);
	pSound->Play();
	if (current_gunter->m_bDead == true)
	{
		sySound* pDie = I_SoundMgr.GetPtr(3);
		pSound->Stop();
		pDie->Play();
		m_gameover.Frame();
		for (auto a : m_gunter)
		{
			a.m_bDead = true;
		}
		return true;
	}


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

	for (auto a : current_mario) 
	{
		if (a.get()->m_current->m_bDead)
		{
			std::vector<shared_ptr<syEnemy>>::iterator it;
			for (it = current_mario.begin(); it != current_mario.end();)
			{
				if ((*it) == a)
				{
					it = current_mario.erase(it);
					sySound* pDieMario = I_SoundMgr.GetPtr(2);
					pDieMario->Play();

				}

				else
				{
					it++;
				}

			}
			break;
		}
		if (a.get()->m_current->m_rtColl.left <1)
		{
			a.get()->isFront = true;
		}
		if (a.get()->m_current->m_rtColl.right >639)
		{
			a.get()->isFront = false;
		}
		a.get()->Frame();
		tileColl(a);
		a.get()->ProcessAI(current_gunter);


	

	}

	if (current_gunter->m_bDead == true)
	{
		m_gameover.Frame();
		for (auto a : m_gunter)
		{
			a.m_bDead = true;
		}
		return true;
	}

	if (current_mario.size() == 0)
	{
		pSound->Stop();
		sySound* pWin = I_SoundMgr.GetPtr(4);
		pWin->SetMode(FMOD_LOOP_OFF);
		pWin->Play();
		m_win.Frame();
	}
	return true;
}

template <typename T>
bool	sample::istileColl(T *gamecharacter)
{
	for (auto a : m_tiles)
	{
		RECT r;
		r.top = a.first->top-1;
		r.bottom = a.first->bottom+1;
		r.left = a.first->left-1;
		r.right = a.first->right+1;

		if (syCollision::RectInRect(gamecharacter->m_rtColl, r))
		{
			return true;
		}
	}
	return false;
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
		float rheight = (r.top - r.bottom) / 2;
		if (syCollision::RectInRect(gamecharacter->m_rtColl, r))
		{
			if (gamecharacter->m_rtColl.bottom >= r.top + rheight &&gamecharacter->delY < 0)//위에서 떨어지는 상황
			{
				gamecharacter->Set
				(syPoint(gamecharacter->getPos().x, r.top - (gamecharacter->m_rtDraw.bottom / 2) ),
					gamecharacter->m_info.rtList[m_iTimerSprite%(gamecharacter->m_info.iNumFrame)],
					gamecharacter->getSpeed()
				);
	
			}
			
			else if (gamecharacter->m_rtColl.top <= r.bottom - rheight && gamecharacter->delY > 0) //밑에서 올라오는 상황
			{
				gamecharacter->setDel(gamecharacter->delX, -gamecharacter->delY);
				gamecharacter->Set
				(syPoint(gamecharacter->getPos().x, r.bottom + (gamecharacter->m_rtDraw.bottom / 2)),
					gamecharacter->m_info.rtList[m_iTimerSprite% (gamecharacter->m_info.iNumFrame)],
					gamecharacter->getSpeed()
				);
				break;
			}			
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
template <typename T>
void	sample::tileColl(shared_ptr<T> game)
{
	shared_ptr<T> gamecharacter = game.get()->m_current;
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
				(syPoint(gamecharacter->getPos().x, r.top - (gamecharacter->m_rtDraw.bottom / 2) - 1),
					gamecharacter->m_info.rtList[m_iTimerSprite % (gamecharacter->m_info.iNumFrame)],
					gamecharacter->getSpeed()
				);
			}
			else if (gamecharacter->m_rtColl.top <= r.bottom && gamecharacter->delY > 0) //밑에서 올라오는 상황
			{
				gamecharacter->setDel(gamecharacter->delX, -gamecharacter->delY);
				gamecharacter->Set
				(syPoint(gamecharacter->getPos().x, r.bottom + (gamecharacter->m_rtDraw.bottom / 2) + 1),
					gamecharacter->m_info.rtList[m_iTimerSprite % (gamecharacter->m_info.iNumFrame)],
					gamecharacter->getSpeed()
				);
			}
			//옆구리로 들어올 때
			//오른쪽
			game->isStand = true;
			break;
		}
		else
		{
			gamecharacter->Set
			(syPoint(gamecharacter->getPos().x, gamecharacter->getPos().y),
				gamecharacter->m_info.rtList[m_iTimerSprite % (gamecharacter->m_info.iNumFrame)],
				gamecharacter->getSpeed());

			game->isStand = false;
		}

	}
}

bool   sample::Render()
{
	if (current_gunter->m_bDead == true)
	{
		m_gameover.Render();
		return true;
	}
	m_bk.Render();
	for (auto aa : current_mario)
	{
		aa.get()->m_current->Render();
	}


	current_gunter->Render();


	
	if (current_mario.size() == 0)
	{
		BLENDFUNCTION bf;
		bf.AlphaFormat = AC_SRC_ALPHA;
		bf.BlendFlags = 0;
		bf.BlendOp = AC_SRC_OVER;
		bf.SourceConstantAlpha = 255;
		AlphaBlend(g_hOffScreenDC,
			320 - m_win.m_rtObj.right/2, 240 - m_win.m_rtObj.bottom,
			m_win.m_rtObj.right, m_win.m_rtObj.bottom,
			m_win.GetBitmap()->m_hMemDC,
			m_win.m_rtObj.left, m_win.m_rtObj.top,
			m_win.m_rtObj.right, m_win.m_rtObj.bottom,
			bf);
		return true;
	}
	return true;

}

bool   sample::Release()
{
	for (auto &a : m_gunter)
	{
		a.Release();
	}

	m_bk.Release();
	m_gameover.Release();

	m_tiles.clear();
	current_gunter->Release();

	return true;
}

syCORE_RUN(Gunter, 0, 0, 640, 480);