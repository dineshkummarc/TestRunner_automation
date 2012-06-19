#pragma once
// 
// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// File:
//    cvResultsView.cpp 
// 
// Description:
//    Implements cvCResultsView which lists all test results
// 
// $Log: 
//  2    CliniVision1.1         11/16/99 5:01:23 PM  Doug C. Eveland Added DocJet
//       group comment
//  1    CliniVision1.0         11/9/99 11:22:50 AM  Doug C. Eveland 
// $
// $Revision: 2$
// $Date: 11/16/99 5:01:23 PM$
// $Author: Doug C. Eveland$
// 

#include "stdafx.h"
#include "cvCTestApp.h"
#include "cvCResultsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(cvCResultsView, CListView)

cvCResultsView::cvCResultsView()
{
}

cvCResultsView::~cvCResultsView()
{
}

BOOL cvCResultsView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= LVS_EDITLABELS | LVS_REPORT |
		LVS_SINGLESEL | LVS_NOCOLUMNHEADER ;//| LVS_EX_INFOTIP;

	return CListView::PreCreateWindow(cs);
}


BEGIN_MESSAGE_MAP(cvCResultsView, CListView)
	//{{AFX_MSG_MAP(cvCResultsView)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CLEAR_RESULTS, OnClearResults)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// cvCResultsView drawing

void cvCResultsView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
}

BOOL cvCResultsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void cvCResultsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void cvCResultsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

// {group:View Classes}
// 
// Name: 
// 	cvCResultsView::OnInitialUpdate
// 
// Description:
// 	Called by the framework once the view is created.
//  Configures the list view by adding a single column for reporting 
//  test results.
// 
void cvCResultsView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();

	// Get size of client area
	CRect rcClient;
	GetClientRect(&rcClient);

	// Insert Column
	LV_COLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	lvc.iSubItem = 0;
	lvc.pszText = _T("Results");
	lvc.cx = rcClient.Width();
	lvc.fmt = LVCFMT_LEFT;
	GetListCtrl().InsertColumn(0,&lvc);
}

/////////////////////////////////////////////////////////////////////////////
// cvCResultsView diagnostics

#ifdef _DEBUG
void cvCResultsView::AssertValid() const
{
	CView::AssertValid();
}

void cvCResultsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

// {group:View Classes}
// 
// Name: 
// 	cvCResultsView::OnContextMenu
// 
// Description:
// 	Called by the framework when the user presses the right mouse button to obtain a context menu
// 
// Arguments:
// 	pWnd - A pointer to the window in which the user clicked the right mouse button
// 
// 	point - The x,y coordinates of the mouse when the right mouse button was clicked.
// 
void cvCResultsView::OnContextMenu(CWnd* /*pWnd*/, CPoint point) 
{
   // load the popup menu to display   
	CMenu mnuTestSuite;
	mnuTestSuite.LoadMenu(IDR_RESULTS_MENU);
	CMenu* mnuPopup = mnuTestSuite.GetSubMenu(0);
   // call the helper function to setup this as a titled popup menu
	mnuPopup->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}

// {group:View Classes}
// 
// Name: 
// 	cvCResultsView::Log
// 
// Description:
// 	Adds a single row to the list control
// 
// Arguments:
// 	szMessage - A null-terminated string containing text to log
// 
void cvCResultsView::Log(LPCTSTR szMessage)
{
	int nItem = GetListCtrl().GetItemCount()+1;
	GetListCtrl().InsertItem(nItem,	szMessage);
}

// {group:View Classes}
// 
// Name: 
// 	cvCResultsView::OnClearResults
// 
// Description:
// 	Removes all rows from the list control
// 
void cvCResultsView::OnClearResults() 
{
	GetListCtrl().DeleteAllItems();
}
