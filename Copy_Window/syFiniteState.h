#pragma once
#include "syStd.h"
enum tState { STATE_STAND, STATE_MOVE, STATE_ATTACK, STATE_COUNT };
enum tEvent { EVENT_TIMER, EVENT_FINDTARGET, EVENT_LOSTTARGET, EVENT_COUNT };
class syFsm;
class syFiniteState
{
	friend class syFsm;
public:
	syFiniteState();
	virtual ~syFiniteState();

public:
	typedef std::map<DWORD, DWORD>::iterator TItor;
	std::map<DWORD, DWORD>  m_List;
public:
	INT GetPtr(DWORD dwKey);
};

