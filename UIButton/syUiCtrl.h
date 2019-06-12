#pragma once
#include "sySprite.h"
class syUiCtrl : public sySprite
{
public:
	syUiCtrl();
	virtual ~syUiCtrl();

public:
	sySprite*		m_pOwner;


};

