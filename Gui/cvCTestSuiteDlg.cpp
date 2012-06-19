// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// Description:
// 	Implements cvCTestSuiteDlg which is used to display and edit 
//  information about a test suite or test.
// 
// $Log: 
//  3    CliniVision1.2         11/16/99 5:05:44 PM  Doug C. Eveland Added DocJet
//       group comment
//  2    CliniVision1.1         11/9/99 12:24:12 PM  Doug C. Eveland Added file and
//       function documentation
//  1    CliniVision1.0         11/4/99 6:16:49 PM   Doug C. Eveland 
// $
// $Revision: 3$
// $Date: 11/16/99 5:05:44 PM$
// $Author: Doug C. Eveland$
// 

#include "stdafx.h"
#include "cvCTestApp.h"
#include "cvCTestSuiteDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// {group:cvCTestSuiteDlg}
// 
// Name: 
// 	cvCTestSuiteDlg::cvCTestSuiteDlg
// 
// Description:
// 	Constructor for cvCTestSuiteDlg. Initializes private data for 
//  this class
// 
// Arguments:
// 	cvCTestSuiteDlg::IDD - Resource ID of dialog
// 
// 	pParent - The handle to this dialog's parent window
// 
cvCTestSuiteDlg::cvCTestSuiteDlg(CWnd* pParent /*=NULL*/)
	: CDialog(cvCTestSuiteDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(cvCTestSuiteDlg)
	m_strName = _T("");
	m_lNumTestRuns = 0;
	m_lRunCount = 0;
	//}}AFX_DATA_INIT
}


void cvCTestSuiteDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(cvCTestSuiteDlg)
	DDX_Text(pDX, IDC_TXT_NAME, m_strName);
	DDX_Text(pDX, IDC_TXT_NUMTESTRUNS, m_lNumTestRuns);
	DDV_MinMaxLong(pDX, m_lNumTestRuns, 0, 100000);
	DDX_Text(pDX, IDC_TXT_RUNCOUNT, m_lRunCount);
	DDV_MinMaxLong(pDX, m_lRunCount, 0, 100000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(cvCTestSuiteDlg, CDialog)
	//{{AFX_MSG_MAP(cvCTestSuiteDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// {group:cvCTestSuiteDlg}
// 
// Name: 
// 	cvCTestSuiteDlg::OnInitDialog
// 
// Description:
// 	Called by the framework when it is time to initialize the dialog.
//  Sets the dialogs caption based on the contents of the WindowText
//  attribute (set before DoModal is called).
// 
// Results:
// 	FALSE if the focus was moved to a different control; else TRUE
// 
// Remarks:
// 	Sets the caption (windowtext) to indicate whether a suite or test is being editied.
// 
BOOL cvCTestSuiteDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	if (m_strCaption.GetLength() > 0)
	{
		SetWindowText(m_strCaption);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


