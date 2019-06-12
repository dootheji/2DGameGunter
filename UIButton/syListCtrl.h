#pragma once
#include "syButtonCtrl.h"

class syListCtrl : public syButtonCtrl
{
public:
	syListCtrl();
	virtual ~syListCtrl();
public:
	std::vector<syButtonCtrl> m_btnList;
public:
	bool Release();
};

