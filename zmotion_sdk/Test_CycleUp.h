
// Test_CycleUp.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTest_CycleUpApp:
// �йش����ʵ�֣������ Test_CycleUp.cpp
//

class CTest_CycleUpApp : public CWinApp
{
public:
	CTest_CycleUpApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTest_CycleUpApp theApp;