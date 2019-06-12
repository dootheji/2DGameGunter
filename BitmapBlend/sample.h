#pragma once
#include "syCore.h"
#include "syPlayer.h"
#include "syCollision.h"

class sample : public syCore 
{
	syPlayer m_fish;
	syObject m_fish2;

	
	syObject m_fish3[10];


	syObject m_bk2;
	



public:
	bool   Init();
	bool   Frame();
	bool   Render();
	bool   Release();

	//bool   AlphaBlendRender();

public:
	sample();
	~sample();
};

