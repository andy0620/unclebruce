// single_move_.h : main header file for the SINGLE_MOVE_ application
//

#if !defined(AFX_SINGLE_MOVE__H__F8D492A7_0D33_48FA_BC09_D00855F5BDF4__INCLUDED_)
#define AFX_SINGLE_MOVE__H__F8D492A7_0D33_48FA_BC09_D00855F5BDF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSingle_move_App:
// See single_move_.cpp for the implementation of this class
//

class CSingle_move_App : public CWinApp
{
public:
	CSingle_move_App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSingle_move_App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSingle_move_App)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SINGLE_MOVE__H__F8D492A7_0D33_48FA_BC09_D00855F5BDF4__INCLUDED_)
