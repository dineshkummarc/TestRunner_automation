// cvInPlaceFrame.h : interface of the cvCInPlaceFrame class
//

#if !defined(AFX_CVINPLACEFRAME_H__42C45BCA_818D_11D3_ABBD_0008C7FB2802__INCLUDED_)
#define AFX_CVINPLACEFRAME_H__42C45BCA_818D_11D3_ABBD_0008C7FB2802__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class cvCInPlaceFrame : public COleIPFrameWnd
{
	DECLARE_DYNCREATE(cvCInPlaceFrame)
public:
	cvCInPlaceFrame();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cvCInPlaceFrame)
	public:
	virtual BOOL OnCreateControlBars(CFrameWnd* pWndFrame, CFrameWnd* pWndDoc);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~cvCInPlaceFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CToolBar    m_wndToolBar;
	CDialogBar m_wndDlgBar;
	CReBar m_wndReBar;
	COleDropTarget	m_dropTarget;
	COleResizeBar   m_wndResizeBar;

// Generated message map functions
protected:
	//{{AFX_MSG(cvCInPlaceFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CVINPLACEFRAME_H__42C45BCA_818D_11D3_ABBD_0008C7FB2802__INCLUDED_)
