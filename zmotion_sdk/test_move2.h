// test_move2.h : main header file for the TEST_MOVE2 application
//

#if !defined(AFX_TEST_MOVE2_H__C5C9C434_4BB1_43B0_BCF5_EC66CBA514B0__INCLUDED_)
#define AFX_TEST_MOVE2_H__C5C9C434_4BB1_43B0_BCF5_EC66CBA514B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTest_move2App:
// See test_move2.cpp for the implementation of this class
//

class CTest_move2App : public CWinApp
{
public:
	CTest_move2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest_move2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTest_move2App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_MOVE2_H__C5C9C434_4BB1_43B0_BCF5_EC66CBA514B0__INCLUDED_)
