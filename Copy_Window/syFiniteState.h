#pragma once
#include "syStd.h"
enum tState { STATE_MOVE, STATE_STAND, STATE_ATTACK, STATE_DEAD, STATE_COUNT };
enum tEvent { EVENT_TIMER, EVENY_DEAD, EVENT_FINDTARGET, EVENT_LOSTTARGET, EVENT_COUNT };
enum syStateMARIO
{
	SY_FORWORD,
	SY_IDLEFORWORD,
	SY_ATTACK,
	SY_DEAD,
	SY_COUNT
};

enum syStateGUNTER
{
	STATE_FORWORD,
	STATE_BACKWORD,
	STATE_LANDINGFORWORD,
	STATE_LANDINGBACKWORD,
	STATE_JUMPINGFORWORD,
	STATE_JUMPINGBACKWORD,
	STATE_IDLEFORWORD,
	STATE_IDLEBACKWORD
};


enum syEvent 
{
	SY_TILECOLL, SY_PLAYERCOLL, SY_FINDTARGET, SY_LOSTTARGET, SY_COUNTER
};


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

