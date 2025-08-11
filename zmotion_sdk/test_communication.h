// test_communication.h : main header file for the TEST_COMMUNICATION application
//

#if !defined(AFX_TEST_COMMUNICATION_H__E817AD4E_745E_4C8B_8A96_DB328C285C80__INCLUDED_)
#define AFX_TEST_COMMUNICATION_H__E817AD4E_745E_4C8B_8A96_DB328C285C80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTest_communicationApp:
// See test_communication.cpp for the implementation of this class
//

class CTest_communicationApp : public CWinApp
{
public:
	CTest_communicationApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTest_communicationApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTest_communicationApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEST_COMMUNICATION_H__E817AD4E_745E_4C8B_8A96_DB328C285C80__INCLUDED_)
