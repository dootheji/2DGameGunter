#pragma once
#include "sySprite.h"
#include "syCollision.h"
#include "syStd.h"

#define WM_UICONTRLMSG  (WM_USER+1)
#define WM_BUTTONCLICK  (WM_USER+2)
#define WM_GAMESTART	(WM_USER+3)

class syUIComponent : public sySprite
{
public:
	syUIComponent();
	~syUIComponent();
public:
	T_STR      m_csName;
	int        m_iIndexType;
	sySprite*	m_pOwner;
	std::vector<syUIComponent*>	  m_ctrlList;
public:
	LRESULT		MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	virtual syUIComponent* Clone() { return nullptr; };
	void Add(syUIComponent* pComponent);
	void Draw(DWORD dwMode) override {};
	//void   Remove(syUIComponent* pComponent);
	//syUIComponent* GetChild(int iIndex);
public:
	syVertex				m_Vertex[16];
	syUIComponent*			m_rtDrawList[9];
	void					SetRect(int iRect,
		syVertex Start,
		syVertex Middle,
		syVertex End,
		int iBitmapID, int iMaskBitmapID);
	void	Gen(syRect rt, syRect rtSrc, int iBitmapID, int iMaskBitmapID);
};

