#pragma once
#include "xBitmap.h"
class XBitmapMgr : public sySingleton<XBitmapMgr>
{

	friend class sySingleton<XBitmapMgr>;
	typedef std::map<int, xBitmap*>::iterator ITOR;
	// ������ �����̳� < Ű, �� >
	std::map<int, xBitmap*>   m_List;
	int			m_iNumBitmap;
public:
	int					m_iNumXBitmap;
public:
	bool		Init();
	bool		Frame();
	bool		Render();
	bool		Release();
	int         Load(T_STR filepath);
	xBitmap*		GetPtr(int iKey);
	bool		Delete(int iKey);
public:
	XBitmapMgr();
	~XBitmapMgr();
};


#define I_BitmapMgr XBitmapMgr::GetInstance()
