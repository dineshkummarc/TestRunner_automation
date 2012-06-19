// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// Description:
// 	Implements cvCInPlaceFrame
// 
// $Log: 
//  1    CliniVision1.0         11/9/99 11:22:49 AM  Doug C. Eveland 
// $
// $Revision: 1$
// $Date: 11/9/99 11:22:49 AM$
// $Author: Doug C. Eveland$
// 

#include "stdafx.h"
#include "cvCTestApp.h"

#include "cvCInPlaceFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(cvCInPlaceFrame, COleIPFrameWnd)

BEGIN_MESSAGE_MAP(cvCInPlaceFrame, COleIPFrameWnd)
	//{{AFX_MSG_MAP(cvCInPlaceFrame)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

cvCInPlaceFrame::cvCInPlaceFrame()
{
}

cvCInPlaceFrame::~cvCInPlaceFrame()
{
}

int cvCInPlaceFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (COleIPFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndResizeBar.Create(this))
	{
		TRACE0("Failed to create resize bar\n");
		return -1;      // fail to create
	}

	m_dropTarget.Register(this);

	return 0;
}

BOOL cvCInPlaceFrame::OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc)
{
	UNREFERENCED_PARAMETER(pWndDoc);

	m_wndToolBar.SetOwner(this);

	if (!m_wndToolBar.CreateEx(pWndFrame) ||
		!m_wndToolBar.LoadToolBar(IDR_SRVR_INPLACE))
	{
		TRACE0("Failed to create toolbar\n");
		return FALSE;
	}

	m_wndDlgBar.SetOwner(this);

	if (!m_wndDlgBar.Create(pWndFrame, IDR_SRVR_INPLACE,
		CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
	{
		TRACE0("Failed to create dialogbar\n");
		return FALSE;
	}

	m_wndReBar.SetOwner(this);

	if (!m_wndReBar.Create(pWndFrame) ||
		!m_wndReBar.AddBar(&m_wndToolBar) ||
		!m_wndReBar.AddBar(&m_wndDlgBar))
	{
		TRACE0("Failed to create rebar\n");
		return FALSE;
	}

	m_wndToolBar.SetBarStyle(m_wndToolBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndDlgBar.SetBarStyle(m_wndDlgBar.GetBarStyle() |
		CBRS_TOOLTIPS | CBRS_FLYBY);

	return TRUE;
}

BOOL cvCInPlaceFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	return COleIPFrameWnd::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// cvCInPlaceFrame diagnostics

#ifdef _DEBUG
void cvCInPlaceFrame::AssertValid() const
{
	COleIPFrameWnd::AssertValid();
}

void cvCInPlaceFrame::Dump(CDumpContext& dc) const
{
	COleIPFrameWnd::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// cvCInPlaceFrame commands
