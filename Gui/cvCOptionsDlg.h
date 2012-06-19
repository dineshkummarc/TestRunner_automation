#pragma once
// 
// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// File:
// 	cvCOptionsDlg.h 
// 
// Description:
// 	Declares the cvCOptionsDlg class
// 
// $Log: 
//  2    CliniVision1.1         11/16/99 5:01:09 PM  Doug C. Eveland Added DocJet
//       group comment
//       Added in-line function headers
//  1    CliniVision1.0         11/11/99 10:22:45 AM Doug C. Eveland 
// $
// $Revision: 2$
// $Date: 11/16/99 5:01:09 PM$
// $Author: Doug C. Eveland$
// 
#pragma once

// {group:Dialog Classes}
// 
// Description:
// 	A dialog used to edit CliniVisionTest options
// 
// Author:
// 	Doug Eveland
// 
class cvCOptionsDlg : public CDialog
{
// Construction
public:
	cvCOptionsDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(cvCOptionsDlg)
	enum { IDD = IDD_OPTIONS };
	CString	m_strLogFileName;		// the name of the log file used by the app
	//}}AFX_DATA

	// {group:Dialog Classes}
	// 
	// Name: 
	// 	SetLogFileName
	// 
	// Description:
	// 	Sets the log file name
	// 
	// Arguments:
	// 	szLogFileName - The name of the log file 
	// 
	void SetLogFileName(LPCTSTR szLogFileName) {m_strLogFileName = szLogFileName;}

	// {group:Dialog Classes}
	// 
	// Name: 
	// 	GetLogFileName
	// 
	// Description:
	// 	Retrieves the log file name property
	// 
	// Results:
	// 	The log file name
	// 
	const CString& GetLogFileName() {return m_strLogFileName;}

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionsDlg)
	afx_msg void OnBtnSelectFile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

