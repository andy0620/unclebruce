
// test_Pswitch.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ctest_PswitchApp:
// �йش����ʵ�֣������ test_Pswitch.cpp
//

class Ctest_PswitchApp : public CWinApp
{
public:
	Ctest_PswitchApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ctest_PswitchApp theApp;