// test_multiMove.h : main header file for the TEST_MULTIMOVE application
//

#if !defined(AFX_TEST_MULTIMOVE_H__08BE3EEA_5422_42A1_A9C8_DEECAACDF728__INCLUDED_)
#define AFX_TEST_MULTIMOVE_H__08BE3EEA_5422_42A1_A9C8_DEECAACDF728__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTest_multiMoveApp:
// See test_multiMove.cpp for the implementation of this class
//

class CTest_multiMoveApp : public CWinApp
{
public:
	CTest_multiMoveApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest_multiMoveApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTest_multiMoveApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_MULTIMOVE_H__08BE3EEA_5422_42A1_A9C8_DEECAACDF728__INCLUDED_)
