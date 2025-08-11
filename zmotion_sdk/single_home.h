// single_home.h : main header file for the SINGLE_HOME application
//

#if !defined(AFX_SINGLE_HOME_H__535ED0F9_A63E_441E_AE63_C505077731EC__INCLUDED_)
#define AFX_SINGLE_HOME_H__535ED0F9_A63E_441E_AE63_C505077731EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSingle_homeApp:
// See single_home.cpp for the implementation of this class
//

class CSingle_homeApp : public CWinApp
{
public:
	CSingle_homeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSingle_homeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSingle_homeApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SINGLE_HOME_H__535ED0F9_A63E_441E_AE63_C505077731EC__INCLUDED_)
