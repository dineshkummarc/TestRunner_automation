#pragma once
// 
// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// File:
//    MainFrm.cpp 
// 
// Description:
//    Implements cvcvCMainFrame
// 
// $Log: 
//  3    CliniVision1.2         11/16/99 5:00:09 PM  Doug C. Eveland Added DocJet
//       group comments
//  2    CliniVision1.1         11/11/99 10:25:53 AM Doug C. Eveland Added function
//       headers
//  1    CliniVision1.0         11/9/99 11:22:50 AM  Doug C. Eveland 
// $
// $Revision: 3$
// $Date: 11/16/99 5:00:09 PM$
// $Author: Doug C. Eveland$
// 
#include "stdafx.h"
#include "cvCTestApp.h"

#include "cvCMainFrm.h"
#include "cvCTestView.h"
#include "cvCTestSuiteView.h"
#include "cvCResultsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNCREATE(cvCMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(cvCMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(cvCMainFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

cvCMainFrame::cvCMainFrame()
{
}

cvCMainFrame::~cvCMainFrame()
{
}

// {group:cvCMainFrame}
// 
// Name: 
// 	cvCMainFrame::OnCreate
// 
// Description:
// 	Called by the frameword during the window creation process.  
//  The tool and status bars are created.
// 
// Arguments:
// 	lpCreateStruct - A pointer to a structure used during window creation
// 
// Results:
// 	-1 if an error occurs; else 0
// 
int cvCMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndDlgBar.Create(this, IDR_MAINFRAME, 
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return -1;		// fail to create
	}

	if (!m_wndReBar.Create(this) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndDlgBar.SetBarStyle(m_wndDlgBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	return 0;
}

// {group:cvCMainFrame}
// 
// Name: 
// 	cvCMainFrame::OnCreateClient
// 
// Description:
// 	Called during the creation of the frame's client window.  The splitter
//  windows are created here.
// 
// Arguments:
// 	/*lpcs*/ - A pointer to the window creation structure
// 
// 	pContext - A pointer to the window creation context
// 
// Results:
// 	TRUE if the client is created; else FALSE
// 
BOOL cvCMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	CRect rectClient;
	GetClientRect(&rectClient);

	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	// make left pane 1/4 width of client
	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(cvCTestView), CSize(200, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}
	else
	{
		if (!m_wndRightSplitter.CreateStatic(&m_wndSplitter, 2, 1,
				WS_CHILD | WS_VISIBLE | WS_BORDER, 
				m_wndSplitter.IdFromRowCol(0, 1)))
		{
			m_wndSplitter.DestroyWindow();
			return FALSE;
		}
		if (!m_wndRightSplitter.CreateView(0, 0, RUNTIME_CLASS(cvCTestSuiteView), CSize(100, (long)(rectClient.Height() * .5)), pContext) ||
			!m_wndRightSplitter.CreateView(1, 0, RUNTIME_CLASS(cvCResultsView), CSize(100, 100), pContext))
		{
			m_wndRightSplitter.DestroyWindow();
			m_wndSplitter.DestroyWindow();
			return FALSE;
		}
	}

	return TRUE;
}

BOOL cvCMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// cvCMainFrame diagnostics

#ifdef _DEBUG
void cvCMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void cvCMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG



