#pragma once
// 
// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// File:
//    ClinivisionTest.cpp 
// 
// Description:
//    Implements the CTestApp class (derived from CWinApp)
// 
// $Log: 
//  4    CliniVision1.3         11/16/99 5:02:31 PM  Doug C. Eveland Added
//       CAboutDlg class header.
//       Fixed call to SetRegistryKey to use resource string 
//  3    CliniVision1.2         11/12/99 5:39:12 PM  Doug C. Eveland Added a
//       default log file name
//  2    CliniVision1.1         11/11/99 10:27:01 AM Doug C. Eveland Added handler
//       for Tools/Options menu item
//  1    CliniVision1.0         11/9/99 11:22:52 AM  Doug C. Eveland 
// $
// $Revision: 4$
// $Date: 11/16/99 5:02:31 PM$
// $Author: Doug C. Eveland$
// 

#include "stdafx.h"
#include "cvCTestApp.h"

#include "cvCMainFrm.h"
#include "cvCInPlaceFrame.h"
#include "cvCTestDoc.h"
#include "cvCResultsView.h"
#include "cvCTestSuiteView.h"
#include "cvCOptionsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(cvCTestApp, CWinApp)
	//{{AFX_MSG_MAP(cvCTestApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_TOOLS_OPTIONS, OnToolsOptions)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()


cvCTestApp::cvCTestApp()
{
}

cvCTestApp theApp;

static const CLSID clsid =
{ 0x42c45bb6, 0x818d, 0x11d3, { 0xab, 0xbd, 0x0, 0x8, 0xc7, 0xfb, 0x28, 0x2 } };


BOOL cvCTestApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	SetRegistryKey(IDS_APPREGISTRY);

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register document templates

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(cvCTestDoc),
		RUNTIME_CLASS(cvCMainFrame),       // main SDI frame window
		RUNTIME_CLASS(cvCTestSuiteView));
	pDocTemplate->SetServerInfo(
		IDR_SRVR_EMBEDDED, IDR_SRVR_INPLACE,
		RUNTIME_CLASS(cvCInPlaceFrame));
	AddDocTemplate(pDocTemplate);
	m_server.ConnectTemplate(clsid, pDocTemplate, TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		COleTemplateServer::RegisterAll();

		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

	m_server.UpdateRegistry(OAT_INPLACE_SERVER);
	COleObjectFactory::UpdateRegistryAll();

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

// {group:Dialog Classes}
// 
// Description:
// 	Used to display a list of tests that support cvITest
// 
// Author:
// 	Doug Eveland
// 
class cvCAboutDlg : public CDialog
{
public:
	cvCAboutDlg();

// Dialog Data
	//{{AFX_DATA(cvCAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cvCAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(cvCAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

cvCAboutDlg::cvCAboutDlg() : CDialog(cvCAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(cvCAboutDlg)
	//}}AFX_DATA_INIT
}

void cvCAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(cvCAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(cvCAboutDlg, CDialog)
	//{{AFX_MSG_MAP(cvCAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void cvCTestApp::OnAppAbout()
{
	cvCAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// 
// Name: 
// 	cvCTestApp::OnToolsOptions
// 
// Description:
// 	Displays the Options dialog and saves the LogFileName to the registry
// 
void cvCTestApp::OnToolsOptions() 
{
	// Retrieve LogFileName from registry, if it exists
	CString strLogFileName;
	if (GetLogFileName(strLogFileName))
	{
		cvCOptionsDlg dlgOptions;
		dlgOptions.SetLogFileName(strLogFileName);

		// If user changes log file name then save it to registry
		if (dlgOptions.DoModal())
		{
			SaveLogFileName(dlgOptions.GetLogFileName());
		}
	}
}

// 
// Name: 
// 	cvCTestApp::GetLogFileName
// 
// Description:
// 	Retrieves the log file name from the registry
// 
// Arguments:
// 	strLogFileName - A reference to a string which will be used to return the log file name
// 
// Results:
// 	TRUE if no errors occured while retrieving the log file name
// 
bool cvCTestApp::GetLogFileName(CString& strLogFileName)
{
	bool bRet = true;

	CRegKey keyLogFileName;
	if (GetLogFileNameRegKey(keyLogFileName))
	{
		TCHAR szBuffer[256];
		ULONG ulSize = sizeof(szBuffer);
		if ((keyLogFileName.QueryValue(szBuffer, _T("LogFileName"), &ulSize) == ERROR_SUCCESS)
			&& (szBuffer[0] != _T('\0')))
		{
			strLogFileName = szBuffer;
		}
		else
		{
			CString strNewLogFileName(MAKEINTRESOURCE(IDS_LOGFILENAME));
			strLogFileName = strNewLogFileName;
		}
	}
	return bRet;
}

// 
// Name: 
// 	cvCTestApp::GetLogFileNameRegKey
// 
// Description:
// 	Retrieves the log file registry key from the registry
// 
// Arguments:
// 	keyLogFileName - A reference to a CRegKey which will be initialized to contain a handle to the log file name registry key
// 
// Results:
// 	TRUE is the key was obtained
// 
bool cvCTestApp::GetLogFileNameRegKey(CRegKey& keyLogFileName)
{
	bool bRet = true;

	// Get LogFileName Keys from resource
	CString strLogFileNameKey(MAKEINTRESOURCE(IDS_LOGFILENAMEKEY));
	CString strLogFileNameValue(MAKEINTRESOURCE(IDS_LOGFILENAMEVALUE));

	// Retrieve LogFileName from registry, if it exists
	DWORD dwRet = keyLogFileName.Create(HKEY_LOCAL_MACHINE, strLogFileNameKey);
	if (dwRet != ERROR_SUCCESS)
	{
		TCHAR szBuffer[256];
		ULONG ulSize = sizeof(szBuffer);
		::FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM, NULL, dwRet, 0, szBuffer, ulSize, NULL);
		AfxMessageBox(szBuffer);
		bRet = false;
	}
	return bRet;
}

// 
// Name: 
// 	cvCTestApp::SaveLogFileName
// 
// Description:
// 	Save the log file name (held in strLogFileName) to the registry
// 
// Arguments:
// 	strLogFileName - A reference to a string which contains the log file name
// 
bool cvCTestApp::SaveLogFileName(const CString& strLogFileName)
{
	bool bRet = false;

	CRegKey keyLogFileName;
	if (GetLogFileNameRegKey(keyLogFileName))
	{
		// Get LogFileName Keys from resource
		CString strLogFileNameKey(MAKEINTRESOURCE(IDS_LOGFILENAMEKEY));
		CString strLogFileNameValue(MAKEINTRESOURCE(IDS_LOGFILENAMEVALUE));

		DWORD dwRet = keyLogFileName.SetValue(strLogFileName, _T("LogFileName"));	
		if (dwRet == ERROR_SUCCESS)
		{
			bRet = true;
		}
	}
	return bRet;
}

