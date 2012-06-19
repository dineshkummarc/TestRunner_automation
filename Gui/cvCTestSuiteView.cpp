// 
// 
//                         MALLINCKRODT 
//         Copyright(c) 1999 All Rights Reserved 
// 
// File:
//    cvTestSuiteView.cpp 
// 
// Description:
//    Implements the treeview for test suites
//
//		cvCTestSuiteView is responsible for implementing the cvISupportTestOutput
//		interface.  It does this using the MFC embedded class approach to implementing
//		COM interface.  The embedded class XSupportTestOutputObj is used to implement
//		the cvISupportTestOutput interface.
// 
// $Log: 
//  3    CliniVision1.2         11/16/99 5:06:47 PM  Doug C. Eveland Added DocJet
//       group comment
//       Added sample XML document file based on code review
//  2    CliniVision1.1         11/11/99 10:28:57 AM Doug C. Eveland Changed import
//       path to use relative path.
//       Added documentation
//  1    CliniVision1.0         11/9/99 11:22:53 AM  Doug C. Eveland 
// $
// $Revision: 3$
// $Date: 11/16/99 5:06:47 PM$
// $Author: Doug C. Eveland$
// 

#include "stdafx.h"
#include "cvCTestApp.h"

#include "cvCTestDoc.h"
#include "cvCTestSuiteView.h"
#include "cvCResultsView.h"
#include "cvCTestSuiteDlg.h"
#include "cvCTestDoc.h"
#include "cvCMainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#import "..\TestCore\TestCore.tlb" no_namespace

// Implement cvISupportTestOutput -- uuid(967013C1-827E-11d3-ABF5-00508B0D0D6E)

IMPLEMENT_OLECREATE(cvCTestSuiteView, "cvCTestSuiteView",
                    0x967013C1, 0x827E, 0x11d3,
                    0xAB, 0xF5, 0x0, 0x50, 0x8b, 0x0d, 0x0d, 0x6e);

IMPLEMENT_DYNCREATE(cvCTestSuiteView, CTreeView)

BEGIN_MESSAGE_MAP(cvCTestSuiteView, CTreeView)
	//{{AFX_MSG_MAP(cvCTestSuiteView)
	ON_COMMAND(ID_CANCEL_EDIT_SRVR, OnCancelEditSrvr)
	ON_NOTIFY_REFLECT(TVN_BEGINDRAG, OnBeginDrag)
	ON_WM_CONTEXTMENU()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_DESTROY()
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_NEW_SUITE, OnNewSuite)
	ON_COMMAND(ID_RENAME_TESTORSUITE, OnRenameTestOrSuite)
	ON_COMMAND(ID_INCREMENT_RUNCOUNT, OnIncrementRunCount)
	ON_NOTIFY_REFLECT(TVN_ENDLABELEDIT, OnEndLabelEdit)
	ON_COMMAND(ID_DECREMENT_RUNCOUNT, OnDecrementRunCount)
	ON_UPDATE_COMMAND_UI(ID_INCREMENT_RUNCOUNT, OnUpdateIncrementRunCount)
	ON_NOTIFY_REFLECT(TVN_DELETEITEM, OnDeleteItem)
	ON_COMMAND(ID_TESTSUITE_RUNTEST, OnTestSuiteRunTests)
	ON_UPDATE_COMMAND_UI(ID_TESTSUITE_RUNTEST, OnUpdateTestSuiteRunTest)
	ON_COMMAND(ID_VIEW_COLLAPSETREE, OnViewCollapseTree)
	ON_COMMAND(ID_VIEW_EXPANDTREE, OnViewExpandTree)
	ON_UPDATE_COMMAND_UI(ID_VIEW_COLLAPSETREE, OnUpdateViewCollapseTree)
	ON_UPDATE_COMMAND_UI(ID_VIEW_EXPANDTREE, OnUpdateViewExpandTree)
	ON_COMMAND(ID_FILE_STOPTESTS, OnFileStopTests)
	ON_UPDATE_COMMAND_UI(ID_FILE_STOPTESTS, OnUpdateFileStopTests)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CTreeView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CTreeView::OnFilePrintPreview)
END_MESSAGE_MAP()

BEGIN_INTERFACE_MAP(cvCTestSuiteView, CCmdTarget)
	INTERFACE_PART(cvCTestSuiteView, IID_IDispatch, SupportTestOutputObj)
	INTERFACE_PART(cvCTestSuiteView, __uuidof(cvISupportTestOutput), SupportTestOutputObj)
END_INTERFACE_MAP()

BEGIN_DISPATCH_MAP(cvCTestSuiteView, CCmdTarget)
	//{{AFX_DISPATCH_MAP(cvCTestSuiteView)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// IUnknown

STDMETHODIMP_(ULONG) cvCTestSuiteView::XSupportTestOutputObj::AddRef(void)
{
    METHOD_PROLOGUE(cvCTestSuiteView, SupportTestOutputObj)
		return pThis->ExternalAddRef();
}
STDMETHODIMP_(ULONG)cvCTestSuiteView::XSupportTestOutputObj::Release(void)
{
	METHOD_PROLOGUE(cvCTestSuiteView, SupportTestOutputObj)
	return pThis->ExternalRelease();
}
STDMETHODIMP cvCTestSuiteView::XSupportTestOutputObj::QueryInterface(REFIID riid, void **ppv) 
{
    METHOD_PROLOGUE(cvCTestSuiteView, SupportTestOutputObj)
    return pThis->ExternalQueryInterface(&riid, ppv);
}
STDMETHODIMP cvCTestSuiteView::XSupportTestOutputObj::GetTypeInfoCount(UINT FAR* pctinfo)
{
	METHOD_PROLOGUE(cvCTestSuiteView, SupportTestOutputObj)
	LPDISPATCH lpDispatch = pThis->GetIDispatch(FALSE);
	ASSERT(lpDispatch != NULL);
	return lpDispatch->GetTypeInfoCount(pctinfo);
}
STDMETHODIMP cvCTestSuiteView::XSupportTestOutputObj::GetTypeInfo(UINT itinfo,
				 LCID lcid, ITypeInfo FAR* FAR* pptinfo)
{
   METHOD_PROLOGUE(cvCTestSuiteView, SupportTestOutputObj)
   LPDISPATCH lpDispatch = pThis->GetIDispatch(FALSE);
   ASSERT(lpDispatch != NULL);
   return lpDispatch->GetTypeInfo(itinfo, lcid, pptinfo);
}
STDMETHODIMP cvCTestSuiteView::XSupportTestOutputObj::GetIDsOfNames(
       REFIID riid, OLECHAR FAR* FAR* rgszNames, UINT cNames,
       LCID lcid, DISPID FAR* rgdispid) 
{
   METHOD_PROLOGUE(cvCTestSuiteView, SupportTestOutputObj)
   LPDISPATCH lpDispatch = pThis->GetIDispatch(FALSE);
   ASSERT(lpDispatch != NULL);
   return lpDispatch->GetIDsOfNames(riid, rgszNames, cNames, 
                                    lcid, rgdispid);
}
STDMETHODIMP cvCTestSuiteView::XSupportTestOutputObj::Invoke(DISPID dispidMember, 
				REFIID riid, LCID lcid, WORD wFlags,
			    DISPPARAMS FAR* pdispparams, VARIANT FAR* pvarResult,
				EXCEPINFO FAR* pexcepinfo, UINT FAR* puArgErr)
{
   METHOD_PROLOGUE(cvCTestSuiteView, SupportTestOutputObj)
   LPDISPATCH lpDispatch = pThis->GetIDispatch(FALSE);
   ASSERT(lpDispatch != NULL);
   return lpDispatch->Invoke(dispidMember, riid, lcid,
                             wFlags, pdispparams, pvarResult,
                             pexcepinfo, puArgErr);
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::XSupportTestOutputObj::raw_LogResult
// 
// Description:
// 	This function implements the LogResult method of the cvISupportTestOutput interface.
// 
// Arguments:
// 	bstrMessage - The message to be logged.
// 
// Results:
// 	Returns S_OK.
// 
STDMETHODIMP cvCTestSuiteView::XSupportTestOutputObj::raw_LogResult(BSTR bstrMessage) 
{
	METHOD_PROLOGUE(cvCTestSuiteView, SupportTestOutputObj);

	_bstr_t bstrOutput(bstrMessage);

	pThis->WriteToResultsView(bstrOutput);
	
	return S_OK;
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::cvCTestSuiteView
// 
// Description:
// 	A constructor for the view.  Initializes class members.
// 
cvCTestSuiteView::cvCTestSuiteView()
: m_pDragImage(NULL) 
, m_htiDrag(NULL) 
, m_htiDrop(NULL)
, m_htiOldDrop(NULL)
, m_bDragging(FALSE)
, m_idTimer(0)
, m_nTestIdx(-1)
, m_nFolderIdx(-1)
, m_nOpenFolderIdx(-1)
, m_bInitialized(FALSE)
, m_nNumFailures(0)
, m_bExecutingTests(FALSE)
{
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::PreCreateWindow
// 
// Description:
// 	Called by the framework before the window is created.  Sets the styles for the tree control.
// 
// Arguments:
// 	cs - A structure which contains info about the window to be created.
// 
// Results:
// 	Should return TRUE if the creation process is to continue
// 
BOOL cvCTestSuiteView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= TVS_HASBUTTONS | TVS_HASLINES |
			TVS_EDITLABELS | TVS_LINESATROOT;

	return CTreeView::PreCreateWindow(cs);
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnDraw
// 
// Description:
// 	Called by the framework when it is time to draw the view.
// 
// Arguments:
// 	pDC - A pointer to the device context
// 
void cvCTestSuiteView::OnDraw(CDC* pDC)
{
	cvCTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnInitialUpdate
// 
// Description:
// 	Called once when the view is first initialized. Performs one
//  time initialization of the view
// 
void cvCTestSuiteView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	InitializeImages();
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::InitializeImages
// 
// Description:
// 	Loads the drop and no-drop cursors, the images maps for the tree icons and
//  the icons for the tree node state (indicates whether an item or sub items 
//  are checked or whether a test or test suite passed or failed.)
// 
void cvCTestSuiteView::InitializeImages()
{
	if (!m_bInitialized)
	{
		// Enable automation for this CCmdTarget object
		EnableAutomation();

		// Load drop/no-drop cursors
		m_hNoDropCursor = AfxGetApp()->LoadCursor(IDC_NODROP);
		ASSERT(m_hNoDropCursor != NULL);

		m_hDropCursor = AfxGetApp()->LoadCursor(IDC_POINTER);
		ASSERT(m_hDropCursor != NULL);

		// load image lists
		CTreeCtrl& TreeCtrl = this->GetTreeCtrl();

		// create an image list of handling tree icons
		CImageList* pImage = new CImageList;
		pImage->Create(16, 16, ILC_COLOR, 0, 3);

		// load bitmaps for the folder, open folder, and test icons
		CBitmap bmFolder;
	    bmFolder.LoadBitmap(IDB_FOLDER); 
		m_nFolderIdx = pImage->Add(&bmFolder,RGB(0,0,0));

		CBitmap bmOpenFolder;
	    bmOpenFolder.LoadBitmap(IDB_OPENFOLDER); 
		m_nOpenFolderIdx = pImage->Add(&bmOpenFolder,RGB(0,0,0));

		CBitmap bmTest;
	    bmTest.LoadBitmap(IDB_TEST); 
		m_nTestIdx = pImage->Add(&bmTest,RGB(0,0,0));

		// Set the tree's image list
		TreeCtrl.SetImageList( pImage, TVSIL_NORMAL );

		//----- Create state image list (to handle checkbox images) -----//
		if (m_StateImage.GetSafeHandle() == NULL)
		{
			m_StateImage.Create(IDB_TESTSUITE_STATE, 13, 1, RGB(255,255,255) );
			TreeCtrl.SetImageList(&m_StateImage, TVSIL_STATE );
		}
		m_bInitialized = true;
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnUpdate
// 
// Description:
// 	Called by the framework when the view should be updated.  
//  This is normally called when the document has been loaded or cleared
// 
// Arguments:
// 	pSender - The view which sent the hint.
// 
// 	lHint - A hint about what changed in the view.  This should be ETestHing_Close or ETestHint)Open
// 
// 	pHint - A pointer to an CObject which has further hint info.  Not used.
// 
void cvCTestSuiteView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// Init cursors, bitmaps, images
	InitializeImages();

	// Document cleared the current collection of test suites.
	if ((cvCTestDoc::ETestHint) lHint == cvCTestDoc::ETestHint_Close)
	{
		GetTreeCtrl().DeleteAllItems();
	}
	else if ((cvCTestDoc::ETestHint) lHint == cvCTestDoc::ETestHint_Open)
	{
		CString strMessage(MAKEINTRESOURCE(IDS_LOADINGTESTSUITES));
		GetParentFrame()->SetMessageText(strMessage);

		GetTreeCtrl().DeleteAllItems();
		
		LoadXMLDocument();

		strMessage.LoadString(IDS_TESTSUITEINFOLOADED);
		GetParentFrame()->SetMessageText(strMessage);

		ExpandTree(GetTreeCtrl().GetRootItem());
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::LoadXMLDocument
// 
// Description:
// 	Loads a set of suites and tests from an XML document which is housed
//  within the app's document.
//
//  A sample XML document appears below.
//
//      <?xml:stylesheet type='text/xsl' href='ClinivisionTests.xsl'?>
//     <TESTSUITES>
//            <TESTSUITE>
//                  <NAME>Smoke Test</NAME>
//                  <RUNCOUNT>1</RUNCOUNT>
//                  <SELECTED>1</SELECTED>
//                  <TEST>
//                        <NAME>TestComponent1</NAME>
//                        <SELECTED>1</SELECTED>
//                        <CLSID>{EC86425F-8321-11D3-ABF8-00508B0D0D6E}</CLSID>
//                  </TEST>
//                  <TEST>
//                        <RUNCOUNT>1</RUNCOUNT>
//                        <SELECTED>1</SELECTED>
//                        <CLSID>{EC864261-8321-11D3-ABF8-00508B0D0D6E}</CLSID>
//                  </TEST>
//	     </TESTSUITE>
//      </TESTSUITES>
// 
void cvCTestSuiteView::LoadXMLDocument()
{
	// Load Test Suites and test from XMLDOMDocument
	cvCTestDoc* pDoc = GetDocument();
	if (pDoc != NULL)
	{
		try
		{
			XML::IXMLDocument2Ptr spXML = pDoc->GetXMLDOMDocumentPtr();
			if (spXML != NULL)
			{
				// Get root note (TESTSUITES)
				XML::IXMLElementPtr spTestNode = spXML->root;
				// Get children of TESTSUITES (TESTSUITE)
				XML::IXMLElementCollectionPtr spTestSuites = spTestNode->children;

				// iterate through test suites, adding each Test Suite to tree.
				for (long lItem = 0; lItem < spTestSuites->length; lItem++)
				{
					spTestNode = spTestSuites->item(lItem);
					InsertXMLNode(spTestNode);
				}
			}
		}
		catch (_com_error e)
		{
			ATLTRACE("cvCTestSuiteView::OnInitialUpdate: InsertXMLNodes Failed (%s)", e.Description());
		}
		catch (...)
		{
			ATLTRACE("cvCTestSuiteView::OnInitialUpdate: InsertXMLNodes Failed");
		}

		// Document just loaded, so it could not be modified yet!
		GetDocument()->SetModifiedFlag(FALSE);
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::InsertXMLNode
// 
// Description:
// 	Inserts a node into the tree control based on the XML node passed.  If the node
//  has children which are TEST's or TESTSUITE's then this function is recursively
//  called to add those nodes.
// 
// Arguments:
// 	XML::IXMLElementPtr& spNode - A reference to an IXMLElement node from the XML tree.
// 
// 	htiParent - A handle to the parent CTreeCtrl item to add this node to as a child.
// 
void cvCTestSuiteView::InsertXMLNode
	(
		const XML::IXMLElementPtr& spNode, 
		HTREEITEM htiParent
	)
{
	// validate incoming interface pointer
	if (spNode == NULL)
	{
		throw _com_error(E_POINTER);
	}

	// create dragdropitem for holding testsuite or test info before insert
	cvCDragDropItem* pDragDropItem = new cvCDragDropItem;
	if (!pDragDropItem)
	{
		throw _com_error(E_OUTOFMEMORY);
	}

	// Set type of node that will be created in the tree
	_bstr_t bstrTagName = spNode->tagName;
	if (spNode->tagName == _bstr_t("TEST"))
	{
		pDragDropItem->SetType(cvCDragDropItem::EDragDropType_Test);
	}
	else if (spNode->tagName == _bstr_t("TESTSUITE"))
	{
		pDragDropItem->SetType(cvCDragDropItem::EDragDropType_Suite);
	}
	else
	{
		throw _com_error(E_INVALIDARG);
	}

	// Insert item in tree now, update its attributes later as they appear 
	// while traversing the XML tree.
	// This newly inserted item is now the parent for any other items
	// that are inserted into the tree
	HTREEITEM htiNewNode = InsertItem(pDragDropItem, htiParent);

	InsertXMLNodeChildren(pDragDropItem, spNode, htiNewNode);
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::InsertXMLNodeChildren
// 
// Description:
//    Get children of this node to use to fill in properties for the node
//    some children may be other nodes, then will be handled by calling InsertXMLnode
// 
// Arguments:
// 	XML::IXMLElementPtr& spNode - A reference to an IXMLElement node from the XML tree.
// 
// 	htiParent - A handle to the parent CTreeCtrl item to add this node to as a child.
// 
void cvCTestSuiteView::InsertXMLNodeChildren
	(
		cvCDragDropItem *pDragDropItem,
		const XML::IXMLElementPtr& spNode, 
		HTREEITEM htiParent
	)
{
	XML::IXMLElementCollectionPtr spTestNodeChildren = spNode->children;			
	long lNumChildrenNodes = spTestNodeChildren->length;
	XML::IXMLElementPtr spTestNode;
	_bstr_t bstrTagName;

	for (long lItem = 0; lItem < lNumChildrenNodes; lItem++)
	{
		spTestNode = spTestNodeChildren->item(_variant_t((long) lItem));
		ASSERT(spTestNode != NULL);
		if (spTestNode != NULL)
		{
			bstrTagName = spTestNode->tagName;

			// If test or testsuite node found, recurse to add node
			if ((bstrTagName == _bstr_t("TEST")) || (bstrTagName == _bstr_t("TESTSUITE")))
			{
				InsertXMLNode(spTestNode, htiParent);
			}
			else if (bstrTagName == _bstr_t("NAME"))
			{
				pDragDropItem->SetName(spTestNode->text);
				UpdateNodeText(htiParent);
			}
			else if (bstrTagName == _bstr_t("RUNCOUNT"))
			{
				pDragDropItem->SetRunCount(atoi(spTestNode->text));
				UpdateNodeText(htiParent);
			}
			else if (bstrTagName == _bstr_t("CLSID"))
			{
				CLSID clsid;
				CLSIDFromString(spTestNode->text, &clsid);
				pDragDropItem->SetCLSID(clsid);
			}
			else if (bstrTagName == _bstr_t("SELECTED"))
			{
				if ( spTestNode->text == _bstr_t("1"))
				{
					SetCheck(htiParent, TOGGLE);
					pDragDropItem->SetSelected(TRUE);
				}
			}
		}
	}
}

BOOL cvCTestSuiteView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void cvCTestSuiteView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void cvCTestSuiteView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
}

void cvCTestSuiteView::OnCancelEditSrvr()
{
	GetDocument()->OnDeactivateUI(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// cvCTestSuiteView diagnostics

#ifdef _DEBUG
void cvCTestSuiteView::AssertValid() const
{
	CTreeView::AssertValid();
}

void cvCTestSuiteView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

cvCTestDoc* cvCTestSuiteView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(cvCTestDoc)));
	return (cvCTestDoc*)m_pDocument;
}
#endif //_DEBUG

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnBeginDrag
// 
// Description:
// 	Called by the framework when a drag operation begins.
//  A drag image is created and the mouse movements are captured
//  until the left mouse button is released (OnLButtonUp)
// 
// Arguments:
// 	pNMHDR - A pointer to the notification messaged header
// 
// 	pResult - A pointer to the result which should be set to 0 before exiting
// 
void cvCTestSuiteView::OnBeginDrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	m_htiDrag = pNMTreeView->itemNew.hItem;
	m_htiDrop = NULL;

	m_pDragImage = GetTreeCtrl().CreateDragImage( m_htiDrag );
	if (!m_pDragImage)
		return;

	m_bDragging = true;
	
	IMAGEINFO ImageInfo;
	m_pDragImage->GetImageInfo( 0, &ImageInfo );

	// find center of image
	CPoint pt;
	pt.x = (ImageInfo.rcImage.right - ImageInfo.rcImage.left) / 2;
	pt.y = (ImageInfo.rcImage.bottom - ImageInfo.rcImage.top) / 2;

	m_pDragImage->BeginDrag(0, pt);
	pt = pNMTreeView->ptDrag;
	ClientToScreen(&pt);
	m_pDragImage->DragEnter(NULL,pt);
	
	SetCapture();

	*pResult = 0;
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnLButtonDown
// 
// Description:
// 	Called when the left mouse button is depressed. If the mouse 
//  is over the tree nodes 'state' icon, then the SetCheck function
//  is called to toggle the state of the checked status of the 
//  tree node.
// 
// Arguments:
// 	nFlags - Indicates whether various virtual keys are down (see CWnd::OnLButtonDown)
// 
// 	point - The x,y coordinate of the mouse when the left button was depressed
// 
void cvCTestSuiteView::OnLButtonDown(UINT nFlags, CPoint pt) 
{
	UINT uFlags=0;
	HTREEITEM hItem = GetTreeCtrl().HitTest(pt,&uFlags);
	if (uFlags & TVHT_ONITEMSTATEICON)
	{
		SetCheck(hItem, TOGGLE);
		return;
	}

	CTreeView::OnLButtonDown(nFlags, pt);
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnLButtonUp
// 
// Description:
// 	Called by the framework when the left mouse button is released.
//  If in the midst of a drag item, the drag object is dropped on the
//  tree.
// 
// Arguments:
// 	nFlags - Indicates whether various virtual keys are down (see CWnd::OnLButtonUp)
// 
// 	point - The x,y coordinate of the mouse when the left mouse button was released.
// 
void cvCTestSuiteView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CTreeView::OnLButtonUp(nFlags, point);

	if (m_bDragging)
	{
		DropItemOnTree(point);
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnRButtonDown
// 
// Description:
// 	Called by the framework when the right mouse button is pressed.
// 
// Arguments:
// 	nFlags - Indicates whether various virtual keys are down (see CWnd::OnMouseMove)
// 
// 	point - The x,y coordinates of the mouse when the right mouse button was depressed.
// 
void cvCTestSuiteView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CPoint pt(point);
	ClientToScreen(&pt);

	OnContextMenu(NULL, pt);
	
	CTreeView::OnRButtonDown(nFlags, point);
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::DropNewTestOnTree
// 
// Description:
// 	Inserts the drag drop item on the tree by calling InsertItem.
//  This function is called from external views which have a list of tests 
//  which are to be added to a test suite.
// 
// Arguments:
// 	pt - The x,y coordinates in the tree where the drop is to occur.
// 
// 	pDragDropItem - A pointer to the item to be dropped.
// 
void cvCTestSuiteView::DropNewTestOnTree(CPoint pt, cvCDragDropItem* pDragDropItem)
{
	CWaitCursor WaitCursor;
	
	ASSERT(pDragDropItem != NULL);
	if (pDragDropItem != NULL)
	{
		//HTREEITEM htiDropTarget = SetDropTarget(pt);
		HTREEITEM htiDropTarget;
		if (CanDropAtPoint(pt, htiDropTarget))
		{
			InsertItem(pDragDropItem, htiDropTarget);
		}
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::CanDropAtPoint
// 
// Description:
// 	Determines if a drop operation can occur at the client-coordinate point specified by 'pt'
//  htiDropTarget is only valid if the drop is a legal operation.
// 
// Arguments:
// 	pt - The point at which the drop would occur
//  htiDropTarget - the handle of the suite which the test could be dropped on
// 
// Results:
// 	TRUE if an drop is legal at this location; else FALSE
// 
bool cvCTestSuiteView::CanDropAtPoint(CPoint& pt, HTREEITEM& htiDropTarget)
{
	bool bRet = false;
	UINT uFlags;
	htiDropTarget = GetTreeCtrl().HitTest(pt,&uFlags);
	if (htiDropTarget != NULL)
	{
		cvCDragDropItem* pDropItem = (cvCDragDropItem*) (GetTreeCtrl().GetItemData(htiDropTarget));
		if (pDropItem->GetType() == cvCDragDropItem::EDragDropType_Suite)
		{
			bRet = true;
		}
	}
	return bRet;
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::DropItemOnTree
// 
// Description:
// 	Drops a test or suite on the tree.  The mousecapture is released.
// 
// Arguments:
// 	pt - The x,y coordinates where the drop should occur
// 
void cvCTestSuiteView::DropItemOnTree(CPoint pt)
{
	CWaitCursor WaitCursor;

	// Set drop target members based on pt
	SetDropTarget(pt);

	// if there is a drop target, continue
	if (m_htiDrop != NULL)
	{
		CTreeCtrl& TreeCtrl = GetTreeCtrl();

		m_bDragging = false;

		CImageList::DragLeave(this);
		CImageList::EndDrag();

		ReleaseCapture();

		// free drag image memory
		if (m_pDragImage != NULL)
		{
			delete m_pDragImage;
			m_pDragImage = NULL;
		}

		TreeCtrl.SelectDropTarget(NULL);
		m_htiOldDrop = NULL;

		//------ Make sure we are dropping the item on a valid target ----//
		// don't drag an item on itself
		if (m_htiDrag == m_htiDrop)
			return;

		// don't drag a test item on a test item or a suite item on a test item
		cvCDragDropItem* pDropItem = (cvCDragDropItem*) (GetTreeCtrl().GetItemData(m_htiDrop));
		if (pDropItem != NULL)
		{
			if (pDropItem->GetType() == cvCDragDropItem::EDragDropType_Test)
				return;
		}
		
		// Make sure that the item being dragged is not being dropped on a
		// node which it is a parent of.
		HTREEITEM htiParent = m_htiDrop;
		while ((htiParent = TreeCtrl.GetParentItem(htiParent)) != NULL)
		{
			if (htiParent == m_htiDrag)
				return;
		}

		//------ Perform the copy below after expanding the drop target --------//
		TreeCtrl.Expand(m_htiDrop, TVE_EXPAND);

		HTREEITEM htiNew = CopyBranch( m_htiDrag, m_htiDrop, TVI_LAST );
		TreeCtrl.DeleteItem(m_htiDrag);
		TreeCtrl.SelectItem(htiNew);

		// NULL out handles used in dragging
		m_htiDrag = m_htiDrop = m_htiOldDrop = NULL;

		// Stop timer if it exists
		if (m_idTimer)
		{
			KillTimer( m_idTimer );
			m_idTimer = 0;
		}
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnMouseMove
// 
// Description:
// 	Called by the framework each time the mouse moves.  If a drag operation
//  is occuring, the mouse cursor is modified based on whether the the mouse
//  is over a valid drop target.
// 
// Arguments:
// 	nFlags - Indicates whether various virtual keys are down (see CWnd::OnMouseMove)
// 
// 	ptCurrent - The x,y coordinates of the mouse
// 
void cvCTestSuiteView::OnMouseMove(UINT nFlags, CPoint ptCurrent) 
{
	if (m_bDragging)
	{
		bool bBadDrop(false);
		CPoint pt(ptCurrent);
		ClientToScreen(&pt);

		// Set the drop target based on the current position
		HTREEITEM htiDropItem = SetDropTarget(ptCurrent);
		if (htiDropItem != NULL)
		{
			// obtain a pointer to dragdrop item info from the item's data
			cvCDragDropItem* pDropItem = (cvCDragDropItem*) (GetTreeCtrl().GetItemData(htiDropItem));
			if ( pDropItem != NULL &&
				(pDropItem->GetType() == cvCDragDropItem::EDragDropType_Test) )
			{
				bBadDrop = true;
			}
		}

		// change icon based on drop window
		CWnd *m_pDropWnd = WindowFromPoint(pt);

		if (!bBadDrop && (m_pDropWnd != NULL) 
			&& (m_pDropWnd->IsKindOf(RUNTIME_CLASS(cvCTestSuiteView))))
		{
			SetCursor(m_hDropCursor);
		}
		else
		{
			SetCursor(m_hNoDropCursor);
		}
	}
	CTreeView::OnMouseMove(nFlags, ptCurrent);
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::SetDropTarget
// 
// Description:
// 	Selects the drop target for the drag/drop operation. 
// 
// Arguments:
// 	pt - The x,y coordinate where the drop will occur.
// 
// Results:
// 	The handle to the tree view node which will be the target of the drop operation.
//  NULL will be returned if there is not drop target.
// 
HTREEITEM cvCTestSuiteView::SetDropTarget(CPoint pt)
{
	UINT uFlags;

	// convert to screen coordinates for DragMove
	CPoint ptDrag(pt);
	ClientToScreen(&ptDrag);
	m_pDragImage->DragMove(ptDrag);

	// Determine if we are dragging onto a tree node.
	HTREEITEM hti = GetTreeCtrl().HitTest(pt,&uFlags);
	if (hti != NULL)
	{
		m_pDragImage->DragShowNolock(FALSE);

		if (m_htiOldDrop == NULL)
			m_htiOldDrop = GetTreeCtrl().GetDropHilightItem();

		GetTreeCtrl().SelectDropTarget(hti);
		
		m_htiDrop = hti;
		
		if (m_idTimer && hti == m_htiOldDrop)
		{
			KillTimer( m_idTimer );
			m_idTimer = 0;
		}
		
		if (!m_idTimer)
			m_idTimer = SetTimer(1000, 2000, NULL );

		m_pDragImage->DragShowNolock(TRUE);
	}

	return hti;
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::CopyItem
// 
// Description:
// 	Copies a node indicated by hti to a location under a new parent, indicated by htiNewParent.
// 
// Arguments:
// 	hti - The handle of the item to be copied.
// 
// 	htiNewParent - The handle of the new parent.
// 
// 	htiAfter  - The handle of the tree item which this new item will be copied after (default is TVI_LAST)
// 
// Results:
// 	A handle to the new copy of the item.
// 
HTREEITEM cvCTestSuiteView::CopyItem
	(
		HTREEITEM hti,
		HTREEITEM htiNewParent, // = TVI_ROOT 
		HTREEITEM htiAfter // = TVI_LAST
	)
{
	CWaitCursor WaitCursor;

	ASSERT(hti != NULL);

	cvCDragDropItem* pDragDropItem = (cvCDragDropItem*) (GetTreeCtrl().GetItemData(hti));
	cvCDragDropItem* pNewDragDropItem = new cvCDragDropItem(*pDragDropItem);
	ASSERT(pNewDragDropItem != NULL);
	if (pNewDragDropItem == NULL)
	{
		return (HTREEITEM) 0;
	}
	else
	{
		*pNewDragDropItem = *pDragDropItem;
		TRACE2("CTestSuiteView::CopyItem: Created copy of Item (%p to %p)\n", pDragDropItem, pNewDragDropItem);
		return InsertItem(pNewDragDropItem, htiNewParent, htiAfter);
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::InsertItem
// 
// Description:
// 	Inserts a new item into the tree based on the contents of pDragDropItem
// 
// Arguments:
// 	pDragDropItem - A pointer to the item (Test or Suite) which will be dropped.
// 
// 	htiParent - The handle to the tree node which will be the parent for the newly inserted node.
// 
// 	htiAfter - The handle of the item which the new item will be inserted after.
// 
// Results:
// 	A handle to the newly inserted item.
// 
HTREEITEM cvCTestSuiteView::InsertItem(cvCDragDropItem* pDragDropItem,
										HTREEITEM htiParent, HTREEITEM htiAfter)
{
	TVINSERTSTRUCT tvItem;
	::ZeroMemory(&tvItem, sizeof(TVINSERTSTRUCT));

	HTREEITEM htiNew = NULL;
	CString strItem((LPCTSTR)pDragDropItem->GetName());

	// Setup the tree view item properties for the item which is to be inserted
	tvItem.item.mask = TVIF_CHILDREN|TVIF_HANDLE|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvItem.item.cchTextMax = strItem.GetLength();
	tvItem.item.pszText = strItem.LockBuffer();

	if (pDragDropItem->GetType() == cvCDragDropItem::EDragDropType_Test)
	{
		tvItem.item.iImage = m_nTestIdx;
		tvItem.item.iSelectedImage = m_nTestIdx;
	}
	else
	{
		tvItem.item.iImage = m_nFolderIdx;
		tvItem.item.iSelectedImage = m_nOpenFolderIdx;
	}

	tvItem.hParent = htiParent;
	tvItem.hInsertAfter = htiAfter;
	tvItem.item.lParam = (LPARAM) pDragDropItem;
	tvItem.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_PARAM;
	htiNew = GetTreeCtrl().InsertItem(&tvItem);
	strItem.UnlockBuffer();

	GetTreeCtrl().SetItemState(htiNew, INDEXTOSTATEIMAGEMASK(1), TVIS_STATEIMAGEMASK );

	UpdateNodeText(htiNew);

	// mark document as modified
	GetDocument()->SetModifiedFlag();

	return htiNew;
}

// {group:View Classes}
// 
// Name: 
//    cvCTestSuiteView::CopyBranch
// 
// Description:
//    Copies a branch of the tree from one location (hti) to another parent (htiParent)
// 
// Arguments:
//    hti - The handle of the branch to copy from
// 
//    htiNewParent - The new parent for the branch
// 
//    htiAfter - The insertion relationship 
// 
// Results:
//    The handle of the newly inserted item
// 
HTREEITEM cvCTestSuiteView::CopyBranch
	(
		HTREEITEM hti,
		HTREEITEM htiNewParent,
		HTREEITEM htiAfter // = TVI_LAST
	)
{
	CWaitCursor WaitCursor;

	ASSERT(_T("Copy Branch\n"));

	CTreeCtrl& TreeCtrl = GetTreeCtrl();

	HTREEITEM htiChild = NULL;

	HTREEITEM htiNew = CopyItem( hti, htiNewParent, htiAfter );
	htiChild = TreeCtrl.GetChildItem( hti );

	while (htiChild != NULL)
	{
		CopyBranch( htiChild, htiNew );
		htiChild = TreeCtrl.GetNextSiblingItem( htiChild );
	}

	return htiNew;
}

// {group:View Classes}
// 
// Name: 
//    cvCTestSuiteView::OnDestroy
// 
// Description:
//    Called just before the window is to be destroyed
// 
void cvCTestSuiteView::OnDestroy() 
{
	CImageList* pImage = GetTreeCtrl().GetImageList( TVSIL_NORMAL );
	delete pImage;

	if (m_idTimer)
	{
		KillTimer( m_idTimer );
		m_idTimer = 0;
	}

	CTreeView::OnDestroy();
}

// {group:View Classes}
// 
// Name: 
//    cvCTestSuiteView::OnTimer
// 
// Description:
//    Called whenever the timer fires. If there exists an item in the
//    tree which is highlighted for a drop operation, the highlighted 
//    item is expanded.  This operation is performed to simplify the drop operation
//    for a user who wants to drop on a subnode of the tree that may be 
//    hidden.
// 
// Arguments:
//    nIDEvent - The id of the timer which fired
// 
void cvCTestSuiteView::OnTimer(UINT nIDEvent) 
{
	if (nIDEvent == m_idTimer)
	{
		CTreeCtrl& TreeCtrl = GetTreeCtrl();
		HTREEITEM htiFloat = TreeCtrl.GetDropHilightItem();
		if (htiFloat && (htiFloat == m_htiDrop))
		{
			if (TreeCtrl.ItemHasChildren( htiFloat ) )
				TreeCtrl.Expand( htiFloat, TVE_EXPAND );
		}
	}

	CTreeView::OnTimer(nIDEvent);
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnContextMenu
// 
// Description:
// 	Called by the framework when the user presses the right mouse button to obtain
//  a context menu
// 
// Arguments:
// 	pWnd - A pointer to the window in which the user clicked the right mouse button
// 
// 	point - The x,y coordinates of the mouse when the right mouse button was clicked.
// 
void cvCTestSuiteView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// load the popup menu to display   
	CMenu mnuTestSuite;
	mnuTestSuite.LoadMenu(IDR_TESTSUITE_MENU);
	CMenu* mnuPopup = mnuTestSuite.GetSubMenu(0);

	// call the helper function to setup this as a titled popup menu
	mnuPopup->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, AfxGetMainWnd(), NULL);
}

// {group:View Classes}
// 
// Name: 
//    cvCTestSuiteView::SetCheck
// 
// Description:
//    Handles the setting the checked/un-unchecked state of a tree node, the node's children, 
//    and the node's parents
// 
// Arguments:
//    hItem - the handle of the tree node which is to be checked
// 
//    nCheck - The type of operation which is to be performed, CHECK or NCHECK
// 
// Results:
//    Returns TRUE if a valid hItem was passed; else FALSE
// 
BOOL cvCTestSuiteView::SetCheck(HTREEITEM hItem, CheckType nCheck)
{
	CWaitCursor WaitCursor;

	if (hItem == NULL)
		return FALSE;

	GetDocument()->SetModifiedFlag();

	CTreeCtrl& TreeCtrl = GetTreeCtrl();

	cvCDragDropItem* pDragDropItem = (cvCDragDropItem*) (GetTreeCtrl().GetItemData(hItem));
	ASSERT(pDragDropItem != NULL);

	UINT nState = TreeCtrl.GetItemState( hItem, TVIS_STATEIMAGEMASK ) >> 12;

	// Determine the new check state
	if (nCheck == CHECK)
	{
		if (pDragDropItem != NULL)
		{
			pDragDropItem->SetSelected(TRUE);
		}

		if (nState == CHECKED || nState == SELF_AND_CHILD_CHECKED)
			return TRUE;

		switch (nState)
		{
			case UNCHECKED:
				nState = CHECKED;
				break;
			case CHILD_CHECKED:
				nState = SELF_AND_CHILD_CHECKED;
				break;
		}
	}
	else if (nCheck == UNCHECK)
	{
		if (pDragDropItem != NULL)
		{
			pDragDropItem->SetSelected(FALSE);
		}

		if (nState == UNCHECKED || nState == CHILD_CHECKED)
			return TRUE;

		switch (nState)
		{
			case CHECKED:
				nState = UNCHECKED;
				break;
			case SELF_AND_CHILD_CHECKED:
				nState = CHILD_CHECKED;
				break;
		}
	}
	else if (nCheck == TOGGLE)
	{
		if (pDragDropItem != NULL)
		{
			pDragDropItem->SetSelected(pDragDropItem->GetSelected() ? FALSE : TRUE);
		}
		switch (nState)
		{
			case UNCHECKED:
				nState = CHECKED;
				break;
			case CHECKED:
				nState = UNCHECKED;
				break;
			case CHILD_CHECKED:
				nState = SELF_AND_CHILD_CHECKED;
				break;
			case SELF_AND_CHILD_CHECKED:
				nState = CHILD_CHECKED;
				break;
		}
	}
	else if (nCheck == REFRESH)
	{
		// Scan children to determine new state
		BOOL bChildSelected = FALSE;
		HTREEITEM htiChild = TreeCtrl.GetChildItem( hItem );

		// Scan children
		while (htiChild)
		{
			UINT nChildState = TreeCtrl.GetItemState( htiChild,TVIS_STATEIMAGEMASK ) >> 12;
			if (nChildState != UNCHECKED && nChildState != NOSTATE )
			{
				bChildSelected = TRUE;
				break;
			}
			htiChild = TreeCtrl.GetNextItem( htiChild, TVGN_NEXT );
		}
		if (bChildSelected)
		{
			if (nState == CHECKED) 
				nState = SELF_AND_CHILD_CHECKED;
			else if (nState == UNCHECKED) 
				nState = CHILD_CHECKED;
		}
		else
		{
			if (nState == SELF_AND_CHILD_CHECKED )
				nState = CHECKED;
			else if (nState == CHILD_CHECKED)
				nState = UNCHECKED;
		}
	}
	TreeCtrl.SetItemState(hItem, INDEXTOSTATEIMAGEMASK(nState),TVIS_STATEIMAGEMASK);
	
	if (nState == CHECKED || (REFRESH && (nState == SELF_AND_CHILD_CHECKED 
				|| nState == CHILD_CHECKED)))
	{
		// Mark the parents to indicate that a child item is selected.
		// Use checkbox with red border.
		HTREEITEM htiParent = TreeCtrl.GetParentItem(hItem);
		while (htiParent)
		{
			nState = TreeCtrl.GetItemState( htiParent, TVIS_STATEIMAGEMASK ) >> 12;
			if (nState == UNCHECKED)
				TreeCtrl.SetItemState( htiParent, INDEXTOSTATEIMAGEMASK(CHILD_CHECKED), 
						TVIS_STATEIMAGEMASK);
			else if ( nState == CHECKED )
				TreeCtrl.SetItemState( htiParent, INDEXTOSTATEIMAGEMASK(SELF_AND_CHILD_CHECKED), 
						TVIS_STATEIMAGEMASK );
			htiParent = TreeCtrl.GetParentItem(htiParent);
		}
		// if CHECKED, make sure all children are checked as well
		HTREEITEM htiChild = TreeCtrl.GetChildItem( hItem );
		while (htiChild)
		{
			SetCheck(htiChild, CHECK);
			htiChild = TreeCtrl.GetNextItem( htiChild, TVGN_NEXT );
		}
	}
	else if (nState == UNCHECKED)
	{
		// Maybe the parent ( ancestors ) state needs to be adjusted if
		// no more children selected.
		while ((hItem = TreeCtrl.GetParentItem( hItem )) != NULL )
		{
			BOOL bChildSelected = FALSE;
			HTREEITEM htiChild = TreeCtrl.GetChildItem( hItem );
			// Scan children
			while (htiChild)
			{
				UINT nChildState = TreeCtrl.GetItemState( htiChild, TVIS_STATEIMAGEMASK ) >> 12;
				if (nChildState != UNCHECKED && nChildState != NOSTATE )
				{
					bChildSelected = TRUE;
					break;
				}
				htiChild = TreeCtrl.GetNextItem( htiChild, TVGN_NEXT );
			}
			if (bChildSelected)
			{
				// The parent does not need to be updated
				// since there are other children still selected
				break;
			}
			else
			{
				// The parent item has no more children selected.
				// Mark accordingly
				UINT nParentState = TreeCtrl.GetItemState(hItem,TVIS_STATEIMAGEMASK ) >> 12;
				if (nParentState == CHILD_CHECKED )
				{
					TreeCtrl.SetItemState(hItem, INDEXTOSTATEIMAGEMASK(UNCHECKED),TVIS_STATEIMAGEMASK);
				}
				else if (nParentState == SELF_AND_CHILD_CHECKED)
				{
					TreeCtrl.SetItemState(hItem, INDEXTOSTATEIMAGEMASK(CHECKED),TVIS_STATEIMAGEMASK);
				}
			}
		}
 	}                                                                                                              
	return TRUE;
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnLButtonDblClk
// 
// Description:
// 	Called when the left mouse button is double-clicked.  A dialog is displayed
//  which allows the user to edit the name and runcount for the current item
// 
// Arguments:
// 	/*uFlags*/ - Not used
// 
// 	/*pt*/ - not used
// 
void cvCTestSuiteView::OnLButtonDblClk( UINT /*uFlags*/, CPoint /*pt*/)
{
	// Get Current tree node
	HTREEITEM hItem = GetTreeCtrl().GetSelectedItem();
	if (hItem != NULL)
	{
		// obtain a pointer to dragdrop item info from the item's data
		cvCDragDropItem* pDragDropItem = (cvCDragDropItem*) (GetTreeCtrl().GetItemData(hItem));
		ASSERT(pDragDropItem != NULL);

		if (pDragDropItem != NULL)
		{
			// set the dialog's caption and the test name and run count values
			cvCTestSuiteDlg dlgTestSuite(this);
			if (pDragDropItem->GetType() == cvCDragDropItem::EDragDropType_Suite)
			{
				dlgTestSuite.SetCaption(_T("Edit Test Suite"));
			}
			else
			{
				dlgTestSuite.SetCaption(_T("Edit Test"));
			}

			dlgTestSuite.SetRunCount(pDragDropItem->GetRunCount());
			dlgTestSuite.SetName(pDragDropItem->GetName());

			// if the user selects 'OK', then save the RunCount and Name values 
			// with the tree nodes dragdrop info.
			if (dlgTestSuite.DoModal() == IDOK)
			{
				pDragDropItem->SetRunCount(dlgTestSuite.GetRunCount());
				pDragDropItem->SetName	((LPCTSTR)dlgTestSuite.GetName());

				// Now update the visual appearance of the node item to 
				// reflect the name and runcount changes.
				UpdateNodeText(hItem);
			}
		}
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnKeyDown
// 
// Description:
// 	Called by the framework when a key is depressed while in this view.
//  The following actions are taken based on the actual key pressed:
//  VK_SPACE (spacebar) - The checkmark on the current tree node is toggled.
//  VK_DELETE (delete) - the current tree node and all childred are removed.
//  VK_INSERT (insert) - A new suite is added at the root node
//  VK_ADD (+ key) - the run count for the current node is incremented.
//  VK_SUBTRACT (- key) - the run count for the current node is decremented.
//
//  NOTE: SetModified called for DELETE.  It is set for all other choices inside
//        each of the methods which are called (e.g. SetCheck()). 
// 
// Arguments:
// 	nChar - The character which was pressed.
// 
// 	nRepCnt - The number of times the key was pressed
// 
//  nFlags - Specifies the scan code, key-transition code, previous key state, 
//       and context code (see CWnd::OnKeyDown).
// 
void cvCTestSuiteView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	bool bModified = true;

	if (nChar == VK_SPACE)
	{
		HTREEITEM hItem = GetTreeCtrl().GetSelectedItem();
		SetCheck(hItem, TOGGLE);
		return;
	}
	else if (nChar == VK_DELETE)
	{
		HTREEITEM hItem = GetTreeCtrl().GetSelectedItem();
		GetTreeCtrl().DeleteItem(hItem);
	}
	else if (nChar == VK_INSERT)
	{
		OnNewSuite();
	}
	else if (nChar == VK_ADD)
	{
		OnIncrementRunCount();
	}
	else if (nChar == VK_SUBTRACT)
	{
		OnDecrementRunCount();
	}
	else
	{
		bModified = false;
	}

	if (bModified)
	{
		GetDocument()->SetModifiedFlag();
	}

	CTreeView::OnKeyDown(nChar, nRepCnt, nFlags);
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnNewSuite
// 
// Description:
// 	Creates a new Test Suite node in the tree.  The node is assigned
//  a default name of 'New Suite'.
// 
void cvCTestSuiteView::OnNewSuite()
{
	cvCDragDropItem *pDragDropItem = new cvCDragDropItem;
	ASSERT(pDragDropItem != NULL);

	if (pDragDropItem != NULL)
	{
		pDragDropItem->SetType(cvCDragDropItem::EDragDropType_Suite);
		pDragDropItem->SetName(_T("New Suite"));

		InsertItem(pDragDropItem);
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnRenameTestOrSuite
// 
// Description:
// 	Called when the user selects to rename a test or suite node in the tree.
//  The name attribute of the cvCDragDropItem associated with the node is
//  modified in response to the name change. 
// 
void cvCTestSuiteView::OnRenameTestOrSuite() 
{
	HTREEITEM hItem = GetTreeCtrl().GetSelectedItem();
	if (hItem != NULL)
	{
		cvCDragDropItem* pDragDropItem = (cvCDragDropItem*) (GetTreeCtrl().GetItemData(hItem));
		ASSERT(pDragDropItem != NULL);

		if (pDragDropItem != NULL)
		{
			GetTreeCtrl().SetItemText(hItem,(LPCTSTR) pDragDropItem->GetName());
		}

		GetTreeCtrl().EditLabel(hItem);	

		if (pDragDropItem != NULL)
		{
			CString strText = GetTreeCtrl().GetItemText(hItem);
			pDragDropItem->SetName(_bstr_t(strText));
		}

		UpdateNodeText(hItem);
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnIncrementRunCount
// 
// Description:
// 	Called when the user selects to increment the run count of a test or test suite.
//  If there is a currently selected item in the treeview the handle of that item
//  is used grab the item data from the node (as cvCDragDropItem*).  The RunCount
//  property of that dragdrop item is incremented and the label for the node is
//  updated to reflect the runcount change.
// 
void cvCTestSuiteView::OnIncrementRunCount() 
{
	HTREEITEM hItem = GetTreeCtrl().GetSelectedItem();
	if (hItem != NULL)
	{
		cvCDragDropItem* pDragDropItem = (cvCDragDropItem*) (GetTreeCtrl().GetItemData(hItem));

		ASSERT(pDragDropItem != NULL);

		if (pDragDropItem != NULL)
		{
			pDragDropItem->IncrementCount();
			UpdateNodeText(hItem);
		}
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnDecrementRunCount
// 
// Description:
// 	Called when the user selects to decrement the run count of a test or test suite.
//  If there is a currently selected item in the treeview the handle of that item
//  is used grab the item data from the node (as cvCDragDropItem*).  The RunCount
//  property of that dragdrop item is decremented and the label for the node is
//  updated to reflect the runcount change.
// 
void cvCTestSuiteView::OnDecrementRunCount() 
{
	HTREEITEM hItem = GetTreeCtrl().GetSelectedItem();
	if (hItem != NULL)
	{
		cvCDragDropItem* pDragDropItem = (cvCDragDropItem*) (GetTreeCtrl().GetItemData(hItem));

		ASSERT(pDragDropItem != NULL);

		if (pDragDropItem != NULL)
		{
			pDragDropItem->DecrementCount();
			UpdateNodeText(hItem);
		}
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::UpdateNodeText
// 
// Description:
// 	Updates the node text indicated by hItem to include the test or test suite name
//  as well as the current run count.
// 
// Arguments:
// 	hItem - A handle to the tree item whose text is to be updated
// 
void cvCTestSuiteView::UpdateNodeText(HTREEITEM hItem)
{
	cvCDragDropItem* pDragDropItem = (cvCDragDropItem*) (GetTreeCtrl().GetItemData(hItem));
	ASSERT(pDragDropItem != NULL);

	if (pDragDropItem != NULL)
	{
		CString strText;
		strText.Format(_T("%s (%d)"), (LPCTSTR)pDragDropItem->GetName(), pDragDropItem->GetRunCount());
		GetTreeCtrl().SetItemText(hItem,strText);
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnEndLabelEdit
// 
// Description:
// 	Called by the framework when a user completes the edit of a node's label
// 
// Arguments:
// 	pNMHDR - A pointer to a notification message header
// 
// 	pResult - A pointer to an LRESULT which should be set before returning.
// 
void cvCTestSuiteView::OnEndLabelEdit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	ASSERT(pTVDispInfo != NULL);

	HTREEITEM hItem = pTVDispInfo->item.hItem;
	
	if (hItem != NULL && pTVDispInfo != NULL)
	{
		cvCDragDropItem* pDragDropItem = (cvCDragDropItem*) (GetTreeCtrl().GetItemData(hItem));
		ASSERT(pDragDropItem != NULL);

		if (pDragDropItem != NULL)
		{
			if (pTVDispInfo->item.pszText != NULL)
			{
				pDragDropItem->SetName(_bstr_t(pTVDispInfo->item.pszText));
				UpdateNodeText(hItem);
			}
		}
	}
	*pResult = 0;
}

// {group:View Classes}
// 
// Name: 
//    cvCTestSuiteView::OnTestSuiteRunTests
// 
// Description:
//    Called when the user selects to run a test or test suite from the
//    user interface.
// 
void cvCTestSuiteView::OnTestSuiteRunTests() 
{
	HTREEITEM hItem = GetTreeCtrl().GetSelectedItem();

	StartAtTest(hItem);
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnUpdateTestSuiteRunTest
// 
// Description:
// 	Called by the framework to determine if a user interface element associated
//  with running tests should be enabled.  Tests can be run IF no tests are 
//  current running, and an element in the tree view has been selected.
// 
// Arguments:
// 	pCmdUI - A pointer to the user interface element
// 
void cvCTestSuiteView::OnUpdateTestSuiteRunTest(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!m_bExecutingTests && GetTreeCtrl().GetSelectedItem() != NULL);
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteItem::FindNodeByName
// 
// Description:
// 	Finds a node in the tree based on the nodes' name (label)
// 
// Arguments:
// 	szNodeName - The name of the node to find
// 
// Results:
// 	A handle to the treectrl node whose name matched szNodeName
// 
HTREEITEM cvCTestSuiteView::FindNodeByName(LPCTSTR szNodeName)
{
	_bstr_t bstrNodeName(szNodeName);
	CTreeCtrl& TreeCtrl = GetTreeCtrl();

	HTREEITEM htiFound = NULL;
	HTREEITEM htiChild = TreeCtrl.GetChildItem(TVI_ROOT);

	while (htiChild != NULL)
	{
		// Quit looking once the a matching node name is found
		cvCDragDropItem* pDragDropItem = (cvCDragDropItem*) (TreeCtrl.GetItemData(htiChild));
		if (((pDragDropItem != NULL) && 
			(pDragDropItem->GetName() == bstrNodeName)))
		{
			htiFound = htiChild;
			break;
		}
		// or a matching node name is found in a child
		else
		{
			htiFound = FindNodeByName(szNodeName);
			if (htiFound != NULL)
			{
				break;
			}
		}

		// Get next node at this level
		htiChild = TreeCtrl.GetNextSiblingItem(htiChild);
	}
	return htiFound;
}

// {group:View Classes}
// 
// Name: 
//    cvCTestSuiteView::StartAtTest
// 
// Description:
//    Runs a test or tests starting at the node specified by szNodeName
//
// Arguments:
//     hItem - Handle to the tree node whose test are to be run.  All tests
//       at or below the node are run.
// 
BOOL cvCTestSuiteView::StartAtTest(LPCTSTR szNodeName)
{
	return StartAtTest(FindNodeByName(szNodeName));
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::StartAtTest
// 
// Description:
// 	Runs all tests starting with the node specified by hItem.
//  Instances of cvISupportTestOutput and cvITestOutput are created.
//  Then the instance of cvISupportTestOutput is added as a listener
//  to the instance of cvITestOutput.  The instance of cvITestOutput is passed
//  to all tests that are executed.
// 
// Arguments:
// 	hItem - The tree node to start running tests from
// 
// Results:
// 	TRUE if all tests passed; else FALSE
// 
BOOL cvCTestSuiteView::StartAtTest(HTREEITEM hItem)
{
	BOOL bRet(FALSE);

	if (hItem != NULL)
	{
		try
		{
			HRESULT hr(S_OK);

			// Get the spISupportTestOutput interface from this view (QI'ing from IDispatch)
			CComPtr<IDispatch> spIDispatch = this->GetIDispatch(TRUE);

			// Get cvISupportTestOutput interface
			CComPtr<cvISupportTestOutput> spISupportTestOutput;
			spIDispatch->QueryInterface(__uuidof(cvISupportTestOutput), (void**)&spISupportTestOutput);

			// Get cvITestOutput interface
			CComPtr<cvITestOutput> spITestOutput;
			spITestOutput.CoCreateInstance(__uuidof(cvCTestOutput));

			// Add cvISupportTestOutput as a listener for output
			hr = spITestOutput->AddListener(spISupportTestOutput);
			if (FAILED(hr))
				throw _com_error(hr);

			// specify log file name
			CString strLogFileName;
			cvCTestApp* pApp = dynamic_cast<cvCTestApp*>(AfxGetApp());
			ASSERT(pApp != NULL);
			pApp->GetLogFileName(strLogFileName);
			spITestOutput->LogFileName = _bstr_t(strLogFileName);

			// Set NumTestRuns to the RunCount for all suites starting at top suite
			ResetTests(hItem);

			// Execute the top level test, which recurses down to other tests
			ResetNumFailures();
			ResetNumPasses();

			m_bExecutingTests = true;	
			ExecuteTest(hItem, spITestOutput);
			m_bExecutingTests = false;	

			// Report # of passes and failures to test output stream
			CString strResults;
			strResults.Format(_T("# of Passes: %d   # of Failures: %d "), GetNumPasses(), GetNumFailures());
			spITestOutput->LogResult(_bstr_t(strResults.GetBuffer(0)), VARIANT_FALSE);
			bRet = GetNumFailures() > 0 ? FALSE : TRUE;

			// Report results to status bar
			GetParentFrame()->SetMessageText(strResults);
		}
		catch(_com_error e)
		{
			TCHAR szBuffer[128];
			_stprintf(szBuffer, _T("A error occured during the test run\n%s"), e.Description());
			MessageBox(szBuffer);
		}
	}
	return bRet;
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::ResetTests
// 
// Description:
// 	Resets the NumTestRuns attribute of cvCDragDropItem to zero.  Works recursively
//  to reset all tests starting with hParentItem.  This operation only affects
//  the parent item if bResetParent is true. 
// 
// Arguments:
// 	hParentItem - The node in the tree which is the parent of all nodes to be reset.
//  bResetParent - if true, res
// 

void cvCTestSuiteView::ResetTests(HTREEITEM hParentItem, bool bResetParent)
{
	// Reset parent if specifiedd
	if (bResetParent)
	{
		cvCDragDropItem* pDragDropItem = (cvCDragDropItem*) (GetTreeCtrl().GetItemData(hParentItem));
		if (pDragDropItem != NULL)
		{
			pDragDropItem->SetNumTestRuns(0);
		}
	}

	// if item has children, recurse down to reset them
	HTREEITEM hChildItem = GetTreeCtrl().GetChildItem(hParentItem);
	while (hChildItem != NULL)
	{
		ResetTests(hChildItem);
		hChildItem = GetTreeCtrl().GetNextItem(hChildItem, TVGN_NEXT);
	}
}

// {group:View Classes}
// 
// Name: 
//    cvCTestSuiteView::ExecuteTest
// 
// Description:
//    Called when the user selects to execute a test or test suite node
// 
// Arguments:
//    hParentItem - The handle to the parent test suite or test
// 
//    spITestOutput - A  pointer to the cvITestOutput interface which is
//    to report the results of the test
// 
void cvCTestSuiteView::ExecuteTest(HTREEITEM hParentItem, CComPtr<cvITestOutput>& spITestOutput)
{
	// Stop tests if commanded to by user
	if (!m_bExecutingTests)
	{
		return;
	}
	
	try
	{
		HRESULT hr = S_OK;

		cvCDragDropItem* pDragDropItem = (cvCDragDropItem*) (GetTreeCtrl().GetItemData(hParentItem));
		ASSERT(pDragDropItem != NULL);
		
		if (pDragDropItem != NULL)
		{
			// Run if this test item node is a test (not a suite)
			// and the test is enabled to run.
			if ( (pDragDropItem->GetType() == cvCDragDropItem::EDragDropType_Test)
				&& pDragDropItem->GetSelected())
			{
				// Instantiate test object which supports the cvITest interface
				CComPtr<cvITest> spITest;
				CLSID clsid = pDragDropItem->GetCLSID();
				if (clsid == IID_NULL)
				{
					_bstr_t bstrMessage = _T("An invalid CLSID was detected for a test '");
					bstrMessage += pDragDropItem->GetName();
					bstrMessage += "'";
					WriteToResultsView(bstrMessage);
				}
				else
				{
					CString strTestPassed(MAKEINTRESOURCE(IDS_TESTPASSED));
					CString strTestFailed(MAKEINTRESOURCE(IDS_TESTFAILED));

					hr = spITest.CoCreateInstance(clsid);
					if (FAILED(hr))
						throw _com_error(hr);

					while  (pDragDropItem->GetNumTestRuns() < pDragDropItem->GetRunCount())
					{
						_bstr_t bstrTestName = pDragDropItem->GetName();
						spITestOutput->TestName = bstrTestName;

						// Run the test, count any error encountered
						_variant_t varArg;
						hr = spITest->Run(spITestOutput, varArg);
						if (hr == S_FALSE)
						{
							IncrementNumFailures();
							WriteToResultsView(strTestFailed);
						}
						else
						{
							IncrementNumPasses();
							WriteToResultsView(strTestPassed);
						}

        	
						pDragDropItem->SetNumTestRuns(pDragDropItem->GetNumTestRuns()+1);

						// Stop tests if commanded to by user
						YieldProcessing();
						if (!m_bExecutingTests)
						{
							break;
						}
					}
				}
			}

			// For suites, reset run count for children, then run tests for all children of suite
			else if ( (pDragDropItem->GetType() == cvCDragDropItem::EDragDropType_Suite)
				&& pDragDropItem->GetSelected())
			{
				// Run tests the # of times specified by the user
				while  (pDragDropItem->GetNumTestRuns() < pDragDropItem->GetRunCount())
				{
					// reset test run count for all children, 
					ResetTests(hParentItem, false /*don't reset parent (i.e. suite)*/);
					
					// Create suite output title 
					CString strMessage;
					strMessage.Format(_T("---------- Suite: %s (Run Count: %d  Run#: %d) -----------"),
							(LPCTSTR) pDragDropItem->GetName(), pDragDropItem->GetRunCount(),
							pDragDropItem->GetNumTestRuns()+1); 

					// Write results to results view
					WriteToResultsView(_T(""));
					WriteToResultsView(strMessage);

					// Report results to status bar
					GetParentFrame()->SetMessageText(strMessage);

					// Recurse down to children of this item
					HTREEITEM hChildItem = GetTreeCtrl().GetChildItem(hParentItem);
					while (hChildItem != NULL)
					{
						ExecuteTest(hChildItem, spITestOutput);
						hChildItem = GetTreeCtrl().GetNextItem(hChildItem, TVGN_NEXT);
					}

					// Increment suite num test runs
					pDragDropItem->SetNumTestRuns(pDragDropItem->GetNumTestRuns()+1);

					// Stop tests if commanded to by user
					YieldProcessing();
					if (!m_bExecutingTests)
					{
						break;
					}
				}
			}
		}
	}
	catch(_com_error e)
	{
		TCHAR szBuffer[128];
		_stprintf(szBuffer, _T("A error occured during the test run (%s)"), e.ErrorMessage());
		WriteToResultsView(szBuffer);
	}
	catch (...)
	{
		WriteToResultsView(_T("A unknown error occured during the test run\n%s"));
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnUpdateTestSuiteRunTests
// 
// Description:
// 	Called by framework to determine if this menu item should be enabled.
// 
// Arguments:
// 	pCmdUI - A pointer to the user interface element which is to be enabled/disabled
// 
// Remarks:
// 	This is a remark
// 
void cvCTestSuiteView::OnUpdateTestSuiteRunTests(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);

	HTREEITEM hItem = GetTreeCtrl().GetSelectedItem();
	cvCDragDropItem* pDragDropItem = (cvCDragDropItem*) (GetTreeCtrl().GetItemData(hItem));

	ASSERT(pDragDropItem != NULL);

	if (pDragDropItem != NULL)
	{
		if (pDragDropItem->GetRunCount() > 0)
		{
			pCmdUI->Enable();
		}
	}
}

// {group:View Classes}
// 
// Name: 
//    cvCTestSuiteView::OnUpdateIncrementRunCount
// 
// Description:
//    Called when a WM_COMMAND is encoutered for incrementing the run count of a 
//    test suite or test item
// 
// Arguments:
//    pCmdUI - A pointer to the command user interface element
// 
// Remarks:
//    Increments the test suite or test item run count which indicates the number 
//    of times the test or suite is run.
// 

void cvCTestSuiteView::OnUpdateIncrementRunCount(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(FALSE);

	HTREEITEM hItem = GetTreeCtrl().GetSelectedItem();
	if (hItem != NULL)
	{
		cvCDragDropItem* pDragDropItem = (cvCDragDropItem*) (GetTreeCtrl().GetItemData(hItem));

		ASSERT(pDragDropItem != NULL);

		if (pDragDropItem != NULL)
		{
			pCmdUI->Enable();
		}
	}
}

// {group:View Classes}
// 
// Name: 
//    cvCTestSuiteView::OnDeleteItem
// 
// Description:
//    Called when an item in the tree is to be deleted.  Obtains a pointer
//    to the cvCDragDropItem stored in the itemdata and deletes it.
// 
// Arguments:
//    pNMHDR - A pointer to the notification message header associated with the operation
// 
//    pResult - The result of the operation (0 if no error)
// 
void cvCTestSuiteView::OnDeleteItem(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	if (pNMTreeView->itemOld.lParam)
	{
		TRACE1("CTestSuiteView::DeleteItem (%p)\n", (cvCDragDropItem*) pNMTreeView->itemOld.lParam);
		HTREEITEM hItem = pNMTreeView->itemOld.hItem;

		// delete cvCDragDropItem stored at this node
		delete ((cvCDragDropItem*) pNMTreeView->itemOld.lParam);

		// Zero out the cvCDragDropItem pointer
		GetTreeCtrl().SetItemData(hItem, 0);
	}	
	*pResult = 0;
}
  
// {group:View Classes}
// 
// Name: 
//    cvCTestSuiteView::WriteToResultsView
// 
// Description:
//    Used to record test results to the cvCResultsView
// 
// Arguments:
//    szMessage - The message to be sent to cvCResultsView
// 
void cvCTestSuiteView::WriteToResultsView(LPCTSTR szMessage)
{
	CDocument *pDoc = GetDocument();
	ASSERT(pDoc != NULL);
	if (pDoc != NULL)
	{
		POSITION pos = pDoc->GetFirstViewPosition();
		while (pos != NULL)
		{
			cvCResultsView* pView = dynamic_cast<cvCResultsView*>(pDoc->GetNextView(pos));
			if (pView != NULL)
			{
				pView->Log((LPCTSTR) szMessage);
				YieldProcessing();
				break;
			}
		}
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::CreateXMLString
// 
// Description:
// 	Creates a string which contains the XML that describes the current set of test suites and tests
// 
// Arguments:
// 	strXML - A reference to a string that will contain XML for the current set of suites and tests
// 
void cvCTestSuiteView::CreateXMLString(CString& strXML)
{
	CTreeCtrl& TreeCtrl = GetTreeCtrl();

	HTREEITEM htiChild = TreeCtrl.GetChildItem(TVI_ROOT);

	strXML = _T("<?xml version='1.0'?>\r\n");
	strXML += _T("<?xml:stylesheet type='text/xsl' href='ClinivisionTests.xsl'?>\r\n");
	strXML += _T("<TESTSUITES>\r\n");

	while (htiChild != NULL)
	{
		InternalCreateXMLString(htiChild, strXML);
		htiChild = TreeCtrl.GetNextSiblingItem(htiChild);
	}

	strXML += "</TESTSUITES>\r\n";
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::InternalCreateXMLString
// 
// Description:
// 	Creates a string which contains the XML for a single node in the tree
// 
// Arguments:
// 	hti - a handle to the tree node whose XML should be created.
// 	strXML - A reference to a string that will contain XML for the current set of suites and tests
// 
void cvCTestSuiteView::InternalCreateXMLString(HTREEITEM hti, CString& strXML)
{
	// Add current node to XML string
	cvCDragDropItem* pDragDropItem = (cvCDragDropItem*) (GetTreeCtrl().GetItemData(hti));
	if (pDragDropItem != NULL)
	{
		if (pDragDropItem->GetType() == cvCDragDropItem::EDragDropType_Suite)
		{
			strXML += _T("<TESTSUITE>\r\n");
		}
		else
		{
			strXML += _T("<TEST>\r\n");
		}

		char szBuffer[33];
		
		strXML += _T("\t<NAME>");
		strXML += pDragDropItem->GetName();
		strXML += _T("</NAME>\r\n");
		strXML += _T("\t<RUNCOUNT>");
		strXML += itoa(pDragDropItem->GetRunCount(), szBuffer, 10);
		strXML += _T("</RUNCOUNT>\r\n");
		strXML += _T("\t<SELECTED>");
		strXML += itoa(pDragDropItem->GetSelected(), szBuffer, 10);
		strXML += _T("</SELECTED>\r\n");

		if (pDragDropItem->GetType() == cvCDragDropItem::EDragDropType_Test)
		{
			LPOLESTR pszCLSID;

			strXML += _T("\t<CLSID>");
			if (StringFromCLSID(pDragDropItem->GetCLSID(), &pszCLSID) == S_OK) 
			{
				strXML += pszCLSID;
				CoTaskMemFree(pszCLSID);
			}
			strXML += _T("</CLSID>\r\n");
		}
	}

	HTREEITEM hChildItem = GetTreeCtrl().GetChildItem(hti);

	while (hChildItem != NULL)
	{
		InternalCreateXMLString(hChildItem, strXML);
		hChildItem = GetTreeCtrl().GetNextItem(hChildItem, TVGN_NEXT);
	}

	if (pDragDropItem->GetType() == cvCDragDropItem::EDragDropType_Suite)
	{
		strXML += _T("</TESTSUITE>\r\n");
	}
	else
	{
		strXML += _T("</TEST>\r\n");
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnViewCollapseTree
// 
// Description:
// 	Called by the framework when the user selects to collapse the tree 
//  items under the curren mode.
// 
void cvCTestSuiteView::OnViewCollapseTree() 
{
	HTREEITEM hItem = GetTreeCtrl().GetSelectedItem();
	if (hItem != NULL)
	{
		GetTreeCtrl().Expand(hItem, TVE_COLLAPSE);
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnUpdateViewCollapseTree
// 
// Description:
// 	Called by framework to determine if the Collapse tree menu item  should be enabled.
// 
// Arguments:
// 	pCmdUI - A pointer to the user interface element which is to be enabled/disabled
// 
// Remarks:
// 	This is a remark
// 
void cvCTestSuiteView::OnUpdateViewCollapseTree(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetTreeCtrl().GetSelectedItem() != NULL);
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnViewExpandTree
// 
// Description:
// 	Called by the framework when the user selects to expand the nodes in a tree
//  starting with the currently selected node.
// 
void cvCTestSuiteView::OnViewExpandTree() 
{
	HTREEITEM hItem = GetTreeCtrl().GetSelectedItem();
	if (hItem != NULL)
	{
		ExpandTree(hItem);
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::ExpandTree
// 
// Description:
// 	Expands all of the nodes in the tree starting with the node specified
//  by hItem. This function is recursively called until no more children
//  of the specified node are found.
// 
void cvCTestSuiteView::ExpandTree(HTREEITEM hItem)
{
	GetTreeCtrl().Expand(hItem, TVE_EXPAND);

	HTREEITEM hChildItem = GetTreeCtrl().GetChildItem(hItem);

	while (hChildItem != NULL)
	{
		ExpandTree(hChildItem);
		hChildItem = GetTreeCtrl().GetNextItem(hChildItem, TVGN_NEXT);
	}

}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnUpdateViewExpandTree
// 
// Description:
// 	Called by framework to determine if the Expand tree menu item  should be enabled.
// 
// Arguments:
// 	pCmdUI - A pointer to the user interface element which is to be enabled/disabled
// 
// Remarks:
// 	This is a remark
// 
void cvCTestSuiteView::OnUpdateViewExpandTree(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(GetTreeCtrl().GetSelectedItem() != NULL);
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::YieldProcessing
// 
// Description:
// 	This function reads the windows message queue for any outstanding messages, 
//  then pumps them through the app to allow other messages to be processed.
//  Should be called when in a tight loop.
// 
void cvCTestSuiteView::YieldProcessing()
{
	// Yield once in a while to allow GUI to work
	MSG msg;
	while (::PeekMessage (&msg, NULL, 0, 0, PM_NOREMOVE))
	{ 
		if (!AfxGetApp ()->PumpMessage ())
		{ 
			::PostQuitMessage (0); 
			return ; 
		} 
	}
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnFileStopTests
// 
// Description:
// 	Called by framework when the user want to stop the execution of tests
//  m_bExecutingTests is set to TRUE when tests are run and this flag
//  is also checked during a test run to determine if the test run should
//  stop.
// 
void cvCTestSuiteView::OnFileStopTests() 
{
	m_bExecutingTests = false;	
}

// {group:View Classes}
// 
// Name: 
// 	cvCTestSuiteView::OnUpdateFileStopTests
// 
// Description:
// 	Called by framework to determine if the Stop Tests tree menu item  should be enabled.
// 
// Arguments:
// 	pCmdUI - A pointer to the user interface element which is to be enabled/disabled
// 
// Remarks:
// 	This is a remark
// 
void cvCTestSuiteView::OnUpdateFileStopTests(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(	m_bExecutingTests);
}
