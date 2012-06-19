#pragma once
// 
// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// File:
//    ClinivisionTest.h 
// 
// Description:
//    
// 
// $Log: 
//  3    CliniVision1.2         11/16/99 5:02:43 PM  Doug C. Eveland Added DocJet
//       group comment
//  2    CliniVision1.1         11/11/99 10:27:17 AM Doug C. Eveland Added handler
//       for Tools/Options menu item
//  1    CliniVision1.0         11/9/99 11:22:52 AM  Doug C. Eveland 
// $
// $Revision: 3$
// $Date: 11/16/99 5:02:43 PM$
// $Author: Doug C. Eveland$
// 
// ClinivisionTest.h : main header file for the CLINIVISIONTEST application
//

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#import "..\TestCore\TestCore.tlb" no_namespace


// {group:Framework Classes}
// 
// Description:
// 	The main CWinApp derived class
// 
// Author:
// 	Doug Eveland
// 
class cvCTestApp : public CWinApp
{
public:
	cvCTestApp();

	bool GetLogFileName(CString& strLogFileName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cvCTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
	//{{AFX_MSG(cvCTestApp)
	afx_msg void OnAppAbout();
	afx_msg void OnToolsOptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	bool SaveLogFileName(const CString& strLogFileName);
	bool GetLogFileNameRegKey(CRegKey& keyLogFileName);
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

