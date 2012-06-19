// 
// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// File:
//    cvResultsView.h 
// 
// Description:
//    Declares cvCResultsView - used to display test results
// 
// $Log: 
//  3    CliniVision1.2         11/16/99 5:01:47 PM  Doug C. Eveland Added DocJet
//       group comment
//  2    CliniVision1.1         11/11/99 10:26:28 AM Doug C. Eveland Added class
//       header
//  1    CliniVision1.0         11/9/99 11:22:51 AM  Doug C. Eveland 
// $
// $Revision: 3$
// $Date: 11/16/99 5:01:47 PM$
// $Author: Doug C. Eveland$
// 
#pragma once

// {group:View Classes}
// 
// Description:
// 	Used to display the results from a test run
// 
// Author:
// 	Doug Eveland
// 
class cvCResultsView : public CListView
{
protected:
	cvCResultsView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(cvCResultsView)

// Attributes
public:

// Operations
public:
	void Log(LPCTSTR szMessage);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cvCResultsView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~cvCResultsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(cvCResultsView)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnClearResults();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP();

private:

};

