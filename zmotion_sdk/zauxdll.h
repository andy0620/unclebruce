// zauxdll.h : main header file for the ZAUXDLL DLL
//

#if !defined(AFX_ZAUXDLL_H__DECC6374_2E30_4D7C_A371_E6F3AC49DAD1__INCLUDED_)
#define AFX_ZAUXDLL_H__DECC6374_2E30_4D7C_A371_E6F3AC49DAD1__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CZauxdllApp
// See zauxdll.cpp for the implementation of this class
//

class CZauxdllApp : public CWinApp
{
public:
	CZauxdllApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZauxdllApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CZauxdllApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZAUXDLL_H__DECC6374_2E30_4D7C_A371_E6F3AC49DAD1__INCLUDED_)
