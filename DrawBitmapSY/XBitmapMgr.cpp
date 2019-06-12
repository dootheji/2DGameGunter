#include "XBitmapMgr.h"



XBitmapMgr::XBitmapMgr()
{
	m_iNumBitmap = 0;
}


XBitmapMgr::~XBitmapMgr()
{
	Release();
}


bool		XBitmapMgr::Init()
{

	return true;
}

bool		XBitmapMgr::Frame()
{
	for (ITOR itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		xBitmap* pBitmap = (*itor).second;
		pBitmap->Frame();
	}

	return true;
}

bool		XBitmapMgr::Render()
{
	for (ITOR itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		xBitmap* pBitmap = (*itor).second;
		pBitmap->Render();
	}
	return true;
}

bool		XBitmapMgr::Release()
{
	for (ITOR itor = m_List.begin();itor != m_List.end();)
	{
		xBitmap* pBitmap = (*itor).second;
		pBitmap->Release();
		delete pBitmap;
		itor = m_List.erase(itor);
	}
	
	m_List.clear();


	return true;
}

xBitmap*		XBitmapMgr::GetPtr(int iKey)
{
	ITOR itor = m_List.find(iKey);

	if (itor != m_List.end())
	{	
		xBitmap* pData = (*itor).second;
		return pData;
	}
	return nullptr;
}

bool		XBitmapMgr::Delete(int iKey)
{
	ITOR itor = m_List.find(iKey);
	if (itor != m_List.end())
	{
		xBitmap* pData = (*itor).second;
		pData->Release();
		delete pData;
		m_List.erase(itor);
		return true;
	}
	return false;
}




int        XBitmapMgr::Load(T_STR filepath)
{
	//path split
	if (filepath.empty()) return -1;

	TCHAR Drive[MAX_PATH] = { 0, };
	TCHAR Dir[MAX_PATH] = { 0, };
	TCHAR Name[MAX_PATH] = { 0, };
	TCHAR Ext[MAX_PATH] = { 0, };
	_tsplitpath_s(filepath.c_str(), Drive, Dir, Name, Ext);

	T_STR filename = Name;
	filename += Ext;

	T_STR path = Drive;
	path += Dir;

	// 중복제거
	for (ITOR itor = m_List.begin(); itor != m_List.end();itor++)
	{
		xBitmap* pData = (*itor).second;
		if (pData->m_szName == filepath)
		{
			return pData->m_iIndex;
		}
	}
	xBitmap* pData = new xBitmap;
	if (pData->Load(filepath) == false)
	{
		delete pData;
		return -1;
	}
	pData->m_szName = filename;
	pData->m_szPath = path;
	pData->m_iIndex = m_iNumBitmap++;
	m_List.insert(make_pair(pData->m_iIndex, pData));
	return pData->m_iIndex;
}

