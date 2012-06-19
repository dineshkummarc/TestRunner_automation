#pragma once
// 
// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// File:
//    cvTestSuiteView.h 
// 
// Description:
//    Declares the class cvCTestSuiteView which displays a test suite/test tree view
// 
// $Log: 
//  3    CliniVision1.2         11/16/99 5:07:35 PM  Doug C. Eveland Added DocJet
//       group comment
//       Added additional function to simplify a larger function based on a request
//       by Rollan during the code review.
//  2    CliniVision1.1         11/11/99 10:29:10 AM Doug C. Eveland Added class
//       header
//  1    CliniVision1.0         11/9/99 11:22:54 AM  Doug C. Eveland 
// $
// $Revision: 3$
// $Date: 11/16/99 5:07:35 PM$
// $Author: Doug C. Eveland$
// 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class cvCTestDoc;

// {group:View Classes}
// 
// Description:
// 	Used to display a tree of test suites and tests
// 
// Author:
// 	Doug Eveland
// 
class cvCTestSuiteView : public CTreeView
{
protected: // create from serialization only
	cvCTestSuiteView();
	DECLARE_DYNCREATE(cvCTestSuiteView)

    // declares the class object:    
	DECLARE_OLECREATE(cvCTestSuiteView)


	BEGIN_INTERFACE_PART(SupportTestOutputObj, cvISupportTestOutput)
        STDMETHOD(raw_LogResult)(BSTR bstrMessage);
		STDMETHOD(GetTypeInfoCount)
			(
				UINT FAR* pctinfo
			);
		STDMETHOD(GetTypeInfo) 
			(
				UINT itinfo,
				LCID lcid, ITypeInfo FAR* FAR* pptinfo
			);
		STDMETHOD(GetIDsOfNames)
			(
			REFIID riid, OLECHAR FAR* FAR* rgszNames, UINT cNames,
			LCID lcid, DISPID FAR* rgdispid
			);
		STDMETHOD(Invoke)
			(
			DISPID dispidMember, 
			REFIID riid, LCID lcid, WORD wFlags,
			DISPPARAMS FAR* pdispparams, VARIANT FAR* pvarResult,
			EXCEPINFO FAR* pexcepinfo, UINT FAR* puArgErr
			);

	END_INTERFACE_PART(SupportTestOutputObj)

// Attributes
public:
	cvCTestDoc* GetDocument();
	void DropNewTestOnTree(CPoint pt, cvCDragDropItem* pDragDropItem);
	bool CanDropAtPoint(CPoint& pt, HTREEITEM& htiDropTarget);
	void CreateXMLString(CString& strXML);
	BOOL StartAtTest(LPCTSTR szTestName);
	BOOL StartAtTest(HTREEITEM hItem);

// Enumerations
	enum CheckState{NOSTATE = 0, UNCHECKED, CHECKED, CHILD_CHECKED, SELF_AND_CHILD_CHECKED };
	enum CheckType{CHECK, UNCHECK, TOGGLE, REFRESH};

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cvCTestSuiteView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~cvCTestSuiteView() {}
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	HTREEITEM SetDropTarget(CPoint pt);
	void DropItemOnTree(CPoint point);
	HTREEITEM CopyItem(HTREEITEM hti,HTREEITEM htiNewParent = TVI_ROOT,HTREEITEM htiAfter = TVI_LAST);
	HTREEITEM CopyBranch(HTREEITEM hti,HTREEITEM htiNewParent,HTREEITEM htiAfter  = TVI_LAST);
	BOOL SetCheck(HTREEITEM hItem, CheckType nCheck);
	HTREEITEM InsertItem(LPCTSTR szItem, 
			HTREEITEM htiParent = TVI_ROOT, HTREEITEM htiAfter = TVI_LAST);
	HTREEITEM InsertItem(cvCDragDropItem* pDragDropItem, 
			HTREEITEM htiParent = TVI_ROOT, HTREEITEM htiAfter = TVI_LAST);
	void UpdateNodeText(HTREEITEM hItem);
	void ResetTests(HTREEITEM hParentItem, bool bResetParent = TRUE);
	void ExecuteTest(HTREEITEM hItem, CComPtr<cvITestOutput>& spITestOutput);
	void WriteToResultsView(LPCTSTR szMessage);
	void InsertXMLNode(const XML::IXMLElementPtr& spNode, HTREEITEM htiParent = TVI_ROOT);
	void InsertXMLNodeChildren(cvCDragDropItem *pDragDropItem,
			const XML::IXMLElementPtr& spNode, HTREEITEM htiParent = TVI_ROOT);
	void InternalCreateXMLString(HTREEITEM hti, CString& strXML);
	void LoadXMLDocument();
	HTREEITEM FindNodeByName(LPCTSTR szNodeName);
	void ExpandTree(HTREEITEM hItem);
	void YieldProcessing();
	void InitializeImages();

	// Resets the number of test execution failures that have been detected.
	void ResetNumFailures() {m_nNumFailures = 0;}		
	// Increments the number of test failures by 1
	void IncrementNumFailures() {m_nNumFailures++;}
	// Returns the number of test failures which have been detected.
	int GetNumFailures() {return m_nNumFailures;}

	// Resets the number of test execution passes (successes)
	void ResetNumPasses() {m_nNumPasses = 0;}		
	// Increments the number of test passes by 1
	void IncrementNumPasses() {m_nNumPasses++;}
	// Returns the number of test passes which have been detected.
	int GetNumPasses() {return m_nNumPasses;}


// Generated message map functions
protected:
	//{{AFX_MSG(cvCTestSuiteView)
	afx_msg void OnCancelEditSrvr();
	afx_msg void OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDblClk( UINT, CPoint );
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnNewSuite();
	afx_msg void OnRenameTestOrSuite();
	afx_msg void OnIncrementRunCount();
	afx_msg void OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDecrementRunCount();
	afx_msg void OnTestSuiteRunTests();
	afx_msg void OnUpdateTestSuiteRunTests(CCmdUI* pCmdUI);
	afx_msg void OnUpdateIncrementRunCount(CCmdUI* pCmdUI);
	afx_msg void OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnUpdateTestSuiteRunTest(CCmdUI* pCmdUI);
	afx_msg void OnViewCollapseTree();
	afx_msg void OnViewExpandTree();
	afx_msg void OnUpdateViewCollapseTree(CCmdUI* pCmdUI);
	afx_msg void OnUpdateViewExpandTree(CCmdUI* pCmdUI);
	afx_msg void OnFileStopTests();
	afx_msg void OnUpdateFileStopTests(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

private:
	CImageList* m_pDragImage;	// images for showing items while begin dragged
	CImageList m_StateImage;	// images used to indicate which tests are selected (checked)
	HTREEITEM m_htiDrag;		// Tree handle for item which is being dragged
	HTREEITEM m_htiDrop;		// Tree handle for item which is target of drop
	HTREEITEM m_htiOldDrop;		// Tree handle for item which was the target of a drop
	bool m_bDragging;			// TRUE is in the process of dragging 
	UINT m_idTimer;				// HANDLE for timer used to open tree view selections

	HCURSOR m_hDropCursor;		// handle to the ok-to-drop cursor
	HCURSOR m_hNoDropCursor;	// handle to the not-ok-to-drop cursor

	int m_nTestIdx;				// index in imagelist for test icon
	int m_nOpenFolderIdx;		// index in imagelist for open folder icon
	int m_nFolderIdx;			// index in imagelist for folder icon
	bool m_bInitialized;		// Initially false;  set to TRUE after OnInitialUpdate
	int m_nNumFailures;			// indicates the number of tests that failed
	int m_nNumPasses;			// indicates the number of tests that passed
	bool m_bExecutingTests;		// TRUE if in the process of executing tests

protected:
	DECLARE_INTERFACE_MAP()     // declare the nested classes
	DECLARE_DISPATCH_MAP()
};

#ifndef _DEBUG  // debug version in cvTestSuiteView.cpp
inline cvCTestDoc* cvCTestSuiteView::GetDocument()
   { return (cvCTestDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

