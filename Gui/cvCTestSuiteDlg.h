#pragma once
// 
// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// File:
// 	cvCTestSuiteDlg.h 
// 
// Description:
// 	Declares the cvCTestSuiteDlg class which is reponsible for querying the user
//  for the name and runcount properties of a suite or test item.
// 
// $Log: 
//  4    CliniVision1.3         11/16/99 5:06:12 PM  Doug C. Eveland Added DocJet
//       group comment
//       Added additional in-line function definitions
//  3    CliniVision1.2         11/11/99 10:28:20 AM Doug C. Eveland Added class
//       header
//  2    CliniVision1.1         11/9/99 12:24:31 PM  Doug C. Eveland Added
//       documentation
//  1    CliniVision1.0         11/4/99 6:16:49 PM   Doug C. Eveland 
// $
// $Revision: 4$
// $Date: 11/16/99 5:06:12 PM$
// $Author: Doug C. Eveland$
// 

// {group:Dialog Classes}
// 
// Description:
// 	A dialog used to edit information about a test or test suite
// 
// Author:
// 	Doug Eveland
// 
class cvCTestSuiteDlg : public CDialog
{
// Construction
public:
	cvCTestSuiteDlg(CWnd* pParent = NULL);   // standard constructor

// Properties

	// retrieves the name of a test or test suite
	const CString& GetName() {return m_strName;}
	// retrieves the run counr
	const long& GetRunCount() {return m_lRunCount;}
	// sets the name of a test or test sutie
	void SetName(LPCTSTR szName) {m_strName = szName;}
	// sets the RunCount property
	void SetRunCount(long lRunCount) {m_lRunCount = lRunCount;}
	// set the caption of the dialog 
	// (used to indicate if a test or test suite is to be editied)
	// m_szCaption is used for setting the caption, instead of 
	// SetWindowText because the caller must set the caption 
	// before the window exists.
	void SetCaption(LPCTSTR szCaption) {m_strCaption = szCaption;}

	//{{AFX_DATA(cvCTestSuiteDlg)
	enum { IDD = IDD_TESTSUITE };
	CString	m_strName;					// Name of test
	long	m_lNumTestRuns;				// Number of times test has been run
	long	m_lRunCount;				// Number of times test should be run.
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cvCTestSuiteDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(cvCTestSuiteDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	// {secret}
	CString m_strCaption;	// indicates title of dialog
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.
