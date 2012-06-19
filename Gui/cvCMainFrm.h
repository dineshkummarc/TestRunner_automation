#pragma once

// 
// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// File:
// 	cvCMainFrm.h 
// 
// Description:
// 	Declares the class cvCMainFrame
// 
// $Log: 
//  3    CliniVision1.2         11/16/99 5:00:27 PM  Doug C. Eveland Added class
//       header
//  2    CliniVision1.1         11/11/99 10:26:11 AM Doug C. Eveland Documented
//       private members
//  1    CliniVision1.0         11/9/99 11:22:50 AM  Doug C. Eveland 
// $
// $Revision: 3$
// $Date: 11/16/99 5:00:27 PM$
// $Author: Doug C. Eveland$
// 

// {group:Framework Classes}
// 
// Description:
// 	The main frame for the application (contains the splitter windows)
// 
// Author:
// 	Doug Eveland
// 
class cvCMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	cvCMainFrame();
	DECLARE_DYNCREATE(cvCMainFrame)

// Attributes
protected:
	CSplitterWnd m_wndSplitter;
	CSplitterWnd m_wndRightSplitter;
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cvCMainFrame)
	public:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~cvCMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;		// the status bar window
	CToolBar    m_wndToolBar;		// the tool bar window
	CReBar      m_wndReBar;			// the rebar window
	CDialogBar  m_wndDlgBar;		// the dialog bar window

// Generated message map functions
protected:
	//{{AFX_MSG(cvCMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

