// test_handmove.h : main header file for the TEST_HANDMOVE application
//

#if !defined(AFX_TEST_HANDMOVE_H__A3D34877_0E89_46A7_888D_B0672B63DC3A__INCLUDED_)
#define AFX_TEST_HANDMOVE_H__A3D34877_0E89_46A7_888D_B0672B63DC3A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTest_handmoveApp:
// See test_handmove.cpp for the implementation of this class
//

class CTest_handmoveApp : public CWinApp
{
public:
	CTest_handmoveApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest_handmoveApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTest_handmoveApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_HANDMOVE_H__A3D34877_0E89_46A7_888D_B0672B63DC3A__INCLUDED_)
