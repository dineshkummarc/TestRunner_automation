#pragma once
// 
// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// File:
// 	cvTestDoc.h 
// 
// Description:
// 	Declares the cvCTestDoc class which is responsible for persisting test
//  and test suite data.
// 
// $Log: 
//  3    CliniVision1.2         11/16/99 5:05:11 PM  Doug C. Eveland Added DocJet
//       group comment
//  2    CliniVision1.1         11/11/99 10:28:04 AM Doug C. Eveland Added class
//       header
//  1    CliniVision1.0         11/9/99 11:22:52 AM  Doug C. Eveland 
// $
// $Revision: 3$
// $Date: 11/16/99 5:05:11 PM$
// $Author: Doug C. Eveland$
// 
#include "cvCTestSuiteView.h"

class cvCSrvrItem;

// {group:Document Classes}
// 
// Description:
// 	Used to display a tree of test suites and tests
// 
// Author:
// 	Doug Eveland
// 
// Description:
// 	Used to serialize the testsuites and tests from an XML document
// 
// Author:
// 	Doug Eveland
// 
class cvCTestDoc : public COleServerDoc
{
protected: // create from serialization only
	cvCTestDoc();
	DECLARE_DYNCREATE(cvCTestDoc)

// Attributes
public:
	cvCSrvrItem* GetEmbeddedItem()
		{return (cvCSrvrItem*)COleServerDoc::GetEmbeddedItem();}

// Operations
public:

	// 
	// Name: 
	// 	GetXMLDOMDocumentPtr
	// 
	// Description:
	// 	Returns a reference to the XMLDocument2 interface
	// 
	XML::IXMLDocument2Ptr& GetXMLDOMDocumentPtr() {return m_spXMLdoc;}

	// Hints used in UpdateAllViews to signal document status changes
	// Hints should not by 0 since 0 is used by framework
	enum ETestHint {ETestHint_Open = 1, ETestHint_Close};

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(cvCTestDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void DeleteContents();
	protected:
	virtual COleServerItem* OnGetEmbeddedItem();
	//}}AFX_VIRTUAL

// Implementation
	
public:
	virtual ~cvCTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	cvCTestSuiteView* GetTestSuiteView();

// Generated message map functions 

protected:
	//{{AFX_MSG(cvCTestDoc)
	afx_msg void OnUpdateFileSave(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(cvCTestDoc)
	afx_msg BOOL Run(LPCTSTR szFileName, LPCTSTR szTestName);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

private:
	// A smartpointer for the IXMLDocument2 interface
	XML::IXMLDocument2Ptr m_spXMLdoc;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

