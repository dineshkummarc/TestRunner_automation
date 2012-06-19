#pragma once
// 
// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// File:
//    cvTestView.h 
// 
// Description:
//    Declares cvCTestView which is uses to list all objects which support ITest
// 
// $Log: 
//  3    CliniVision1.2         11/16/99 5:08:24 PM  Doug C. Eveland Added DocJet
//       group comment
//  2    CliniVision1.1         11/11/99 10:30:14 AM Doug C. Eveland Added class
//       header.
//       Removed function documentation from header file
//  1    CliniVision1.0         11/9/99 11:22:55 AM  Doug C. Eveland 
// $
// $Revision: 3$
// $Date: 11/16/99 5:08:24 PM$
// $Author: Doug C. Eveland$
// 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class cvCTestDoc;

// {group:View Classes}
// 
// Description:
// 	Used to display a list of tests that support cvITest
// 
// Author:
// 	Doug Eveland
// 
class cvCTestView : public CListView
{
protected: // create from serialization only

	cvCTestView();

	DECLARE_DYNCREATE(cvCTestView)

// Attributes
public:
	cvCTestDoc* GetDocument();


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cvCTestView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:

	virtual ~cvCTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void DropItemOnList();
	cvCDragDropItem* GetDragDropItemFromIndex(int nIndex);

	int InsertItem(int nItem, _bstr_t bstrName,
					  _bstr_t bstrDescription, CLSID clsid);

	// Generated message map functions
protected:
	//{{AFX_MSG(cvCTestView)
	afx_msg void OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CImageList m_ImageList;		// list of images used by this view
	CImageList* m_pDragImage;	// image used to illustrate drag operation
	BOOL m_bDragging;			// TRUE if drag is occuring; else FALSE
	int m_nDragIndex;			// 0-based index of the list item begin dragged
	int m_nDropIndex;			// 0-based index of the list item after which the
								// item will be dropped

	HCURSOR m_hDropCursor;		// cursor indicating drop is allowed
	HCURSOR m_hNoDropCursor;	// cursor indicating no drop is allowed

	CWnd* m_pDropWnd;			// pointer to window which is the drop target
	CPoint m_ptDropPoint;		// location in window where item is dropped
	bool m_bInitialized;		// Initially false; set to true after OnInitialUpdate
};

#ifndef _DEBUG  // debug version in cvTestView.cpp
inline cvCTestDoc* cvCTestView::GetDocument()
   { return (cvCTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


