
// test_Pitchset.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Ctest_PitchsetApp:
// �йش����ʵ�֣������ test_Pitchset.cpp
//

class Ctest_PitchsetApp : public CWinApp
{
public:
	Ctest_PitchsetApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Ctest_PitchsetApp theApp;