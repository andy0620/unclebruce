
// test_UserSub.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ctest_UserSubApp:
// �йش����ʵ�֣������ test_UserSub.cpp
//

class Ctest_UserSubApp : public CWinApp
{
public:
	Ctest_UserSubApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ctest_UserSubApp theApp;