// test_BusInit.h : main header file for the TEST_BUSINIT application
//

#if !defined(AFX_TEST_BUSINIT_H__633C6EF8_1DFC_4E84_84B8_3560F149C3D1__INCLUDED_)
#define AFX_TEST_BUSINIT_H__633C6EF8_1DFC_4E84_84B8_3560F149C3D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTest_BusInitApp:
// See test_BusInit.cpp for the implementation of this class
//

class CTest_BusInitApp : public CWinApp
{
public:
	CTest_BusInitApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest_BusInitApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTest_BusInitApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_BUSINIT_H__633C6EF8_1DFC_4E84_84B8_3560F149C3D1__INCLUDED_)
