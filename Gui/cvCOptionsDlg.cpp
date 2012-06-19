// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// Description:
// 	Implements cvCOptionsDlg - this dialog is used to query the user for 
//     configuration options.  Currently this dialog just asks for the
//     log file name.
// 
// $Log: 
//  2    CliniVision1.1         11/16/99 5:00:44 PM  Doug C. Eveland Added DocJet
//       group comment
//  1    CliniVision1.0         11/11/99 10:22:45 AM Doug C. Eveland 
// $
// $Revision: 2$
// $Date: 11/16/99 5:00:44 PM$
// $Author: Doug C. Eveland$
// 
#include "stdafx.h"
#include "cvCTestApp.h"
#include "cvCOptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// {group:Dialog Classes}
// 
// Name: 
// 	cvCOptionsDlg::cvCOptionsDlg
// 
// Description:
// 	cvCOptionsDlg Constructor - initializes the log file name string
// 
// Arguments:
// 	cvCOptionsDlg::IDD - The resource id of the dialog
// 
// 	pParent - The handle to the dialogs parent window
// 
cvCOptionsDlg::cvCOptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(cvCOptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(cvCOptionsDlg)
	m_strLogFileName = _T("");
	//}}AFX_DATA_INIT
}


void cvCOptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(cvCOptionsDlg)
	DDX_Text(pDX, IDC_TXT_LOGFILENAME, m_strLogFileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(cvCOptionsDlg, CDialog)
	//{{AFX_MSG_MAP(cvCOptionsDlg)
	ON_BN_CLICKED(IDC_BTN_SELECTFILE, OnBtnSelectFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// {group:Dialog Classes}
// 
// Name: 
// 	cvCOptionsDlg::OnBtnSelectFile
// 
// Description:
// 	Called by framework when the select file (...) button is pressed. 
//  The file selection dialog is displayed.  If the user presses the OK button 
//  on that dialog the selected file name is placed in the Log File Name edit control
// 
void cvCOptionsDlg::OnBtnSelectFile() 
{
	CFileDialog dlgFileSelection(TRUE);
	if (dlgFileSelection.DoModal() == IDOK)
	{
		m_strLogFileName = dlgFileSelection.GetPathName();
		UpdateData(FALSE);
	}
}
