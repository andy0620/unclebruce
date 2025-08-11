// test_move.h : main header file for the TEST_MOVE application
//

#if !defined(AFX_TEST_MOVE_H__3BC29914_9C30_44BB_81C9_38AE33D6824C__INCLUDED_)
#define AFX_TEST_MOVE_H__3BC29914_9C30_44BB_81C9_38AE33D6824C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTest_moveApp:
// See test_move.cpp for the implementation of this class
//

class CTest_moveApp : public CWinApp
{
public:
	CTest_moveApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest_moveApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTest_moveApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_MOVE_H__3BC29914_9C30_44BB_81C9_38AE33D6824C__INCLUDED_)
