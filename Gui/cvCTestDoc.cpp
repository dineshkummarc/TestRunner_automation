// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// Description:
// 	Implements cvCTestDoc which handles persisting the Test and Test suite information.
// 
// $Log: 
//  3    CliniVision1.2         11/16/99 5:04:57 PM  Doug C. Eveland Simplified
//       call to ar.write to eliminate unicode and non-unicode versions by usring
//       T2A.
//  2    CliniVision1.1         11/11/99 10:27:44 AM Doug C. Eveland Added fix to
//       ensure Unicode and non-Unicode builds would work
//  1    CliniVision1.0         11/9/99 11:22:52 AM  Doug C. Eveland 
// $
// $Revision: 3$
// $Date: 11/16/99 5:04:57 PM$
// $Author: Doug C. Eveland$
// 
#include "stdafx.h"
#include "cvCTestApp.h"

#include "cvCTestDoc.h"
#include "cvCSrvrItem.h"
#include "cvCTestSuiteView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// cvCTestDoc

IMPLEMENT_DYNCREATE(cvCTestDoc, COleServerDoc)

BEGIN_MESSAGE_MAP(cvCTestDoc, COleServerDoc)
	//{{AFX_MSG_MAP(cvCTestDoc)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, OnUpdateFileSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(cvCTestDoc, COleServerDoc)
	//{{AFX_DISPATCH_MAP(cvCTestDoc)
	DISP_FUNCTION(cvCTestDoc, "Run", Run, VT_BOOL, VTS_BSTR VTS_BSTR)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


static const IID IID_IClinivisionTest =
{ 0x42c45bb8, 0x818d, 0x11d3, { 0xab, 0xbd, 0x0, 0x8, 0xc7, 0xfb, 0x28, 0x2 } };

BEGIN_INTERFACE_MAP(cvCTestDoc, COleServerDoc)
	INTERFACE_PART(cvCTestDoc, IID_IClinivisionTest, Dispatch)
END_INTERFACE_MAP()

// {group:cvCTestDoc}
// 
// Name: 
// 	cvCTestDoc::cvCTestDoc
// 
// Description:
// 	Constructor - enables automation for this class
// 
cvCTestDoc::cvCTestDoc()
{
	EnableAutomation();

	AfxOleLockApp();
}

// {group:cvCTestDoc}
// 
// Name: 
// 	cvCTestDoc::~cvCTestDoc
// 
// Description:
// 	Destructor
// 
cvCTestDoc::~cvCTestDoc()
{
	AfxOleUnlockApp();
}

// {group:cvCTestDoc}
// 
// Name: 
// 	cvCTestDoc::OnNewDocument
// 
// Description:
// 	Called by framework when the user selects to create a new document
// 
// Results:
// 	TRUE if a new document was created; else FALSE
// 
BOOL cvCTestDoc::OnNewDocument()
{
	if (!COleServerDoc::OnNewDocument())
		return FALSE;

	return TRUE;
}

COleServerItem* cvCTestDoc::OnGetEmbeddedItem()
{
	cvCSrvrItem* pItem = new cvCSrvrItem(this);
	ASSERT_VALID(pItem);
	return pItem;
}

// {group:cvCTestDoc}
// 
// Name: 
// 	cvCTestDoc::Serialize
// 
// Description:
// 	Used to read/write the test document from disk as XML
//  The read operation used the IXMLDocument2Ptr interface to read
//  the XML file from disk.
//  The write operation asks cvCTestSuiteView to create a string of
//  XML based on the contents of the tree view.
// 
// Arguments:
// 	ar - A reference to the archive for this document
// 
void cvCTestDoc::Serialize(CArchive& ar)
{
	HRESULT hr = S_OK;
	USES_CONVERSION;

	try
	{
		CString strFileName = ar.GetFile()->GetFileName();

		// Save test suite and test info to XML file.
		if (ar.IsStoring())
		{
			// only save file if it has been modified
			if (IsModified())
			{
				// find cvcTestSuiteView
				cvCTestSuiteView* pView = GetTestSuiteView();
				if (pView != NULL)
				{
					// Ask view to create XML testsuite/test string from tree
					CString strXML;
					pView->CreateXMLString(strXML);

					ar.Write((void*)T2A(strXML.LockBuffer()), strXML.GetLength());
				}
			}
		}

		// Initialize XMLDocument (m_spXMLDoc) using document's file name
		else
		{
			if (m_spXMLdoc != NULL)
			{
				m_spXMLdoc = NULL;
			}
			hr = m_spXMLdoc.CreateInstance(__uuidof(XML::XMLDocument));
			if (FAILED(hr))
				throw _com_error(hr);
			m_spXMLdoc->url = _bstr_t(strFileName);

			// Reset document modified flag
			SetModifiedFlag(FALSE);
		}
	}
	catch (_com_error e)
	{
		ATLTRACE("cvcTestDoc::Serialize: COM Error (%s)\n", e.Description());
	}
	catch(...)
	{
		ATLTRACE("cvcTestDoc::Serialize: Unknown error\n");
	}
}

/////////////////////////////////////////////////////////////////////////////
// cvCTestDoc diagnostics

#ifdef _DEBUG
void cvCTestDoc::AssertValid() const
{
	COleServerDoc::AssertValid();
}

void cvCTestDoc::Dump(CDumpContext& dc) const
{
	COleServerDoc::Dump(dc);
}
#endif //_DEBUG

// {group:cvCTestDoc}
// 
// Name: 
// 	cvCTestDoc::Run
// 
// Description:
// 	An automation method for the document class which a specific test suite
//  to be run.
// 
// Arguments:
// 	szFileName - the name of file which contains the test suites and tests
// 	szTestName - the name of the test suite or test to run.
// 
BOOL cvCTestDoc::Run(LPCTSTR szFileName, LPCTSTR szTestName) 
{
	BOOL bRet(FALSE);

	// Aquire pointer to test suite view
	cvCTestSuiteView* pView = GetTestSuiteView();
	if (pView != NULL)
	{
		// Delete existing contents of document
		DeleteContents();

		// open the new document
		_bstr_t bstrFileName(szFileName);
		if (OnOpenDocument((LPCTSTR) bstrFileName))
		{
			// Run a test with this name
			_bstr_t bstrTestName(szTestName);
			bRet = pView->StartAtTest((LPCTSTR) bstrTestName);
		}
	}
	return bRet ? VARIANT_TRUE : VARIANT_FALSE;
}

// {group:cvCTestDoc}
// 
// Name: 
// 	cvCTestDoc::GetTestSuiteView
// 
// Description:
// 	Finds the cvCTestSuiteView by interating thorugh the views for this document
// 
// Results:
// 	A pointer to the cvcTestSuiteView
// 
cvCTestSuiteView* cvCTestDoc::GetTestSuiteView()
{
	cvCTestSuiteView* pView = NULL;

	// find cvcTestSuiteView
	POSITION pos = GetFirstViewPosition();
	while (pos != NULL)
	{
		pView = dynamic_cast<cvCTestSuiteView*>(GetNextView(pos));
		if (pView != NULL)
		{
			break;
		}
	}
	return pView;
}

// {group:cvCTestDoc}
// 
// Name: 
// 	cvCTestDoc::OnOpenDocument
// 
// Description:
// 	Called by the framework when the test suite document is opened.  
//  A hint is sent to all views to allow them to respond to the event
// 
// Arguments:
// 	lpszPathName - The name of the test suite file which is being opened
// 
// Results:
// 	Returns TRUE if the document can be opened; else FALSE
// 
BOOL cvCTestDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!COleServerDoc::OnOpenDocument(lpszPathName))
		return FALSE;
	
	UpdateAllViews(NULL, ETestHint_Open);   
	
	return TRUE;
}

// {group:cvCTestDoc}
// 
// Name: 
// 	cvCTestDoc::OnUpdateFileSave
// 
// Description:
// 	Called by the framework when a UI element (e.g. button) associated with
//  Saving the document (e.g. the toolbar save button) is displayed.
//  If the document has been modified this UI element is enabled; else 
//  it is disabled.
// 
// Arguments:
// 	pCmdUI - A pointer to the UI element
// 
void cvCTestDoc::OnUpdateFileSave(CCmdUI* pCmdUI) 
{
	if (IsModified())
		pCmdUI->Enable(TRUE);
	else
		pCmdUI->Enable(FALSE);
	
}

// {group:cvCTestDoc}
// 
// Name: 
// 	cvCTestDoc::DeleteContents
// 
// Description:
// 	Called by the framework to delete the contents of the document
//  The IXMLDocument2Ptr interface is set to NULL, then the base document
//  DeleteContents is called.
// 
void cvCTestDoc::DeleteContents() 
{
	m_spXMLdoc = NULL;
	
	COleServerDoc::DeleteContents();
}


